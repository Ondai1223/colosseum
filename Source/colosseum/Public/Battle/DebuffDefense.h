// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Battle/BuffDebuffBase.h"
#include "DebuffDefense.generated.h"

/**
 * 防御力に関するデバフクラス
 */
UCLASS()
class COLOSSEUM_API UDebuffDefense : public UBuffDebuffBase
{
	GENERATED_BODY()
public:
	UDebuffDefense();
	
	virtual float CalcPower(float BasePower) override;
};
