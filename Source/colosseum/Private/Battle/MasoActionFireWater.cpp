// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoActionFireWater.h"

UMasoActionFireWater::UMasoActionFireWater()
{
	ActionNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/FixEffect/miyaryu/NS/F+W/F+W.F+W"));
}

void UMasoActionFireWater::ApplyAction()
{
	UE_LOG(LogTemp, Warning, TEXT("火と水の魔素が組み合わさりました。"));
}

void UMasoActionFireWater::ActionEffect(TObjectPtr<AMasoPanel> MasoPanel)
{
	UE_LOG(LogTemp, Warning, TEXT("水蒸気爆発のエフェクト"));
	Super::ActionEffect(MasoPanel);
}

EActionType UMasoActionFireWater::GetActionType()
{
	return EActionType::EAT_Normal;
}
