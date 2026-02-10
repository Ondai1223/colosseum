// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/BattleAttackCamera.h"


/**
 *  カメラコントロールクラス
 */



// Sets default values
ABattleAttackCamera::ABattleAttackCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABattleAttackCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattleAttackCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABattleAttackCamera::Initialize(
    const FVector& InStartEye,  //  目線開始位置
    const FVector& InEndEye,    //  目線終了位置
    const FVector& InStartLookAt,   //  注視点開始位置
    const FVector& InEndLookAt, //  注視点終了位置
    float InSpeed,   //  補間速度(秒数)
    EMoveType InMoveType,   //  移動タイプ
    ECurveType InCurveType //  補間曲線タイプ
)
{
    LerpEye.Initialize(InCurveType, InMoveType, InStartEye, InEndEye, InSpeed);
    LerpLookAt.Initialize(InCurveType, InMoveType, InStartLookAt, InEndLookAt, InSpeed);

    ActionType = ECameraAction::Run;
}


void ABattleAttackCamera::Update(float DeltaTime)
{

    if (ActionType == ECameraAction::Stop)
    {
        return;
    }


    if (!CameraActor)
    {   //  カメラの設定がされていない
        return;
    }

    if (IsFinished())
    {
        ActionType = ECameraAction::Stop;
        return;
    }

    LerpEye.Update(DeltaTime);
    LerpLookAt.Update(DeltaTime);
    if (CameraActor)
    {
        FVector EyePos = LerpEye.GetValue();
        FVector LookAtPos = LerpLookAt.GetValue();

        //  カメラのベクトルを算出
        FVector Vec = LookAtPos - EyePos;
        Vec.Normalize();

        //  カメラの回転を算出
        FRotator Rot = Vec.Rotation();

        CameraActor->SetActorLocation(EyePos);
        CameraActor->SetActorRotation(Rot);
    }
}


bool ABattleAttackCamera::IsFinished()const
{
    return LerpEye.IsFinished() && LerpLookAt.IsFinished();
}


// 現在の注視点位置の取得
FVector ABattleAttackCamera::GetCurrentEyeLocation() const
{
    return LerpEye.GetValue();
}

// 現在の注視点位置の取得
FVector ABattleAttackCamera::GetCurrentLookAtLocation() const
{
    return LerpLookAt.GetValue();
}
