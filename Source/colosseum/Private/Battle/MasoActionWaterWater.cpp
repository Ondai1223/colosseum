// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoActionWaterWater.h"

UMasoActionWaterWater::UMasoActionWaterWater()
{
	ActionNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/FixEffect/miyaryu/NS/W+W/W+W.W+W"));
}

void UMasoActionWaterWater::ApplyAction()
{
	UE_LOG(LogTemp, Warning, TEXT("水と水の魔素が組み合わさりました。"));
}

void UMasoActionWaterWater::ActionEffect(TObjectPtr<AMasoPanel> MasoPanel)
{
	UE_LOG(LogTemp, Warning, TEXT("深海エフェクト"));
	Super::ActionEffect(MasoPanel);
}

EActionType UMasoActionWaterWater::GetActionType()
{
	return EActionType::EAT_Immediate;
}
