// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/BattleInGameWidget.h"
#include "Battle/BattleGameMode.h"
#include "Battle/BattleCommandWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Battle/UnitBattleParameter.h"


#define PLAYER1TURN_NAME    TEXT("プレーヤー１のターン")
#define PLAYER2TURN_NAME    TEXT("プレーヤー２のターン")
#define PLAYER_TRUNE_DISPLAY_ITEM_NAME  TEXT("TurnTextBlock")


#define COMMAND_WPB_NAME    TEXT("WBP_Commands")
#define PLAYER_TRUN_INFO_NAME   TEXT("WBP_PlayerTurnInform")


#define PLAYER1_TEAM_PARAMETER_NAME TEXT("VerticalBox_1P")
#define PLAYER2_TEAM_PARAMETER_NAME TEXT("VerticalBox_2P")

#define HP_GAUGE_NAME  TEXT("WBP_InGame_Gauge_HP")
#define MP_GAUGE_NAME  TEXT("WBP_InGame_Gauge_MP")

#define GAUGE_COLUMN 2

#define GAUGE_TEXT_NOW     TEXT("TextBlock_NumTop")
#define GAUGE_TEXT_MAX     TEXT("TextBlock_NumBottom")

#define GAUGE_BAR_NAME      TEXT("ProgressBar")
#define GAUGE_NAME          TEXT("TextBlock_ParameterName")

#define PLAYER1_TEAM_NAME   TEXT("WBP_PlayerName_P1")
#define PLAYER2_TEAM_NAME   TEXT("WBP_PlayerName_P2")


void UBattleInGameWidget::NativeConstruct()
{
    Super::NativeConstruct();



    TurnDisplay = Cast<UUserWidget>(GetWidgetFromName(PLAYER_TRUN_INFO_NAME));
    if (!TurnDisplay) {
        UE_LOG(LogTemp, Warning, TEXT("TurnDisplay is nullptr"));
    }
    else
    {
        TurnDisplay->SetVisibility(ESlateVisibility::Hidden);
    }

    BattleCommand = Cast<UBattleCommandWidget>(GetWidgetFromName(COMMAND_WPB_NAME));
    if (!BattleCommand)
    {
        UE_LOG(LogTemp, Warning, TEXT("BattleCommand is nullptr"));
    }
    else
    {
        BattleCommand->SetVisibility(ESlateVisibility::Hidden);
    }

}


void UBattleInGameWidget::BeginBattleCommand_Implementation(ABattleGameMode* GameMode, AUnitBattleParameter* BattleUnit)
{
    SelectUnit = BattleUnit;
    Command = EBattleCommand::EBC_CONTINUE;
    SelectLock = true;
}

void UBattleInGameWidget::TickBattleCommand_Implementation(float DeltaSeconds)
{
}

void UBattleInGameWidget::ReleaseBattleCommand_Implementation(float DeltaSeconds)
{

}



void UBattleInGameWidget::EnableVisible()
{
    SetVisibility(ESlateVisibility::Visible);
}


void UBattleInGameWidget::DisenableVisible()
{
    SetVisibility(ESlateVisibility::Hidden);
}




void UBattleInGameWidget::EnableBattleCommand()
{
    BattleCommand->SetVisibility(ESlateVisibility::Visible);
}

void UBattleInGameWidget::DisenableBattleCommand()
{
    BattleCommand->SetVisibility(ESlateVisibility::Hidden);
}



void UBattleInGameWidget::OpenBattleCommand(ABattleGameMode* GameMode, AUnitBattleParameter* BattleUnit)
{
    BattleCommand->Command = EBattleCommand::EBC_CONTINUE;
    BattleCommand->BeginBattleCommand(GameMode, BattleUnit);
}


void UBattleInGameWidget::RunBattleCommand(float DeltaSeconds)
{
    BattleCommand->TickBattleCommand(DeltaSeconds);
    Command = BattleCommand->Command;
}


void UBattleInGameWidget::CloseBattleCommand(float DeltaSeconds)
{
    BattleCommand->ReleaseBattleCommand(DeltaSeconds);
}





void UBattleInGameWidget::EnableTurnDisplay(ABattleGameMode* GameMode)
{
    TurnDisplay->SetVisibility(ESlateVisibility::Visible);
    TObjectPtr<UTextBlock> TurnText = Cast<UTextBlock>(TurnDisplay->GetWidgetFromName(PLAYER_TRUNE_DISPLAY_ITEM_NAME));
    if (TurnText)
    {
        TurnText->SetText(FText::FromString((GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player1) ? PLAYER1TURN_NAME : PLAYER2TURN_NAME));
    }
}

void UBattleInGameWidget::DisenableTurnDisplay()
{
    TurnDisplay->SetVisibility(ESlateVisibility::Hidden);
}



void UBattleInGameWidget::ReflectPlayersStatus(ABattleGameMode* GameMode)
{
    TObjectPtr<UVerticalBox> Player1Parameters = Cast<UVerticalBox>(GetWidgetFromName(PLAYER1_TEAM_PARAMETER_NAME));
    TObjectPtr<UVerticalBox> Player2Parameters = Cast<UVerticalBox>(GetWidgetFromName(PLAYER2_TEAM_PARAMETER_NAME));
    ReflectPlayersStatus(Player1Parameters,GameMode,GameMode->Player1UnitsActors);
    ReflectPlayersStatus(Player2Parameters,GameMode, GameMode->Player2UnitsActors);
}

TObjectPtr<UBattleCharaStatusWidget> UBattleInGameWidget::GetPlayersStatus(EUnitTeamID Team, int Index)
{
   bool Player1Team = Team == EUnitTeamID::EUTID_Team1;

    TObjectPtr<UVerticalBox> PlayerParameters = Cast<UVerticalBox>(GetWidgetFromName((Player1Team) ? PLAYER1_TEAM_PARAMETER_NAME : PLAYER2_TEAM_PARAMETER_NAME));
    if (PlayerParameters)
    {
        TObjectPtr<UUserWidget> UserWidget = Cast<UUserWidget>(PlayerParameters->GetChildAt(Index * GAUGE_COLUMN));
        if (UserWidget) {
            return Cast<UBattleCharaStatusWidget>(UserWidget);
        }
    }
    return nullptr;
}

//  チームのプレイヤーネームウイジェットを取得
TObjectPtr<UPlayerNameWidget> UBattleInGameWidget::GetPlayerNameWidget(EUnitTeamID Team)
{
    bool Player1Team = Team == EUnitTeamID::EUTID_Team1;

    TObjectPtr<UPlayerNameWidget> PlayerName = Cast<UPlayerNameWidget>(GetWidgetFromName((Player1Team) ? PLAYER1_TEAM_NAME : PLAYER2_TEAM_NAME));

    return PlayerName;
}


void UBattleInGameWidget::ReflectPlayersStatus(TObjectPtr<UVerticalBox>& VBox,ABattleGameMode* GameMode, const TArray <TObjectPtr<AUnitBattleParameter>>& Team)
{
    int Index = 0;
    for (TArray<TObjectPtr<AUnitBattleParameter>>::TConstIterator Ite(Team); Ite; ++Ite , Index += GAUGE_COLUMN)
    {
        ReflectPlayerStatus(VBox, GameMode, *Ite,Index);
    }
}

void UBattleInGameWidget::ReflectPlayerStatus(TObjectPtr<UVerticalBox>& VBox, ABattleGameMode* GameMode, const TObjectPtr<AUnitBattleParameter>& Unit, int Index)
{
//    bool Player1Team = Unit->GetTeamID() == EUnitTeamID::EUTID_Team1;

    TObjectPtr<UUserWidget> UserWidget = Cast<UUserWidget>(VBox->GetChildAt(Index));
    if (UserWidget) {
        TObjectPtr<UUserWidget> HpGauge = Cast<UUserWidget>(UserWidget->GetWidgetFromName(HP_GAUGE_NAME));
        TObjectPtr<UUserWidget> MpGauge = Cast<UUserWidget>(UserWidget->GetWidgetFromName(MP_GAUGE_NAME));

        SetGauge(HpGauge, Unit->GetHp(), Unit->GetMaxHp(), FText::FromString(TEXT("HP")));
        SetGauge(MpGauge, Unit->GetMp(), Unit->GetMaxMp(), FText::FromString(TEXT("MP")));
    }
}

void UBattleInGameWidget::SetGauge(TObjectPtr<UUserWidget>& Gauge, int NowPoint, int MaxPoint,const FText& Name)
{

    TObjectPtr<UTextBlock> NowPointText = Cast<UTextBlock>(Gauge->GetWidgetFromName(GAUGE_TEXT_NOW));
    TObjectPtr<UTextBlock> MaxPointText = Cast<UTextBlock>(Gauge->GetWidgetFromName(GAUGE_TEXT_MAX));
    TObjectPtr<UProgressBar> Bar = Cast<UProgressBar>(Gauge->GetWidgetFromName(GAUGE_BAR_NAME));

    TObjectPtr<UTextBlock> TextBox = Cast<UTextBlock>(Gauge->GetWidgetFromName(GAUGE_NAME));

    
    if (NowPointText)
    {
        NowPointText->SetText(FText::FromString(FString::FromInt(NowPoint)));
    }
    if (MaxPointText)
    {
        MaxPointText->SetText(FText::FromString(FString::FromInt(MaxPoint)));
    }
    if (Bar)
    {
        Bar->SetPercent((MaxPoint > 0) ? ((float)NowPoint / (float)MaxPoint) : 0.0f);
    }
    if (TextBox)
    {
        TextBox->SetText(Name);
    }

}

