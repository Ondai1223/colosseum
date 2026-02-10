// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/LineLerp.h"

/**
 * 3D座標線形補間クラス(new や　NewObjectを使わないでください、クラスのメンバとかスタックフレームで使用してください
 */
class COLOSSEUM_API LineLerp3D
{
public:
	LineLerp3D();
	~LineLerp3D();


    // 補間の初期化
    void Initialize(ECurveType InCurveType, EMoveType InMoveType, const FVector& InStartValue, const FVector& InEndValue, float InSpeed);
    // 補間の更新
    void Update(float DeltaTime);
    // 終了したか
    bool IsFinished() const;
    // 補間値の取得
    FVector GetValue() const;

private:
    LineLerp LerpX; // X座標補間
    LineLerp LerpY; //  Y座標補間
    LineLerp LerpZ; // Z座標補間
};
