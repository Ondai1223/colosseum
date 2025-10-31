
#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EUnitTeamID : uint8 //チームのID
{
    // 列挙子を記述
    EUTID_None = 0        UMETA(DisplayName = "Team None"),    //チーム不明
    EUTID_Team1 = 1        UMETA(DisplayName = "Team1"),    // チーム１
    EUTID_Team2 = 2     UMETA(DisplayName = "Team2"), // チーム２
};

