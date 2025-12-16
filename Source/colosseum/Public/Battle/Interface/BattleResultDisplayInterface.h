// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Battle/BattleGameMode.h"
#include "BattleResultDisplayInterface.generated.h"


/**
 *  勝利条件表示設定インタフェース
 */

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBattleResultDisplayInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COLOSSEUM_API IBattleResultDisplayInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

    //  戦闘結果表示の設定
    virtual void SetBattleResultDisplay(EBattleResult Result) = 0;

    //  戦闘結果表示の取得
    virtual EBattleResult GetBattleResultDisplay() const = 0;


    //  チーム名１の設定
    virtual void SetTeam1Name(const FString& name) = 0;

    //  チーム名１の取得
    virtual const FString& GetTeam1Name() const = 0;


    //  チーム名２の設定
    virtual void SetTeam2Name(const FString& name) = 0;

    //  チーム名２の取得
    virtual const FString& GetTeam2Name() const = 0;

};
