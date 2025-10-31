#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EUnitJob : uint8 // ユニットのジョブ
{
    // 列挙子を記述
    EUJ_None = 0        UMETA(DisplayName = "Job None"),    //ジョブ無し
    EUJ_Tank = 1        UMETA(DisplayName = "Job Tank"),    // ジョブ タンク
    EUJ_Rounder = 2     UMETA(DisplayName = "Job Rounder"), // ジョブ ラウンダー
    EUJ_Magician = 3    UMETA(DisplayName = "Job Magician"),    // ジョブ マジシャン
    EUJ_Healer = 4      UMETA(DisplayName = "Job Healer"),  // ジョブ ヒーラー
};

