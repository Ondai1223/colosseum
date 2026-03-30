// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoActionWaterThunder.h"

#define NS_Incidence TEXT("/Game/FixEffect/miyaryu/NS/W+T/W+T_incidence.W+T_incidence")
#define NS_Main TEXT("/Game/FixEffect/miyaryu/NS/W+T/W+T.W+T")

#define IncidentEffectTime 4.3f
#define TotalEffectTime 5.0f

UMasoActionWaterThunder::UMasoActionWaterThunder()
{
	IncidenceNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, NS_Incidence);
	ActionNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, NS_Main);
	EffectDuration = IncidentEffectTime;
}

void UMasoActionWaterThunder::CalcAction(FActionResultData* ActionResult, const uint8 PanelX, const uint8 PanelY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode)
{
}

void UMasoActionWaterThunder::ReflectAction(FActionResultData& ActionResult, ABattleGameMode* GameMode)
{
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

