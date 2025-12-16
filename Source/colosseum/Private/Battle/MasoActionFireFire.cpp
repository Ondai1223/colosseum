// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoActionFireFire.h"

UMasoActionFireFire::UMasoActionFireFire()
{
	ActionNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/FixEffect/miyaryu/NS/F+F/F+F.F+F"));
}

void UMasoActionFireFire::ApplyAction()
{
	UE_LOG(LogTemp, Warning, TEXT("火と火の魔素が組み合わさりました。"));
}

void UMasoActionFireFire::ActionEffect(TObjectPtr<AMasoPanel> MasoPanel)
{
	UE_LOG(LogTemp, Warning, TEXT("大爆発エフェクト"));
	Super::ActionEffect(MasoPanel);
}

EActionType UMasoActionFireFire::GetActionType()
{
	return EActionType::EAT_Immediate;
}
