// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit/Unit.h"
#include "Battle/UnitBattleParameter.h"
#include "GameFramework/Actor.h"
#include "BattleUnits.generated.h"

UCLASS()
class COLOSSEUM_API ABattleUnits : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleUnits();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    //  ユニット配置フィールド
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void CreateUnitFiled();

    //  ユニットを書き込む
    void SetUnit(int X, int Y, TObjectPtr<AUnitBattleParameter>& unit);

    //  ユニット情報を取得
    TObjectPtr<AUnitBattleParameter> GetUnit(int X, int Y);
public:
    UPROPERTY(Transient);
    TArray<TObjectPtr<AUnitBattleParameter>> Units;
};
