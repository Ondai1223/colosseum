// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Battle/BuffDebuffBase.h"
#include "DebuffMove.generated.h"

/**
 * 移動力に関するデバフクラス
 */
UCLASS()
class COLOSSEUM_API UDebuffMove : public UBuffDebuffBase
{
	GENERATED_BODY()
public:
	UDebuffMove();
	
	virtual float CalcPower(float BasePower) override;
};
