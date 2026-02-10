// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RoleSelect/RoleSelectDefines.h"
#include "RoleSelect/RoleUnitSlot.h"
#include "RoleSelectGameState.generated.h"

/**
 * ロールセレクトのゲームステート
 */
UCLASS()
class COLOSSEUM_API ARoleSelectGameState : public AGameStateBase
{
    GENERATED_BODY()




public:
    TArray<TObjectPtr<ARoleUnitSlot>> Player1RoleUnitSlots;

public:
    //  ゲームの対戦モード
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    EBattleGameMode GameMode = EBattleGameMode::EBGM_Player_VS_Player;

};
