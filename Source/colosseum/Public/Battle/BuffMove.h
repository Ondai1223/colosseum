// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Battle/BuffDebuffBase.h"
#include "BuffMove.generated.h"

/**
 * 移動力に関するバフクラス
 */
UCLASS()
class COLOSSEUM_API UBuffMove : public UBuffDebuffBase
{
	GENERATED_BODY()

public:
	UBuffMove();
	
	virtual float CalcPower(float BasePower) override;
};
