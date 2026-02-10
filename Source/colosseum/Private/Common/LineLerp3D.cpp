// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/LineLerp3D.h"


/**
 * 3D座標線形補間クラス(new や　NewObjectを使わないでください、クラスのメンバとかスタックフレームで使用してください
 */

LineLerp3D::LineLerp3D()
{
}

LineLerp3D::~LineLerp3D()
{
}

//  補間の初期化
void LineLerp3D::Initialize(ECurveType InCurveType, EMoveType InMoveType, const FVector& InStartValue, const FVector& InEndValue, float InSpeed)
{
    LerpX.Initialize(InCurveType, InMoveType, InStartValue.X, InEndValue.X, InSpeed);
    LerpY.Initialize(InCurveType, InMoveType, InStartValue.Y, InEndValue.Y, InSpeed);
    LerpZ.Initialize(InCurveType, InMoveType, InStartValue.Z, InEndValue.Z, InSpeed);
}

// 補間の更新
void LineLerp3D::Update(float DeltaTime)
{
    LerpX.Update(DeltaTime);
    LerpY.Update(DeltaTime);
    LerpZ.Update(DeltaTime);
}

// 終了したか
bool LineLerp3D::IsFinished() const
{
    return LerpX.IsFinished() && LerpY.IsFinished() && LerpZ.IsFinished();
}

// 補間値の取得
FVector LineLerp3D::GetValue() const
{
    return FVector(LerpX.GetValue(), LerpY.GetValue(), LerpZ.GetValue());
}
