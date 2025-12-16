// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleSelect/RoleSelectHelper.h"
#include "Battle/BattleHelper.h"

/**
 *  ロールセレクトヘルパークラス
 * NewObject や new でインスタンスを生成しないでください。
 * 
 */
 // コンストラクタ
RoleSelectHelper::RoleSelectHelper()
{
}

// デストラクタ
RoleSelectHelper::~RoleSelectHelper()
{
}


// 添え字より座標を算出
bool RoleSelectHelper::CalcPosition(int* OutX, int* OutY, int Num) const
{
    if (Num < 0 || Num >= (ROLE_SELECT_WIDTH * ROLE_SELECT_DEPTH))
    {
        //  範囲外
        *OutX = -1;
        *OutY = -1;
        return false;
    }

    *OutX = Num % ROLE_SELECT_WIDTH;
    *OutY = Num / ROLE_SELECT_WIDTH;
    return true;
}


FVector RoleSelectHelper::Calc3DLocation(int X, int Y) const
{
    FVector Location;

    Location.X = (ROLE_SELECT_WIDTH - 1 - X) * BATTLE_FILED_BLOCK_SIZE - BATTLE_FILED_BLOCK_SIZE; // X座標を計算
    Location.Y = (ROLE_SELECT_DEPTH - 1 - Y) * BATTLE_FILED_BLOCK_SIZE - BATTLE_FILED_BLOCK_SIZE * 0.5f; // Y座標を計算
    Location.Z = 0.0f;
    return Location;
}


