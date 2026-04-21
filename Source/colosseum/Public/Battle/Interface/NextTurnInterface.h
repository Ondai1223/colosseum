// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NextTurnInterface.generated.h"


//  #define ENABLE_NEXT_TURN_INTERFACE_GAME_MODE_PROXY    //  ゲームモードプロキシを有効にするかどうか

#ifndef ENABLE_NEXT_TURN_INTERFACE_GAME_MODE_PROXY
class ABattleGameMode;
typedef ABattleGameMode ANextTurnGameModeProxy;
#else
class ABattleGameModeProxy;
typedef ABattleGameModeProxy ANextTurnGameModeProxy;
#endif  //
// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UNextTurnInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * ターン切り替えインタフェース
 */
class COLOSSEUM_API INextTurnInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

    // 次のターンの開始イベント
    virtual void BeginNextTurnState(ANextTurnGameModeProxy* GameMode) = 0;

    // 次のターンの状態を表示イベント
    virtual bool TickNextTurnState(ANextTurnGameModeProxy* GameMode, float DeltaSeconds) = 0;

};
