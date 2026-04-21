// Fill out your copyright notice in the Description page of Project Settings.

/**
 * 戦闘のゲームステートを管理するクラス
 */
#include "Battle/BattleGameStateBase.h"
#include "Battle/BattleGameMode.h"
#include "EngineUtils.h"
#include "Camera/CameraActor.h"


#define BATTLE_GAME_MODE_PROXY_NAME    TEXT("/Game/Battle/Blueprints/BP_BattleGameModeProxy.BP_BattleGameModeProxy_C") //  ゲームモード代理

void ABattleGameStateBase::CreateBPBattleGameModeProxy()
{
}

void ABattleGameStateBase::SetupNetWork()
{
    // ネットワークモードの設定
    switch (GetNetMode())
    {
    case NM_Standalone:
        //  落下
    default:
        UE_LOG(LogTemp, Warning, TEXT("SetupBattle: Standalone"));
        NetWorkMode = EBattleNetWorkMode::EBNM_Normal;
        break;
    case NM_DedicatedServer:
        //  落下
    case NM_ListenServer:
        // サーバー側の処理
        UE_LOG(LogTemp, Warning, TEXT("SetupBattle: Listen Server"));
        NetWorkMode = EBattleNetWorkMode::EBNM_Server;
        break;
    case NM_Client:
        // クライアント側の処理
        UE_LOG(LogTemp, Warning, TEXT("SetupBattle: Client"));
        NetWorkMode = EBattleNetWorkMode::EBNM_Client;
        break;
    }
}

 // バトルのセットアップ
void ABattleGameStateBase::SetupBattle()
{
    //  代理ウイジェットの作成
    InGameWidgetProxy = NewObject<UBattleInGameWidgetProxy>(this,TEXT("UBattleInGameWidgetProxy"));
    //  セットアップ
    InGameWidgetProxy->Setup();
}


//  インゲームウイジェットの設定
void ABattleGameStateBase::SetBattleInGameWidget(UBattleInGameWidget* InGameWidget)
{
    InGameWidgetProxy->InGameWidget = InGameWidget;
}

//  ゲームモードプロキシ(代理)の設定
void ABattleGameStateBase::SetupGameModeProxy(ABattleGameMode* GameMode)
{
}

void ABattleGameStateBase::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//    DOREPLIFETIME(ABattleGameStateBase, CommunicationDataServer);
//    DOREPLIFETIME(ABattleGameStateBase, CommunicationDataClient);
}



void ABattleGameStateBase::OnRep_CommunicationData()
{
}
