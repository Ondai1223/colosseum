// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Battle/BattleHelper.h"
#include "BattleGauge.generated.h"

/**
 * ゲージのウイジェット
 */
UCLASS()
class COLOSSEUM_API UBattleGauge : public UUserWidget
{
	GENERATED_BODY()
public:

    // 現在のポイントを設定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void SetNowPoint(int NewNowPoint);

    // 最大ポイントを設定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void SetMaxPoint(int NewMaxPoint);

private:
    int MaxPoint = 100; // 最大ポイント
};
