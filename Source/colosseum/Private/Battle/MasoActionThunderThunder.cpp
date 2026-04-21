// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoActionThunderThunder.h"
#include "Battle/BattleGameMode.h"

#define NS_Main TEXT("/Game/FixEffect/miyaryu/NS/T+T/T+T.T+T")
#define Thunder_Thunder_Base 70
#define Thunder_Thunder_ATK_coeff 0.35
#define Thunder_Thunder_DEF_coeff -0.1
#define TotalEffectTime 1.6f

UMasoActionThunderThunder::UMasoActionThunderThunder()
{
	IncidenceNiagaraSystem = nullptr;
	ActionNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, NS_Main);
}

void UMasoActionThunderThunder::CalcAction(FActionResultData* ActionResult, const uint8 PanelX, const uint8 PanelY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode)
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
        float calculatedDamage = Thunder_Thunder_Base + Thunder_Thunder_ATK_coeff * attackPower;

        // Clamp(変数, Min, Max);変数の取りうる値を制限する.
        calculatedDamage = FMath::Clamp(calculatedDamage, 0.0f, Target->GetMaxHp());


        UE_LOG(LogTemp, Warning, TEXT("攻撃特技の計算：calculatedDamage: %f, attackPower: %f, defensePower: %f"), calculatedDamage, attackPower, defensePower);

        TargetData.HpDamage = calculatedDamage;
        TargetData.MpDamage = 0.0f;
        ActionResult->ActionAttackResult.AttackTargets.Add(TargetData);
    }
}

void UMasoActionThunderThunder::ReflectAction(FActionResultData& ActionResult, ABattleGameMode* GameMode)
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
            GameMode->CheckBattleResult();
        }
        else
        {
            Ite->TargetUnit->PlayAnimationDamage();
        }
        UE_LOG(LogTemp, Warning, TEXT("NextHp: %f, NextMp: %f"), NextHp, NextMp);
    }
}

void UMasoActionThunderThunder::ActionEffect(TObjectPtr<AMasoPanel> MasoPanel)
{
	UE_LOG(LogTemp, Warning, TEXT("巨大雷のエフェクト"));
	Super::ActionEffect(MasoPanel);
}

float UMasoActionThunderThunder::GetActionTime()
{
    return TotalEffectTime;
}

EActionType UMasoActionThunderThunder::GetActionType()
{
	return EActionType::EAT_Normal;
}
