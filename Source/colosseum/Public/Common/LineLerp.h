// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"



UENUM(BlueprintType)
enum class EMoveType : uint8
{
    Normal      UMETA(DisplayName = "通常補間"),
    Reverse     UMETA(DisplayName = "逆方向補間"),
};

UENUM(BlueprintType)
enum class ECurveType : uint8
{
    Linear      UMETA(DisplayName = "線形"),
    Sign        UMETA(DisplayName = "サインカーブ"),
    SlowFast    UMETA(DisplayName = "遅くから早くへ"),
    FastSlow    UMETA(DisplayName = "早くから遅くへ"),
};

/**
 *  線形補間クラス(new や NewObject またはスポーンさせないでください。クラスのメンバかスタックフレーム内の処理で使ってください)
 */
class COLOSSEUM_API LineLerp
{
public:
	LineLerp();
	~LineLerp();

    // 補間の初期化
    void Initialize(ECurveType InCurveType, EMoveType InMoveType, float InStartValue, float InEndValue, float InSpeed);
    // 補間の更新
    void Update(float DeltaTime);
    // 終了したか
    bool IsFinished() const;

    // 補間値の取得
    float GetValue() const;

private:
    ECurveType  CurveType = ECurveType::Linear;   // 補間曲線タイプ
    EMoveType   MoveType = EMoveType::Normal;       // 移動タイプ
    float      StartValue; // 開始値
    float      EndValue;   // 終了値
    float      Lerp;        //  補間値
    float      Speed;      // 補間速度(秒数)
};
