// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle/MasoActionFireFire.h"
#include "Battle/BattleGameMode.h"

#define NS_Main TEXT("/Game/FixEffect/miyaryu/NS/F+F/F+F.F+F")
#define Fire_Fire_Base 30
#define Fire_Fire_ATK_coeff 0.25
#define Fire_Fire_DEF_coeff -0.2
#define TotalEffectTime 1.4f


UMasoActionFireFire::UMasoActionFireFire()
{
	IncidenceNiagaraSystem = nullptr;
	ActionNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, NS_Main);
}

void UMasoActionFireFire::CalcAction(FActionResultData* ActionResult, const uint8 PanelX, const uint8 PanelY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode)
{
	ActionResult->ActionUnit = ActionUnit;

	TObjectPtr Target = GameMode->GetUnit(PanelX, PanelY);
	UE_LOG(LogTemp, Warning, TEXT("UMasoActionFireFire::CalcAction is called(%d, %d)"), PanelX, PanelY);
	if (Target)
	{
        FActionAttackTargetData TargetData;
        TargetData.TargetUnit = Target;
        // FActionTargetAndLocationへの情報格納
        FActionTargetAndLocation TargetLocation;
        TargetLocation.Location.X = PanelX;
        TargetLocation.Location.Y = PanelY;
        TargetLocation.Target = Target;

        // ダメージ計算
        // 攻撃力(行動キャラ)＊特技倍率 / 防御力(被)＊攻撃倍率＝ダメージ
        float attackPower = ActionUnit->GetAttackPower();
        float defensePower = Target->GetDefencePower();
        float calculatedDamage = Fire_Fire_Base + Fire_Fire_ATK_coeff * attackPower + Fire_Fire_DEF_coeff * defensePower;

        // Clamp(変数, Min, Max);変数の取りうる値を制限する.
        calculatedDamage = FMath::Clamp(calculatedDamage, 0.0f, Target->GetMaxHp());


		UE_LOG(LogTemp, Warning, TEXT("攻撃特技の計算：calculatedDamage: %f, attackPower: %f, defensePower: %f"), calculatedDamage, attackPower, defensePower);

        TargetData.HpDamage = calculatedDamage;
        TargetData.MpDamage = 0.0f;
        ActionResult->ActionAttackResult.AttackTargets.Add(TargetData);
	}
}

void UMasoActionFireFire::ReflectAction(FActionResultData& ActionResult, ABattleGameMode* GameMode)
{
    for (TArray<FActionAttackTargetData>::TIterator Ite(ActionResult.ActionAttackResult.AttackTargets); Ite; ++Ite)
    {
        float NextHp = Ite->TargetUnit->GetHp() - Ite->HpDamage;
        float NextMp = Ite->TargetUnit->GetMp() - Ite->MpDamage;

        Ite->TargetUnit->SetHp(NextHp);
        Ite->TargetUnit->SetMp(NextMp);
        GameMode->ReflectionStatus();
        if (Ite->TargetUnit->IsDead())
        {
            Ite->TargetUnit->PlayAnimationDeath();
        }
        else
        {
            Ite->TargetUnit->PlayAnimationDamage();
        }
        UE_LOG(LogTemp, Warning, TEXT("NextHp: %f, NextMp: %f"), NextHp, NextMp);
    }
}

void UMasoActionFireFire::ActionEffect(TObjectPtr<AMasoPanel> MasoPanel)
{
	UE_LOG(LogTemp, Warning, TEXT("大爆発エフェクト"));
	Super::ActionEffect(MasoPanel);
}

float UMasoActionFireFire::GetActionTime()
{
	return TotalEffectTime;
}

EActionType UMasoActionFireFire::GetActionType()
{
	return EActionType::EAT_Immediate;
}
