// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle/BattleHelper.h"
#include "Blueprint/UserWidget.h"

BattleHelper::BattleHelper()
{
}

BattleHelper::~BattleHelper()
{
}

void BattleHelper::CalcStartLocationToGameLocation(int* OutX, int* OutY, int StartX, int StartY, EUnitTeamID Team) const
{
    if (Team == EUnitTeamID::EUTID_Team1)
    {
        *OutX = StartX;
        *OutY = (GAME_LOCATION_DEPTH / 2 - 1) - StartY;
    }
    else
    {
        *OutX = GAME_LOCATION_WIDTH - 1 - StartX; // 反転
        *OutY = StartY + GAME_LOCATION_DEPTH / 2; // 反転
    }
}

//  パネル番号の計算
int BattleHelper::CalcPanelNum(int X, int Y) const
{
    if (X < 0 || X >= GAME_LOCATION_WIDTH || Y < 0 || Y >= GAME_LOCATION_DEPTH) {
        //  範囲外
        return -1;
    }
    int Num = X + Y * GAME_LOCATION_WIDTH;


    if (Num >= (GAME_LOCATION_WIDTH * GAME_LOCATION_DEPTH))
    {
        return -1;
    }

    return Num;
}


FVector BattleHelper::CalcPanelLocation(int X, int Y) const
{
    FVector Location;

    Location.Y = (GAME_LOCATION_WIDTH - 1 - X) * BATTLE_FILED_BLOCK_SIZE - BATTLE_FILED_BLOCK_SIZE; // X座標を計算
    Location.X = Y * BATTLE_FILED_BLOCK_SIZE - BATTLE_FILED_DEPTH * 0.5f + BATTLE_FILED_BLOCK_SIZE * 0.5f; // Y座標を計算
    Location.Z = 0.0f;
    return Location;
}

void BattleHelper::CalcPanelPosition(int* X, int* Y, int Num)const
{
    *X = Num % GAME_LOCATION_WIDTH;
    *Y = Num / GAME_LOCATION_WIDTH;
}


