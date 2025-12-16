// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoActionThunderThunder.h"

UMasoActionThunderThunder::UMasoActionThunderThunder()
{
	ActionNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/FixEffect/miyaryu/NS/T+T/T+T.T+T"));
}

void UMasoActionThunderThunder::ApplyAction()
{
	UE_LOG(LogTemp, Warning, TEXT("雷と雷の魔素が組み合わさりました。"));
}

void UMasoActionThunderThunder::ActionEffect(TObjectPtr<AMasoPanel> MasoPanel)
{
	UE_LOG(LogTemp, Warning, TEXT("巨大雷のエフェクト"));
	Super::ActionEffect(MasoPanel);
}

EActionType UMasoActionThunderThunder::GetActionType()
{
	return EActionType::EAT_Normal;
}
