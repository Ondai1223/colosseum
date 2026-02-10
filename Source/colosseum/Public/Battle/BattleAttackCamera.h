// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Battle/BattleHelper.h"
#include "Common/LineLerp3D.h"
#include "Camera/CameraActor.h"
#include "BattleAttackCamera.generated.h"




UENUM(BlueprintType)
enum class ECameraAction : uint8
{
    Stop      UMETA(DisplayName = "停止状態"),
    Run       UMETA(DisplayName = "実行状態"),
};


/**
 *  カメラコントロールクラス
 */
UCLASS()
class COLOSSEUM_API ABattleAttackCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleAttackCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    //　初期化
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void Initialize(
        const FVector& InStartEye,  //  目線開始位置
        const FVector& InEndEye,    //  目線終了位置
        const FVector& InStartLookAt,   //  注視点開始位置
        const FVector& InEndLookAt, //  注視点終了位置
        float InSpeed = 1.0f,   //  補間速度(秒数)
        EMoveType InMoveType = EMoveType::Normal,   //  移動タイプ
        ECurveType InCurveType = ECurveType::Sign //  補間曲線タイプ
    );

    // 更新
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void Update(float DeltaTime);

    // 終了したか
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    bool IsFinished() const;

    // 現在の注視点位置の取得
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    FVector GetCurrentEyeLocation() const;

    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    FVector GetCurrentLookAtLocation() const;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TObjectPtr<ACameraActor> CameraActor; // カメラアクターの参照

private:
    LineLerp3D LerpEye;   // 目線補間
    LineLerp3D LerpLookAt; // 注視点補間
    ECameraAction   ActionType = ECameraAction::Stop; // カメラアクションタイプ

};
