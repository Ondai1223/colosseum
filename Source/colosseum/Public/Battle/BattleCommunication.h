

#pragma once

#include "CoreMinimal.h"
#include "Unit/UnitData.h"

#include "BattleCommunication.generated.h"


#define CATEGORY_BattleNetWork "BattleNetWork"
/**
 *	通信データ
 */

USTRUCT(BlueprintType)
struct FBattleCommunication
{
    GENERATED_BODY()


public:
    //  サーバーＩＤ


    //  カメラ
    UPROPERTY(BlueprintReadWrite, Category = CATEGORY_BattleNetWork)
    FVector CameraPosition; //  位置

    UPROPERTY(BlueprintReadWrite, Category = CATEGORY_BattleNetWork)
    FRotator CameraRotator; //  回転



};

