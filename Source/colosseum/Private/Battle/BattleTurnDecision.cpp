// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle/BattleTurnDecision.h"
#include "Battle/BattleGameMode.h"

// Sets default values
ABattleTurnDecision::ABattleTurnDecision()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABattleTurnDecision::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattleTurnDecision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABattleTurnDecision::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// ITurnDecisionInterfaceの実装
void ABattleTurnDecision::BeginTurnDecisionState(ABattleGameMode* GameMode)
{
//    GameMode->SetStartTurnDecisionState(EBattleTurn::EBT_Player1); // 最初はプレイヤー1のターンに設定
    EBattleTurn DecidedTurn = FMath::RandBool() ? EBattleTurn::EBT_Player1 : EBattleTurn::EBT_Player2;
    GameMode->SetStartTurnDecisionState(DecidedTurn); // 決定したターンを設定

}

// 先制後攻の決定処理
bool ABattleTurnDecision::TickTurnDecisionState(ABattleGameMode* GameMode, float DeltaSeconds)
{
    // ここに先制後攻の決定ロジックを実装

    DecisionTime = FMath::Max(0.0f, DecisionTime - DeltaSeconds); // 決定時間を減少させる
    if (DecisionTime <= 0.0f)
    {
        GameMode->InGameWidget->EnableTurnDisplay(GameMode);
        // ちょっと待った。
        bool result = false;
        if (CameraDistance <= 0.0f)
        {
            BattleCameraLookAtEyeNormal = GameMode->BattleCameraEyeLocation - GameMode->BattleCameraLookAtLocation;
            CameraDistance = BattleCameraLookAtEyeNormal.Size(); // カメラの距離を計算
            BattleCameraLookAtEyeNormal.Normalize();
            BattleCameraQuatStart = FQuat::MakeFromRotationVector(FVector(0.0f, 0.0f, 0.0f));
            BattleCameraQuatEnd = FQuat::MakeFromRotationVector(FVector(0.0f, 0.0f, (GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player1) ? FMath::DegreesToRadians(90.0f): FMath::DegreesToRadians(-90.0f)));
            GameMode->SetLookAtBattleCamera(FVector(0.0f, 0.0f, 0.0f)); // カメラの注視位置を設定
            GameMode->SetEyeBattleCamera(GameMode->BattleCameraLookAtLocation + BattleCameraLookAtEyeNormal * CameraDistance); // カメラの位置を設定
            GameMode->SetZoomBattleCamera(0.0f);
            GameMode->CalcBattleCamera(); // カメラの計算を実行
        }
        else
        {
            BattleCameraQuatLerp += DeltaSeconds / BattleCameraSlerpTime; // 補間値を更新
            if (BattleCameraQuatLerp > 1.0f)
            {
                BattleCameraQuatLerp = 1.0f; // 補間値を1.0fに制限
                result = true; // 決定が完了したことを示す
            }
            // カメラの注視位置の回転を補間
            FQuat CurrentQuat = FQuat::Slerp(BattleCameraQuatStart, BattleCameraQuatEnd, std::sin(FMath::DegreesToRadians(90.0f) * BattleCameraQuatLerp));
            FMatrix NowMatrix = CurrentQuat.ToMatrix();
            FVector4 NormalVector = NowMatrix.TransformVector(BattleCameraLookAtEyeNormal * CameraDistance);
            FVector EyeLocation = FVector(NormalVector.X, NormalVector.Y, NormalVector.Z);
            GameMode->SetEyeBattleCamera(EyeLocation); // カメラの位置を更新
            GameMode->CalcBattleCamera(); // カメラの計算を実行
        }
        return result; // 決定が完了したことを示す
    }
    return false;
}
