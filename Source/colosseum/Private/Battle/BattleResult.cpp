// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/BattleResult.h"
#include "Battle/BattleGameMode.h"

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

// IBattleResultInterface‚ÌÀ‘•(Å‰‚ÉŒÄ‚Î‚ê‚é)
void ABattleResult::BeginResultState(ABattleGameMode* GameMode)
{
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
        UE_LOG(LogTemp, Warning, TEXT("í“¬’†"));
        break;
    }
}

// IBattleResultInterface‚ÌÀ‘•(–ˆƒtƒŒ[ƒ€ŒÄ‚Î‚ê‚é)
bool ABattleResult::TickResultState(ABattleGameMode* GameMode, float DeltaSeconds)
{
    return true;
}
