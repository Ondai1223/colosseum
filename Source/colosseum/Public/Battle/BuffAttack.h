// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Battle/BuffDebuffBase.h"
#include "BuffAttack.generated.h"

/**
 * 攻撃力に関するバフクラス
 */
UCLASS()
class COLOSSEUM_API UBuffAttack : public UBuffDebuffBase
{
	GENERATED_BODY()

public:
	UBuffAttack();

	virtual float CalcPower(float BasePower) override;
	
};
