// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RoleSelect/RoleSelectDefines.h"
#include "RoleSelect/RoleUnitSlot.h"
#include "RoleSelect/RoleSelectStateData.h"
#include "RoleSelectGameState.generated.h"

/**
 * ロールセレクトのゲームステート
 */
UCLASS()
class COLOSSEUM_API ARoleSelectGameState : public AGameStateBase
{
    GENERATED_BODY()
public:

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


public:
    //  ネゴシエーションメッセージの同期
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
    void SyncNegotiationMessage(const FString& Message);
    virtual void SyncNegotiationMessage_Implementation(const FString& Message);


public:

    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    bool IsCheckPlayerController(int CheckIndex = 2) const;


    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    bool IsCheckPlayerState(int CheckIndex = 2) const;

    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    int GetPlayerNum(ABattleController* controller) const;

    //  文字列比較
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    bool CompereString(const FString& StrLeft, const FString& StrRight) const;


public:
    TArray<TObjectPtr<ARoleUnitSlot>> Player1RoleUnitSlots;
public:
    //  ゲームの対戦モード
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    EBattleGameMode GameMode = EBattleGameMode::EBGM_Player_VS_Player;


    UPROPERTY(Replicated , EditAnywhere , BlueprintReadWrite , Category = CATEGORY_RoleSelect)
    FString NegotiationMessageServer;

    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    FString NegotiationMessageClient;
};
