// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Battle/BattleCommon.h"
#include "Battle/BattleInGameWidgetProxy.h"
#include "Battle/BattleCommunication.h"
#include "BattleGameStateBase.generated.h"


/**
 * 戦闘のゲームステートを管理するクラス
 */
UCLASS(Blueprintable)
class COLOSSEUM_API ABattleGameStateBase : public AGameStateBase
{
	GENERATED_BODY()



public:
    // ネットワークセットアップ
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleState)
    void SetupNetWork();
    // バトルのセットアップ
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleState)
    void SetupBattle();

    //  インゲームウイジェットの設定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleState)
    void SetBattleInGameWidget(UBattleInGameWidget* InGameWidget);

public:
    void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
    UFUNCTION()
    void OnRep_CommunicationData();


public:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CATEGORY_BattleState)
    EBattleNetWorkMode  NetWorkMode = EBattleNetWorkMode::EBNM_Normal;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CATEGORY_BattleState)
    TObjectPtr<ACameraActor>   BattleCamera = nullptr;    


public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CATEGORY_BattleState)
    TObjectPtr<UBattleInGameWidgetProxy> InGameWidgetProxy;





public:
    UPROPERTY(Replicated)
    TArray<FBattleCommunication>    CommunicationDataServer;  //  通信データ（サーバー用）

    UPROPERTY(ReplicatedUsing = OnRep_CommunicationData)
    TArray<FBattleCommunication>    CommunicationDataClient;  //  通信データ（クライアント用）







};
