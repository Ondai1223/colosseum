// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Battle/BattleMain.h"
#include "BattleMainVsNpc.generated.h"

/**
 * プレーヤーVSNPC
 */
UCLASS()
class COLOSSEUM_API ABattleMainVsNpc : public ABattleMain
{
	GENERATED_BODY()


public:

    // バトル開始処理
    virtual void BeginBattleState(ABattleGameMode* GameMode) override;

    // バトルループ処理
    virtual ETickBattleState TickBattleState(ABattleGameMode* GameMode, float DeltaSeconds) override;

public:

    //  バトルコマンドを開く
    virtual void BeginBattleCommand(ABattleGameMode* GameMode);
    //  バトルコマンドを閉じる
    virtual void EndBattleCommand(ABattleGameMode* GameMode);

    void SyncCursor();


    // NPCユニットの選択
    TObjectPtr<AUnitBattleParameter> SelectNpcUnit(ABattleGameMode* GameMode);


private:
    UPROPERTY(Transient)
    TArray<TObjectPtr<AUnitBattleParameter>>    AttackTargets;

    FGameLocation   MoveToLocation; //  移動先
    float   WaitTime = 0.0f;    //  ウエイト秒数
    bool    BeginFlag = false;  //  開始フラグ
};
