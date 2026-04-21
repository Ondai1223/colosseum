// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoActionWaterWater.h"
#include "Battle/BattleGameMode.h"

#define NS_Main TEXT("/Game/FixEffect/miyaryu/NS/W+W/W+W_incidence.W+W_incidence")

#define IncidentEffectTime 4.0f
#define TotalEffectTime 5.0f

#define Water_Water_Base 0.1f

UMasoActionWaterWater::UMasoActionWaterWater()
{
	IncidenceNiagaraSystem = nullptr;
	ActionNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, NS_Main);
	Duration = 2;
}

void UMasoActionWaterWater::CalcAction(FActionResultData* ActionResult, const uint8 PanelX, const uint8 PanelY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode)
{
    // 計算
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

        ActionResult->ActionAttackResult.AttackTargets.Add(TargetData);
    }
}

void UMasoActionWaterWater::ReflectAction(FActionResultData& ActionResult, ABattleGameMode* GameMode)
{
    for (TArray<FActionAttackTargetData>::TIterator Ite(ActionResult.ActionAttackResult.AttackTargets); Ite; ++Ite)
    {
        // デバフの付与
        UBuffDebuffBase* Debuff;
        Debuff = NewObject<UDebuffAttack>(Ite->TargetUnit);
        Debuff->Init(2, Water_Water_Base, Ite->TargetUnit->Get3DLocation());
        Ite->TargetUnit->AddBuffDebuff(Debuff);
    }
}

void UMasoActionWaterWater::ActionEffect(TObjectPtr<AMasoPanel> MasoPanel)
{
	UE_LOG(LogTemp, Warning, TEXT("深海エフェクト"));
	Super::ActionEffect(MasoPanel);
}

float UMasoActionWaterWater::GetActionTime()
{
	return TotalEffectTime;
}

EActionType UMasoActionWaterWater::GetActionType()
{
	return EActionType::EAT_Immediate;
}
