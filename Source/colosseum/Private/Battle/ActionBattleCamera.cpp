// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/ActionBattleCamera.h"
#include "Battle/BattleGameMode.h"

ActionBattleCamera::ActionBattleCamera()
{
}

ActionBattleCamera::~ActionBattleCamera()
{
}

void ActionBattleCamera::Initialize(ABattleGameMode* GameMode, const FVector& LookAt, float Zoom, float Secounds)
{
    BattleGameMode = GameMode;

    // 既存のカメラ位置と注視点を取得
    FromEyeLocation = GameMode->BattleCameraEyeLocation;
    FromLookAtLocation = GameMode->BattleCameraLookAtLocation;
    FromZoom = GameMode->BattleCameraZoom;
    LerpTime = Secounds;
    // 目標のカメラ位置と注視点を設定
    ToLookAtLocation = LookAt;
    ToEyeLocation = ToLookAtLocation + FromEyeLocation - FromLookAtLocation;
    ToZoom = Zoom;
    Lerp = 0.0f; // 補間の進行度を初期化
}

bool ActionBattleCamera::RunNormal(float DeltaSeconds)
{
    Lerp = FMath::Min(1.0f, Lerp + DeltaSeconds / LerpTime);   // 補間の進行度を計算

    SetLerp(Lerp); // 補間の進行度に基づいてカメラの位置と注視点を更新
    if (Lerp >= 1.0f)
    {
        return true; // 補間が完了
    }
    return false; //まだ実行中

}

bool ActionBattleCamera::RunReverse(float DeltaSeconds)
{
    Lerp = FMath::Max(0.0f, Lerp - DeltaSeconds / LerpTime);   // 補間の進行度を計算

    SetLerp(Lerp); // 補間の進行度に基づいてカメラの位置と注視点を更新
    if (Lerp <= 0.0f)
    {
        return true; // 補間が完了
    }
    return false; //まだ実行中

}


void ActionBattleCamera::SetLerp(float NowLerp)
{
    float SinLerp = FMath::Sin(FMath::DegreesToRadians(90.0f) * NowLerp); // 0から1の間でSin関数を使用して滑らかな補間を実現

    FVector NewLookAtLocation = FMath::Lerp(FromLookAtLocation, ToLookAtLocation, SinLerp); // 注視点の補間
    FVector NewEyeLocation = FMath::Lerp(FromEyeLocation, ToEyeLocation, SinLerp); // カメラ位置の補間
    float NewZoom = FMath::Lerp(FromZoom, ToZoom, SinLerp); // ズーム値の補間
    BattleGameMode->SetLookAtBattleCamera(NewLookAtLocation); // カメラの注視点を設定
    BattleGameMode->SetEyeBattleCamera(NewEyeLocation); // カメラの位置を設定
    BattleGameMode->SetZoomBattleCamera(NewZoom); // カメラのズーム値を設定
    BattleGameMode->CalcBattleCamera(); // カメラの計算を実行
}

