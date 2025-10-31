// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Battle/Interface/MasoInterface.h" 
#include "MasoPanelData.generated.h"
/**
 * 魔素パネルのデータ格納用
 */
USTRUCT()
struct COLOSSEUM_API FMasoPanelData
{
    GENERATED_BODY()

    UPROPERTY(Transient)
    TScriptInterface<IMasoInterface> Maso; // どの属性の魔素が入っているのか.

    UPROPERTY(Transient)
    uint16 DisappearTurn = 2; // 消滅までのターン数.

    UPROPERTY(Transient)
    int PanelSideIndex = -1; // マスの0(右)か1(左)かどちらにあるか.

    UPROPERTY(Transient)
    bool bIsactivate = false; // 魔素の効果が実行中かどうか.
};
