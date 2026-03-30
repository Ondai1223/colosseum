// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoActionThunderFire.h"

#define NS_Incidence TEXT("/Game/FixEffect/miyaryu/NS/F+T/F+T_incidence.F+T_incidence")
#define NS_Main TEXT("/Game/FixEffect/miyaryu/NS/F+T/F+T.F+T")

#define IncidentEffectTime 2.0f
#define TotalEffectTime 3.0f

UMasoActionThunderFire::UMasoActionThunderFire()
{   
	IncidenceNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, NS_Incidence);
	ActionNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, NS_Main);
	EffectDuration = IncidentEffectTime;
}

void UMasoActionThunderFire::CalcAction(FActionResultData* ActionResult, const uint8 PanelX, const uint8 PanelY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode)
{
	// 計算
}

void UMasoActionThunderFire::ReflectAction(FActionResultData& ActionResult, ABattleGameMode* GameMode)
{
}

void UMasoActionThunderFire::ActionEffect(TObjectPtr<AMasoPanel> MasoPanel)
{
	UE_LOG(LogTemp, Warning, TEXT("火山灰と雷のエフェクト"));
	Super::ActionEffect(MasoPanel);
}

float UMasoActionThunderFire::GetActionTime()
{
	return TotalEffectTime;
}

EActionType UMasoActionThunderFire::GetActionType()
{
	return EActionType::EAT_Immediate;
}