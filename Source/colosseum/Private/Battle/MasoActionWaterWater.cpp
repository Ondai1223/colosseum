// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoActionWaterWater.h"

#define NS_Incidence TEXT("/Game/FixEffect/miyaryu/NS/W+W/W+W_incidence.W+W_incidence")

#define IncidentEffectTime 4.0f
#define TotalEffectTime 5.0f

UMasoActionWaterWater::UMasoActionWaterWater()
{
	IncidenceNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, NS_Incidence);
	ActionNiagaraSystem = nullptr;
	EffectDuration = IncidentEffectTime;
}

void UMasoActionWaterWater::CalcAction(FActionResultData* ActionResult, const uint8 PanelX, const uint8 PanelY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode)
{
}

void UMasoActionWaterWater::ReflectAction(FActionResultData& ActionResult, ABattleGameMode* GameMode)
{
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
