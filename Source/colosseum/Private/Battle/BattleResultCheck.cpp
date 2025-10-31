// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/BattleResultCheck.h"
#include "Battle/BattleGameMode.h"

// 戦闘結果チェック
void UBattleResultCheck::CheckBattleResult(ABattleGameMode* GameMode)
{
    //  現状はとりあえず、結果は出さず戦闘続行
    //  以下を修正してください。
    //  GameMode に色々判定関数を用意します。

    if (GameMode->GetBattleResult() != EBattleResult::EBR_None) {
        //  既に結果が出ている場合は何もしない(負けを認めた場合など
        return;
    }

    //  まだ結果が出ていない場合は、勝敗を判定する
    bool bPlayer1AllDead = GameMode->IsPlayer1AllDead();    //  プレイヤー1が全滅しているか？
    bool bPlayer2AllDead = GameMode->IsPlayer2AllDead();    //  プレイヤー2が全滅しているか？

    //  基本の勝敗判定
    if (bPlayer1AllDead && bPlayer2AllDead) {
        //  両者全滅なら引き分け
        GameMode->SetBattleResult(EBattleResult::EBR_Draw);
        return;
    }
    else if (bPlayer1AllDead) {
        //  プレイヤー1が全滅ならプレイヤー2の勝利
        GameMode->SetBattleResult(EBattleResult::EBR_Player2Win);
        return;
    }
    else if (bPlayer2AllDead) {
        //  プレイヤー2が全滅ならプレイヤー1の勝利
        GameMode->SetBattleResult(EBattleResult::EBR_Player1Win);
        return;
    }

    // それ以外、決着がつかない、詰みの判定


    //  続行
    GameMode->SetBattleResult(EBattleResult::EBR_None);
}

