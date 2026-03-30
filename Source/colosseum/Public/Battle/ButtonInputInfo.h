// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonInputInfo.generated.h"


#define CATEGORY_BattleInput "BattleInput"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FButtonInputInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_BattleInput)
    bool Coutinue = false;  //  コンテニュー入力

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_BattleInput)
    bool Trigger = false;   //  トリガ入力

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_BattleInput)
    bool Repeat = false;    //  リピート入力

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_BattleInput)
    bool BeforeContinue = false;    //  前回のコンテニュー入力

};
