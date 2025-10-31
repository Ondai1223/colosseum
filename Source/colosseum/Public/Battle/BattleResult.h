// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Battle/Interface/BattleResultInterface.h"
#include "BattleResult.generated.h"

class ABattleGameMode;

UCLASS()
class COLOSSEUM_API ABattleResult : public APawn, public IBattleResultInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABattleResult();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


    // IBattleResultInterface‚ÌÀ‘•(Å‰‚ÉŒÄ‚Î‚ê‚é)
    virtual void BeginResultState(ABattleGameMode* GameMode) override;

    // IBattleResultInterface‚ÌÀ‘•(–ˆƒtƒŒ[ƒ€ŒÄ‚Î‚ê‚é)
    virtual bool TickResultState(ABattleGameMode* GameMode, float DeltaSeconds) override;


};
