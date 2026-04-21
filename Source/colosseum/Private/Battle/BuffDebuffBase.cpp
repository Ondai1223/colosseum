// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/BuffDebuffBase.h"
#include "NiagaraFunctionLibrary.h"


void UBuffDebuffBase::Init(int32 Times, float Magnification, const FVector& Location)
{
	Duration = Times;
	Multiplier = Magnification;
	if (BuffDebuffSystem)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), BuffDebuffSystem, Location, FRotator::ZeroRotator);
	}
}

float UBuffDebuffBase::CalcPower(float BasePower)
{
	return 0.0f; // 基底クラスでは0を返す。派生クラスでオーバーライドして具体的な計算を行う。
}
