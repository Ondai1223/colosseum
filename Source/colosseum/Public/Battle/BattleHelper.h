// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit/UnitTeamID.h"

#define GAME_LOCATION_WIDTH 3 // ゲームの座標幅
#define GAME_LOCATION_DEPTH 4 // ゲームの座標奥行き

#define BATTLE_FILED_BLOCK_SIZE  (100.0f)
#define BATTLE_FILED_WIDTH (GAME_LOCATION_WIDTH * BATTLE_FILED_BLOCK_SIZE) // 戦闘フィールドの幅
#define BATTLE_FILED_DEPTH (GAME_LOCATION_DEPTH * BATTLE_FILED_BLOCK_SIZE) // 戦闘フィールドの奥行き

#define BATTLE_LOAD_SYNC    //  同期をとってロード

/**
 * ヘルパークラス（このクラスはNewObject や new で生成しないこと）
 */
class COLOSSEUM_API BattleHelper
{
public:
	BattleHelper();
	~BattleHelper();

    //  チームのスタート位置からゲームの座標に変換
    void CalcStartLocationToGameLocation(int* OutX, int* OutY, int StartX, int StartY, EUnitTeamID Team) const;


    //  パネル番号の計算
    int CalcPanelNum(int X, int Y) const;

    //  パネル座標からロケーション座標を算出
    FVector CalcPanelLocation(int X, int Y) const;


    //  添え字より座標を算出
    void CalcPanelPosition(int* X, int* Y,int Num)const;


    //  ロード(条件付きコンパイルで非同期にも出るようにする)
    template <class T>
    TSubclassOf<T> Load(const FString& FileName) const
    {
#ifdef BATTLE_LOAD_SYNC
        FSoftObjectPath Path(FileName);
        TSubclassOf<T> A = TSoftClassPtr<T>(Path).LoadSynchronous();
        return A;
#else
        return nullptr;
#endif
    }


};
