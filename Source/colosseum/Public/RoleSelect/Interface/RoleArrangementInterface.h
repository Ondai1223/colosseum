// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RoleArrangementInterface.generated.h"


class ARoleSelectGameModeBase;

UENUM(BlueprintType)
enum class ERoleArrangementState : uint8
{
    ERAS_Arranging       UMETA(DisplayName = "ロール配置中"),  // ロール配置中
    ERAS_Completed       UMETA(DisplayName = "配置完了"),   // 配置完了
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URoleArrangementInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *  ロール配置インターフェース
 */

class COLOSSEUM_API IRoleArrangementInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:


    //  ロール配置開始
    virtual void BeginRoleArrangement(ARoleSelectGameModeBase* GameMode) = 0;
    //  ロール配置のTick
    virtual ERoleArrangementState TickRoleArrangement(ARoleSelectGameModeBase* GameMode , float DeltaSeconds) = 0;


};
