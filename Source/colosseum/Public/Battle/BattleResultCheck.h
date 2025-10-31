// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Battle/Interface/BattleResultCheckInterface.h"
#include "BattleResultCheck.generated.h"

/**
 * 戦闘結果チェック
 */
UCLASS()
class COLOSSEUM_API UBattleResultCheck : public UObject, public IBattleResultCheckInterface
{
	GENERATED_BODY()
	
public:
    // 戦闘結果チェック
    virtual void CheckBattleResult(ABattleGameMode* GameMode) override;

};
