// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Battle/Interface/TurnDecisionInterface.h"
#include "BattleTurnDecision.generated.h"


class ABattleGameMode;

/**
 * 先制後攻の決定処理
 */
UCLASS()
class COLOSSEUM_API ABattleTurnDecision : public APawn, public ITurnDecisionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABattleTurnDecision();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


    // ITurnDecisionInterfaceの実装
    virtual void BeginTurnDecisionState(ABattleGameMode* GameMode) override;

    // 先制後攻の決定処理
    virtual bool TickTurnDecisionState(ABattleGameMode* GameMode, float DeltaSeconds) override;

private:
    FVector BattleCameraLookAtEyeNormal = FVector(0.0f,0.0f,1.0f);
    FQuat BattleCameraQuatStart = FQuat::Identity; // カメラの注視位置の回転
    FQuat BattleCameraQuatEnd = FQuat::Identity; // カメラの注視位置の回転
    float BattleCameraQuatLerp = 0.0f; // カメラの注視位置の補間値
    float BattleCameraSlerpTime = 0.5f; // カメラの注視位置のスラー時間
    float DecisionTime = 2.0f; // 決定までの時間
    float CameraDistance = 0.0f; // カメラの距離
};
