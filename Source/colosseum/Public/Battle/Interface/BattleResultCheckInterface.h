// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BattleResultCheckInterface.generated.h"


class ABattleGameMode;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBattleResultCheckInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * インタフェースクラス
 */
class COLOSSEUM_API IBattleResultCheckInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:


    virtual void CheckBattleResult(ABattleGameMode* GameMode) = 0;

};
