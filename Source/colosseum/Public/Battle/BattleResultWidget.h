// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Battle/BattleGameMode.h"
#include "BattleResultWidget.generated.h"

/**
 *  戦闘結果表示ウイジェット
 */
UCLASS()
class COLOSSEUM_API UBattleResultWidget : public UUserWidget
{
	GENERATED_BODY()


public:
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void OpenBattleResult();
    virtual void OpenBattleResult_Implementation();

    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void CloseBattleResult();
    virtual void CloseBattleResult_Implementation();

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    EBattleResult BattleResult;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CATEGORY_Battle)
    FString   Player1TeamName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CATEGORY_Battle)
    FString   Player2TeamName;


};
