// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BattleInterface.generated.h"

UENUM(BlueprintType)
enum class ETickBattleState : uint8
{
    EBS_Tick UMETA(DisplayName = "実行中"), // 実行中
    EBS_TurnEnd  UMETA(DisplayName = "今回のターン終了"), // 今回のターン終了
    EBS_End UMETA(DisplayName = "終了"), // 終了
};


class ABattleGameMode;
// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UBattleInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * バトルインタフェース
 */
class COLOSSEUM_API IBattleInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    // 戦闘開始前の先制後攻の決定イベント
    virtual void BeginBattleState(ABattleGameMode* GameMode) = 0;

    // 戦闘開始前の先制後攻の表示イベント
    // trueで次の状態へ
    virtual ETickBattleState TickBattleState(ABattleGameMode* GameMode, float DeltaSeconds) = 0;
};
