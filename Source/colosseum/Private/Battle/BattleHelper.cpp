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
    float CenterOffset = -BATTLE_FILED_OFFSET_SIZE;
    if (Y >= (GAME_LOCATION_DEPTH / 2))
    {
        // 1ブロック分の空間を追加
        CenterOffset = BATTLE_FILED_OFFSET_SIZE;
    }
    Location.Y = (GAME_LOCATION_WIDTH - 1 - X) * BATTLE_FILED_BLOCK_SIZE - BATTLE_FILED_BLOCK_SIZE; // X座標を計算
    Location.X = Y * BATTLE_FILED_BLOCK_SIZE + CenterOffset - BATTLE_FILED_DEPTH * 0.5f + BATTLE_FILED_BLOCK_SIZE * 0.5f; // Y座標を計算
    Location.Z = 0.0f;
    return Location;
}

void BattleHelper::CalcPanelPosition(int* X, int* Y, int Num)const
{
    *X = Num % GAME_LOCATION_WIDTH;
    *Y = Num / GAME_LOCATION_WIDTH;
}

bool BattleHelper::CalcLookAtRotation(FQuat* pOut , const FVector2D& From, const FVector2D& To ) const
{
    //  ベクトル算出
    FVector2D vec = To - From;

    if (vec.Length() < FLT_EPSILON)
    {   //  計算できない（方向計算ができない
        return false;
    }
    //  正規化
    vec.Normalize();


    FQuat Result(FVector(0.0f, 0.0f, 1.0f), FMath::Atan2(-vec.Y, -vec.X));
    *pOut = Result;
    return true;
}


//  攻撃位置の計算
// AttackX,AttackY : 攻撃対象位置
// CenterX ,CenterY : 攻撃者位置
FVector BattleHelper::CalcAttackActionPosition(int AttackX, int AttackY, int CenterX, int CenterY) const
{

    if (CenterY == AttackY)
    {   // 横のユニットに攻撃（味方に攻撃）
        return CalcPanelLocation(CenterX, CenterY);
    }

    //  差分を算出
    int SubX = AttackX - CenterX;
    int SubY = AttackY - CenterY;

    FVector ResultLocation;
    ResultLocation = CalcPanelLocation(AttackX, AttackY);

    if (CenterY < (GAME_LOCATION_DEPTH / 2))
    {

        if (SubY > 0)
        {
            //  前に攻撃
            ResultLocation.X -= BATTLE_FILED_BLOCK_SIZE;

        }
        else
        {
            //  後ろに攻撃
            ResultLocation.X += BATTLE_FILED_BLOCK_SIZE;
        }
    }
    else
    {
        if (SubY > 0)
        {
            //  前に攻撃
            ResultLocation.X -= BATTLE_FILED_BLOCK_SIZE;

        }
        else
        {
            //  後ろに攻撃
            ResultLocation.X += BATTLE_FILED_BLOCK_SIZE;
        }
    }
    return ResultLocation;
}


// 攻撃するユニットのカメラ位置を算出する
FVector BattleHelper::CalcAttackAttackStartCameraPosition(int ActionStartX, int ActionStartY) const
{
    FVector BaseLocation = CalcPanelLocation(ActionStartX, ActionStartY);
    FVector Vector;

    if (ActionStartY < (GAME_LOCATION_DEPTH / 2))
    {
        Vector = FVector(ATTACK_CAMERA_OFFSET_X,ATTACK_CAMERA_OFFSET_Y, 0.0f);
    }
    else
    {
        Vector = FVector(-ATTACK_CAMERA_OFFSET_X, -ATTACK_CAMERA_OFFSET_Y, 0.0f);
    }
    BaseLocation.Z = ATTACK_CAMERA_OFFSET_Z;

    return BaseLocation + Vector;
}
