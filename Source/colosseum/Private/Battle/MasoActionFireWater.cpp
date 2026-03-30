// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoActionFireWater.h"
#include "Battle/BattleGameMode.h"

#define NS_Main TEXT("/Game/FixEffect/miyaryu/NS/F+W/F+W.F+W")
#define Fire_Water_HP_Base 30
#define Fire_Water_HP_ATK_coeff 0.12
#define Fire_Water_HP_DEF_coeff -0.1
#define Fire_Water_MP_Base 5
#define Fire_Water_MP_ATK_coeff 0.07
#define TotalEffectTime 0.5f

UMasoActionFireWater::UMasoActionFireWater()
{
	IncidenceNiagaraSystem = nullptr;
	ActionNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, NS_Main);
}

void UMasoActionFireWater::CalcAction(FActionResultData* ActionResult, const uint8 PanelX, const uint8 PanelY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode)
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
        float calculatedDamage = Fire_Water_HP_Base + Fire_Water_HP_ATK_coeff * attackPower;
		float calculatedMpDamage = Fire_Water_MP_Base + Fire_Water_MP_ATK_coeff * attackPower;

        // Clamp(変数, Min, Max);変数の取りうる値を制限する.
        calculatedDamage = FMath::Clamp(calculatedDamage, 0.0f, Target->GetMaxHp());
		calculatedMpDamage = FMath::Clamp(calculatedMpDamage, 0.0f, Target->GetMaxMp());

        UE_LOG(LogTemp, Warning, TEXT("攻撃特技の計算：calculatedDamage: %f, attackPower: %f, defensePower: %f"), calculatedDamage, attackPower, defensePower);

        TargetData.HpDamage = calculatedDamage;
        TargetData.MpDamage = calculatedMpDamage;
        ActionResult->ActionAttackResult.AttackTargets.Add(TargetData);
    }
}

void UMasoActionFireWater::ReflectAction(FActionResultData& ActionResult, ABattleGameMode* GameMode)
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

void UMasoActionFireWater::ActionEffect(TObjectPtr<AMasoPanel> MasoPanel)
{
	UE_LOG(LogTemp, Warning, TEXT("水蒸気爆発のエフェクト"));
	Super::ActionEffect(MasoPanel);
}

float UMasoActionFireWater::GetActionTime()
{
    return TotalEffectTime;
}

EActionType UMasoActionFireWater::GetActionType()
{
	return EActionType::EAT_Normal;
}
