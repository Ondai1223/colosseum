// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/BattleResultDisplay.h"
/**
 *  戦闘結果表示アクター
 */

// Sets default values
ABattleResultDisplay::ABattleResultDisplay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABattleResultDisplay::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattleResultDisplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//  戦闘結果表示の設定
UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
void ABattleResultDisplay::SetBattleResultDisplay(EBattleResult Result)
{
    BattleResultWidget->BattleResult = Result;
}

//  戦闘結果表示の取得
UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
EBattleResult ABattleResultDisplay::GetBattleResultDisplay() const
{
    return BattleResultWidget->BattleResult;
}

//  チーム名１の設定
void ABattleResultDisplay::SetTeam1Name(const FString& name)
{
    BattleResultWidget->Player1TeamName = name;
}

//  チーム名１の取得
const FString& ABattleResultDisplay::GetTeam1Name() const
{
    return BattleResultWidget->Player1TeamName;
}

//  チーム名２の設定
void ABattleResultDisplay::SetTeam2Name(const FString& name)
{
    BattleResultWidget->Player2TeamName = name;
}

//  チーム名２の取得
const FString& ABattleResultDisplay::GetTeam2Name() const
{
    return BattleResultWidget->Player2TeamName;
}




