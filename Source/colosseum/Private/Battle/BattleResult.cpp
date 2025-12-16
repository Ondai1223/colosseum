// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/BattleResult.h"
#include "Battle/BattleResultDisplay.h"
#include "Battle/BattleGameMode.h"
#include "Battle/BattleHelper.h"


#define BATTLE_RESULT_DISPLAY TEXT("/Game/Battle/Blueprints/BP_BattleResultDisplay.BP_BattleResultDisplay_C"
// Sets default values
ABattleResult::ABattleResult()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABattleResult::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattleResult::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABattleResult::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// IBattleResultInterfaceの実装(最初に呼ばれる)
void ABattleResult::BeginResultState(ABattleGameMode* GameMode)
{

    BattleHelper helper;

    //  戦闘結果表示アクターの生成
    TSubclassOf<ABattleResultDisplay> subclass = helper.Load<ABattleResultDisplay>(BATTLE_RESULT_DISPLAY));

    if (subclass == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("ABattleResult::BeginResultState: Failed to load BattleResultDisplay class"));
    }
    else
    {
        FVector SpawnLocation = FVector::ZeroVector; // 開始位置を計算
        FRotator SpawnRotation = FRotator::ZeroRotator; // 回転はゼロに設定
        BattleResultDisplay = GetWorld()->SpawnActor<ABattleResultDisplay>(subclass, SpawnLocation, SpawnRotation);
        if (BattleResultDisplay == nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("ABattleResult::BeginResultState: Failed to spawn BattleResultDisplay actor"));
        }
        else
        {
            BattleResultDisplay->SetBattleResultDisplay(GameMode->GetBattleResult());
            BattleResultDisplay->SetTeam1Name(GameMode->Player1TeamName);
            BattleResultDisplay->SetTeam2Name(GameMode->Player2TeamName);
            BattleResultDisplay->BattleResultWidget->OpenBattleResult();
        }
    }






    switch (GameMode->GetBattleResult())
    {
    case EBattleResult::EBR_Player1Win:
        UE_LOG(LogTemp, Warning, TEXT("Player 1 Win!"));
        break;
    case EBattleResult::EBR_Player2Win:
        UE_LOG(LogTemp, Warning, TEXT("Player 2 Win!"));
        break;
    case EBattleResult::EBR_Draw:
        UE_LOG(LogTemp, Warning, TEXT("Draw!"));
        break;
    default:
        UE_LOG(LogTemp, Warning, TEXT("戦闘中"));
        break;
    }
}

// IBattleResultInterfaceの実装(毎フレーム呼ばれる)
bool ABattleResult::TickResultState(ABattleGameMode* GameMode, float DeltaSeconds)
{
    return true;
}
