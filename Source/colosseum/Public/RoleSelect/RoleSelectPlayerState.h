// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Battle/BattleController.h"
#include "RoleSelect/RoleSelectDefines.h"
#include "RoleSelect/RoleSelectPage.h"
#include "RoleSelectPlayerState.generated.h"

/**
 *  プレーヤーロール選択ステート
 */
UCLASS()
class COLOSSEUM_API ARoleSelectPlayerState : public APlayerState
{
	GENERATED_BODY()
	



public:

    /**
     *  プレイヤー番号の取得
     */
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    int GetPlayerNo() const;


    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void TickProc(URoleSelectPage* page, ABattleController* BattleController, float DT);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    int PlayerIndex;


};
