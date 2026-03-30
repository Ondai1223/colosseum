// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleSelect/RoleSelectCursor.h"
#include "NiagaraFunctionLibrary.h"
#include "RoleSelect/RoleSelectHelper.h"

#define ROLE_CURSOR_NAME TEXT("/Game/FixEffect/Cursoul/Ef_Cursoul.Ef_Cursoul")

#define START_POS_X 1
#define START_POS_Y 0

// Sets default values
ARoleSelectCursor::ARoleSelectCursor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    CursorModel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CursorMesh"));

    if (CursorModel)
    {
        RootComponent = CursorModel; // メッシュコンポーネントをルートコンポーネントに設定
    }

}

// Called when the game starts or when spawned
void ARoleSelectCursor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoleSelectCursor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//  ロール選択後配置カーソル
void ARoleSelectCursor::CreateRoleArrangementCursor()
{
    RoleArrangementCursor = LoadObject<UNiagaraSystem>(nullptr, ROLE_CURSOR_NAME);

    if (RoleArrangementCursor)
    {
        // NiagaraComponentを取得
        CursorEffectComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
            RoleArrangementCursor,
            CursorModel,
            NAME_None,
            FVector::ZeroVector,
            FRotator::ZeroRotator,
            FVector(1.7f, 1.7f, 1.0f),
            EAttachLocation::KeepRelativeOffset,
            true,
            ENCPoolMethod::None,
            true,
            true
        );
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load RoleArrangementCursor Niagara System."));
    }
}

void ARoleSelectCursor::SetCursorPosition(int X, int Y)
{

    if (CursorModel)
    {
        RoleSelectHelper    helper;

        FVector location = helper.Calc3DLocation(X, Y);
        CursorModel->SetRelativeLocation(location);
    }

    MoveCursorData.X = X;
    MoveCursorData.Y = Y;
    MoveCursorData.BeforeX = X;
    MoveCursorData.BeforeY = Y;
    MoveCursorData.MoveNowTime = MOVE_CURSOR_TIME;
}

void ARoleSelectCursor::StartMoveCursor(int X, int Y , float MoveTime)
{
    MoveCursorData.BeforeX = MoveCursorData.X;
    MoveCursorData.BeforeY = MoveCursorData.Y;
    MoveCursorData.X = X;
    MoveCursorData.Y = Y;
    MoveCursorData.MoveNowTime = 0.0f;
    MoveCursorData.MoveTime = MoveTime;

}

bool ARoleSelectCursor::MoveCursor(float DeltaTime,FVector* NowLocation)
{

    MoveCursorData.MoveNowTime = FMath::Min(MoveCursorData.MoveNowTime + DeltaTime, MoveCursorData.MoveTime);

    float NowLerp = MoveCursorData.MoveNowTime / MoveCursorData.MoveTime;
    float SinLerp = FMath::Sin(NowLerp * (PI / 2.0f));

    RoleSelectHelper    helper;

    FVector BeforeLocation = helper.Calc3DLocation(MoveCursorData.BeforeX, MoveCursorData.BeforeY);
    FVector ToLocation = helper.Calc3DLocation(MoveCursorData.X, MoveCursorData.Y);

    FVector Result = FMath::Lerp(BeforeLocation, ToLocation, SinLerp);

    if (CursorModel)
    {
        CursorModel->SetRelativeLocation(Result);
    }

    if (NowLocation)
    {
        *NowLocation = Result;
    }

    bool ResultFlag = MoveCursorData.MoveNowTime <  MoveCursorData.MoveTime;

    if (ResultFlag == false)
    {
        //  移動完了
        MoveCursorData.BeforeX = MoveCursorData.X;
        MoveCursorData.BeforeY = MoveCursorData.Y;
    }

    return ResultFlag;;
}


