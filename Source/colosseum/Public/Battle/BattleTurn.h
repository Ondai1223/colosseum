// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Battle/Interface/NextTurnInterface.h"
#include "BattleTurn.generated.h"
class ABattleGameMode;


/**
 * 次のターン開始の処理
 */
UCLASS()
class COLOSSEUM_API ABattleTurn : public APawn, public INextTurnInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABattleTurn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
    // INextTurnInterfaceの実装
    // 次のターン開始イベント
    virtual void BeginNextTurnState(ABattleGameMode* GameMode) override;

    // 次のターン状態の表示イベント
    virtual bool TickNextTurnState(ABattleGameMode* GameMode, float DeltaSeconds) override;


private:

    bool SkipTurnCameraMove = false; // ターンスキップフラグ

    FVector BattleCameraAtToEyeVector; // カメラの注視位置から目標位置へのベクトル

    FQuat BattleCameraQuatStart = FQuat::Identity; // カメラの注視位置の回転
    FQuat BattleCameraQuatEnd = FQuat::Identity; // カメラの注視位置の回転

    float BattleCameraLerp = 0.0f;
    float BattleCameraMoveLerpTime = 0.5f;

};
