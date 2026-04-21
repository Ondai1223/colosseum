// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoActionWaterThunder.h"
#include "Battle/BattleGameMode.h"

#define NS_Incidence TEXT("/Game/FixEffect/miyaryu/NS/W+T/W+T_incidence.W+T_incidence")
#define NS_Main TEXT("/Game/FixEffect/miyaryu/NS/W+T/W+T.W+T")

#define IncidentEffectTime 4.3f
#define TotalEffectTime 5.0f

#define Water_Thunder_Base 1.0f

UMasoActionWaterThunder::UMasoActionWaterThunder()
{
	IncidenceNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, NS_Incidence);
	ActionNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, NS_Main);
	Duration = 2;
	EffectDuration = IncidentEffectTime;
}

void UMasoActionWaterThunder::CalcAction(FActionResultData* ActionResult, const uint8 PanelX, const uint8 PanelY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode)
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

void UMasoActionWaterThunder::ReflectAction(FActionResultData& ActionResult, ABattleGameMode* GameMode)
{
    for (TArray<FActionAttackTargetData>::TIterator Ite(ActionResult.ActionAttackResult.AttackTargets); Ite; ++Ite)
    {
        // デバフの付与
        UBuffDebuffBase* Debuff;
        Debuff = NewObject<UDebuffMove>(Ite->TargetUnit);
        Debuff->Init(2, Water_Thunder_Base, Ite->TargetUnit->Get3DLocation());
        Ite->TargetUnit->AddBuffDebuff(Debuff);
    }
}

void UMasoActionWaterThunder::ActionEffect(TObjectPtr<AMasoPanel> MasoPanel)
{
	UE_LOG(LogTemp, Warning, TEXT("電気の海エフェクト"));
	Super::ActionEffect(MasoPanel);
}

float UMasoActionWaterThunder::GetActionTime()
{
	return TotalEffectTime;
}

EActionType UMasoActionWaterThunder::GetActionType()
{
	return EActionType::EAT_Normal;
}

