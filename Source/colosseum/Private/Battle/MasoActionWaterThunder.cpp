// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoActionWaterThunder.h"

UMasoActionWaterThunder::UMasoActionWaterThunder()
{
	ActionNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/FixEffect/miyaryu/NS/W+T/W+T.W+T"));
}

void UMasoActionWaterThunder::ApplyAction()
{
	UE_LOG(LogTemp, Warning, TEXT("水と雷の魔素が組み合わさりました。"));
}

void UMasoActionWaterThunder::ActionEffect(TObjectPtr<AMasoPanel> MasoPanel)
{
	UE_LOG(LogTemp, Warning, TEXT("電気の海エフェクト"));
	Super::ActionEffect(MasoPanel);
}

EActionType UMasoActionWaterThunder::GetActionType()
{
	return EActionType::EAT_Normal;
}

