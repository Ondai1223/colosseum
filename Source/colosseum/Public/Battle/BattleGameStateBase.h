// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Battle/BattleCommon.h"
#include "Battle/BattleInGameWidgetProxy.h"
#include "Battle/BattleCommunication.h"
#include "BattleGameStateBase.generated.h"


class ABattleGameModeProxy;
class ABattleGameMode;
/**
 * 戦闘のゲームステートを管理するクラス
 */
UCLASS(Blueprintable)
class COLOSSEUM_API ABattleGameStateBase : public AActor
{
	GENERATED_BODY()



public:
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleState)
    void CreateBPBattleGameModeProxy();


    // ネットワークセットアップ
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleState)
    void SetupNetWork();
    // バトルのセットアップ
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleState)
    void SetupBattle();

    //  インゲームウイジェットの設定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleState)
    void SetBattleInGameWidget(UBattleInGameWidget* InGameWidget);


    //  ゲームモードプロキシ(代理)の設定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleState)
    void SetupGameModeProxy(ABattleGameMode* GameMode);
public:
    void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
    UFUNCTION()
    void OnRep_CommunicationData();

public:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CATEGORY_BattleState)
    EBattleNetWorkMode  NetWorkMode = EBattleNetWorkMode::EBNM_Normal;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CATEGORY_BattleState)
    TObjectPtr<UBattleInGameWidgetProxy> InGameWidgetProxy;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CATEGORY_BattleState)
    bool    ValidGameModeProxy = false;   //  プロキシクラスを使うかどうか true で使用

public:
    UPROPERTY(Replicated)
    TArray<FBattleCommunication>    CommunicationDataServer;  //  通信データ（サーバー用）

    UPROPERTY(ReplicatedUsing = OnRep_CommunicationData)
    TArray<FBattleCommunication>    CommunicationDataClient;  //  通信データ（クライアント用）
};
