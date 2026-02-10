// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/LineLerp.h"


#define START_SIGN_IN   0.0f
#define END_SIGN_OUT     90.0f


/**
 *  線形補間クラス
 */


LineLerp::LineLerp()
{
}

LineLerp::~LineLerp()
{
}

//  補間の初期化
void LineLerp::Initialize(ECurveType InCurveType, EMoveType InMoveType, float InStartValue, float InEndValue, float InSpeed)
{
    CurveType = InCurveType;
    MoveType = InMoveType;
    StartValue = InStartValue;
    EndValue = InEndValue;
    Speed = InSpeed;

    if (MoveType == EMoveType::Normal)
    {
        // 通常補間の場合、開始値で初期化
        Lerp = 0.0f;
    }
    else
    {
        // 逆方向補間の場合、終了値で初期化
        Lerp = 1.0f;
    }
}


// 補間の更新
void LineLerp::Update(float DeltaTime)
{
    // 補間速度に基づいて補間値を更新
    float DeltaLerp = DeltaTime / Speed;
    if (MoveType == EMoveType::Normal)
    {   //  通常補間
        Lerp += DeltaLerp;
        if (Lerp > 1.0f)
        {
            Lerp = 1.0f;
        }
    }
    else // EMoveType::Reverse
    {
        // 逆方向補間
        Lerp -= DeltaLerp;
        if (Lerp < 0.0f)
        {
            Lerp = 0.0f;
        }
    }
}

// 終了したか
bool LineLerp::IsFinished() const
{
    if (MoveType == EMoveType::Normal)
    {
        return Lerp >= 1.0f;
    }
    return Lerp <= 0.0f;
}

// 補間値の取得
float LineLerp::GetValue() const
{
    switch(CurveType)
    {
    case ECurveType::Linear:
        //  線形補間
        return FMath::Lerp(StartValue, EndValue, Lerp);
    case ECurveType::Sign:
        // サインカーブ補間
        return FMath::Lerp(StartValue, EndValue, FMath::Sin(FMath::DegreesToRadians(FMath::Lerp(START_SIGN_IN , END_SIGN_OUT, Lerp))));
        //  遅いスピードで入って早くなって抜ける
    case ECurveType::SlowFast:
        return FMath::Lerp(StartValue, EndValue, FMath::Sin(FMath::DegreesToRadians(FMath::Lerp(START_SIGN_IN, END_SIGN_OUT * 0.5f + START_SIGN_IN, Lerp))));
        //  早いスピードで入って遅くなる
    case ECurveType::FastSlow:
    default:
        return FMath::Lerp(StartValue, EndValue, FMath::Sin(FMath::DegreesToRadians(FMath::Lerp(START_SIGN_IN + END_SIGN_OUT * 0.5f, END_SIGN_OUT,Lerp))));
    }
}
