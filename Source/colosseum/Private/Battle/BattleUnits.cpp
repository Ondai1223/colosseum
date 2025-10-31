// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle/BattleUnits.h"
#include "Battle/BattleHelper.h"

// Sets default values
ABattleUnits::ABattleUnits()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABattleUnits::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattleUnits::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//  ユニット配置フィールド
void ABattleUnits::CreateUnitFiled()
{
    int Num = GAME_LOCATION_WIDTH * GAME_LOCATION_DEPTH;

    for (int i = 0; i < Num; ++i)
    {
        Units.Add(nullptr);

    }
}


//  ユニット選択
void ABattleUnits::SetUnit(int X, int Y, TObjectPtr<AUnitBattleParameter>& unit)
{
    BattleHelper    helper;
    int Num = helper.CalcPanelNum(X, Y);

    if (Num >= 0)
    {
        Units[Num] = unit;
    }
}

TObjectPtr<AUnitBattleParameter> ABattleUnits::GetUnit(int X, int Y)
{
    BattleHelper    helper;
    int Num = helper.CalcPanelNum(X, Y);

    if (Num >= 0)
    {
        return Units[Num];
    }
    return nullptr;
}


