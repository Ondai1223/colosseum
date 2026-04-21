// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Battle/BuffDebuffBase.h"
#include "BuffDefense.generated.h"

/**
 * 防御力に関するバフクラス
 */
UCLASS()
class COLOSSEUM_API UBuffDefense : public UBuffDebuffBase
{
	GENERATED_BODY()

public:
	UBuffDefense();
	
	virtual float CalcPower(float BasePower) override;
};
