// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle/BattleTurn.h"
#include "Battle/BattleGameMode.h"

// Sets default values
ABattleTurn::ABattleTurn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABattleTurn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattleTurn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABattleTurn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// 次のターン開始イベント
void ABattleTurn::BeginNextTurnState(ABattleGameMode* GameMode)
{
    EBattleTurn turn = GameMode->GetCurrentBattleTurn();
    FVector DirVector = FVector(0.0f, 0.0f, 1.0f);

    if (turn == EBattleTurn::EBT_Player1)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player1's turn!"));
        // プレイヤー1のターン開始処理
        // ここにプレイヤー1のターン開始ロジックを追加
        GameMode->InGameWidget->EnableTurnDisplay(GameMode);
        DirVector = FVector(-1.0f, 0.0f, 0.0f); // プレイヤー1の方向ベクトル
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player2's turn!"));
        // プレイヤー2のターン開始処理
        // ここにプレイヤー2のターン開始ロジックを追加
        GameMode->InGameWidget->EnableTurnDisplay(GameMode);
        DirVector = FVector(1.0f, 0.0f, 0.0f); // プレイヤー2の方向ベクトル
    }

    BattleCameraQuatEnd = FQuat::MakeFromRotationVector(FVector(0.0f, 0.0f, FMath::DegreesToRadians(180.0f)));

    FVector CameraVector = GameMode->BattleCameraEyeLocation - GameMode->BattleCameraLookAtLocation;

    double dot = CameraVector.Dot(DirVector);

    // カメラの向きが一致している場合、何もしないフラグをたてて、ターンの表示を行う
    SkipTurnCameraMove = dot > 0.0f;

    if (SkipTurnCameraMove == false) {
        //  カメラ移動初期化
        // カメラの注視位置と目標位置のベクトルを計算
        BattleCameraAtToEyeVector = GameMode->BattleCameraEyeLocation - GameMode->BattleCameraLookAtLocation;
        BattleCameraLerp = 0.0f; // カメラの補間値を初期化
    }
}

// 次のターン状態の表示イベント
bool ABattleTurn::TickNextTurnState(ABattleGameMode* GameMode, float DeltaSeconds)
{
    if (SkipTurnCameraMove == false) {
        // カメラ移動の処理
        BattleCameraLerp += DeltaSeconds / BattleCameraMoveLerpTime; // 補間値を更新
        bool result = false;

        if (BattleCameraLerp >= 1.0f) {
            BattleCameraLerp = 1.0f; // 補間値を1.0fに制限
            result = true; // 補間が完了した場合、trueを返す
        }

        FQuat CurrentQuat = FQuat::Slerp(BattleCameraQuatStart, BattleCameraQuatEnd, std::sin(FMath::DegreesToRadians(90.0f) * BattleCameraLerp));
        FMatrix NowMatrix = CurrentQuat.ToMatrix();
        FVector4 AtToEyeVector = NowMatrix.TransformVector(BattleCameraAtToEyeVector);
        GameMode->SetEyeBattleCamera(GameMode->BattleCameraLookAtLocation + AtToEyeVector); // カメラの位置を更新
        GameMode->CalcBattleCamera(); // カメラの計算を実行
        if (result == true)
        {
            GameMode->InGameWidget->DisenableTurnDisplay();
        }
        return result;
    }

    GameMode->InGameWidget->DisenableTurnDisplay();

    // ターンの表示処理
    return true;
}
