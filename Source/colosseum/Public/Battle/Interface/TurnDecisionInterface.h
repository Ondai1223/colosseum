// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TurnDecisionInterface.generated.h"




//  #define ENABLE_TRUN_DECISION_INTERFACE_GAME_MODE_PROXY    //  ゲームモードプロキシを有効にするかどうか

#ifndef ENABLE_TRUN_DECISION_INTERFACE_GAME_MODE_PROXY
class ABattleGameMode;
typedef ABattleGameMode ATurnDecisionGameModeProxy;
#else
class ABattleGameModeProxy;
typedef ABattleGameModeProxy ATurnDecisionGameModeProxy;
#endif  //


// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UTurnDecisionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 最初のターン開始決定インタフェース
 */
class COLOSSEUM_API ITurnDecisionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    // ターン開始決定イベントの開始
    virtual void BeginTurnDecisionState(ATurnDecisionGameModeProxy* GameMode) = 0;

    // ターン開始決定イベントの表示
    virtual bool TickTurnDecisionState(ATurnDecisionGameModeProxy* GameMode, float DeltaSeconds) = 0;
};


