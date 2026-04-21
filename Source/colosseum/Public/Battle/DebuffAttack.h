// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Battle/BuffDebuffBase.h"
#include "DebuffAttack.generated.h"

/**
 * 攻撃力に関するデバフクラス
 */
UCLASS()
class COLOSSEUM_API UDebuffAttack : public UBuffDebuffBase
{
	GENERATED_BODY()

public:
	UDebuffAttack();
	
	virtual float CalcPower(float BasePower) override;
};
