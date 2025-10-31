// Fill out your copyright notice in the Description page of Project Settings.

/**
 * ウイジェット代理クラス
 */

#include "Battle/BattleInGameWidgetProxy.h"

 //  セットアップ
void UBattleInGameWidgetProxy::Setup()
{
 
}

//  バトルコマンド開始
void UBattleInGameWidgetProxy::BeginBattleCommand(class ABattleGameMode* GameMode, class AUnitBattleParameter* BattleUnit)
{
    if (!InGameWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBattleInGameWidgetProxy::BeginBattleCommand: InGameWidget is nullptr"));
    }
    else
    {
        InGameWidget->BeginBattleCommand(GameMode, BattleUnit);
    }
}

//  バトルコマンドの処理
void UBattleInGameWidgetProxy::TickBattleCommand(float DeltaSeconds)
{
    if (!InGameWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBattleInGameWidgetProxy::TickBattleCommand: InGameWidget is nullptr"));
    }
    else
    {
        InGameWidget->TickBattleCommand(DeltaSeconds);
        Command = InGameWidget->Command;
    }
}

void UBattleInGameWidgetProxy::ReleaseBattleCommand(float DeltaSeconds)
{
    if (!InGameWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBattleInGameWidgetProxy::ReleaseBattleCommand: InGameWidget is nullptr"));
    }
    else
    {
        InGameWidget->ReleaseBattleCommand(DeltaSeconds);
    }
}


//  ステータス全体の表示非表示
void UBattleInGameWidgetProxy::EnableVisible()
{
    if (!InGameWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBattleInGameWidgetProxy::EnableVisible: InGameWidget is nullptr"));
    }
    else
    {
        InGameWidget->EnableVisible();
    }
}


void UBattleInGameWidgetProxy::DisenableVisible()
{
    if (!InGameWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBattleInGameWidgetProxy::DisenableVisible: InGameWidget is nullptr"));
    }
    else
    {
        InGameWidget->DisenableVisible();
    }
}

//  バトルコマンドの表示非表示
void UBattleInGameWidgetProxy::EnableBattleCommand()
{
    if (!InGameWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBattleInGameWidgetProxy::EnableBattleCommand: InGameWidget is nullptr"));
    }
    else
    {
        InGameWidget->EnableBattleCommand();
    }
}

//  
void UBattleInGameWidgetProxy::DisenableBattleCommand()
{
    if (!InGameWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBattleInGameWidgetProxy::DisenableBattleCommand: InGameWidget is nullptr"));
    }
    else
    {
        InGameWidget->DisenableBattleCommand();
    }
}

//  バトルコマンドを開く
void UBattleInGameWidgetProxy::OpenBattleCommand(ABattleGameMode* GameMode, AUnitBattleParameter* BattleUnit)
{
    if (!InGameWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBattleInGameWidgetProxy::OpenBattleCommand: InGameWidget is nullptr"));
    }
    else
    {
        InGameWidget->OpenBattleCommand(GameMode, BattleUnit);
    }
}

//  実行
void UBattleInGameWidgetProxy::RunBattleCommand(float DeltaSeconds)
{
    if (!InGameWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBattleInGameWidgetProxy::RunBattleCommand: InGameWidget is nullptr"));
    }
    else
    {
        InGameWidget->RunBattleCommand(DeltaSeconds);
    }
}
//  リリースバトルコマンド
void UBattleInGameWidgetProxy::CloseBattleCommand(float DeltaSeconds)
{
    if (!InGameWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBattleInGameWidgetProxy::CloseBattleCommand: InGameWidget is nullptr"));
    }
    else
    {
        InGameWidget->CloseBattleCommand(DeltaSeconds);
    }
}

//  ターンの表示
void UBattleInGameWidgetProxy::EnableTurnDisplay(ABattleGameMode* GameMode)
{
    if (!InGameWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBattleInGameWidgetProxy::EnableTurnDisplay: InGameWidget is nullptr"));
    }
    else
    {
        InGameWidget->EnableTurnDisplay(GameMode);
    }
}

//  ターン非表示
void UBattleInGameWidgetProxy::DisenableTurnDisplay()
{
    if (!InGameWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBattleInGameWidgetProxy::DisenableTurnDisplay: InGameWidget is nullptr"));
    }
    else
    {
        InGameWidget->DisenableTurnDisplay();
    }
}

//  プレーヤーのステータスをすべて反映
void UBattleInGameWidgetProxy::ReflectPlayersStatus(ABattleGameMode* GameMode)
{
    if (!InGameWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBattleInGameWidgetProxy::ReflectPlayersStatus: InGameWidget is nullptr"));
    }
    else
    {
        InGameWidget->ReflectPlayersStatus(GameMode);
    }
}




//  チームのインデックスのプレイヤーステータスを取得
TObjectPtr<UBattleCharaStatusWidget> UBattleInGameWidgetProxy::GetPlayersStatus(EUnitTeamID Team, int Index)
{
    if (!InGameWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBattleInGameWidgetProxy::GetPlayersStatus: InGameWidget is nullptr"));
        return nullptr;
    }
    return InGameWidget->GetPlayersStatus(Team, Index);
}

//  チームのプレイヤーネームウイジェットを取得
TObjectPtr<UPlayerNameWidget> UBattleInGameWidgetProxy::GetPlayerNameWidget(EUnitTeamID Team)
{
    if (!InGameWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBattleInGameWidgetProxy::GetPlayerNameWidget: InGameWidget is nullptr"));
        return nullptr;
    }
    return InGameWidget->GetPlayerNameWidget(Team);
}


