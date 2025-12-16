// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoActionThunderFire.h"

UMasoActionThunderFire::UMasoActionThunderFire()
{
	ActionNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/FixEffect/miyaryu/NS/F+T/F+T.F+T"));
}

void UMasoActionThunderFire::ApplyAction()
{
	UE_LOG(LogTemp, Warning, TEXT("雷と火の魔素が組み合わさりました。"));
}

void UMasoActionThunderFire::ActionEffect(TObjectPtr<AMasoPanel> MasoPanel)
{
	UE_LOG(LogTemp, Warning, TEXT("火山灰と雷のエフェクト"));
	Super::ActionEffect(MasoPanel);
}

EActionType UMasoActionThunderFire::GetActionType()
{
	return EActionType::EAT_Immediate;
}
