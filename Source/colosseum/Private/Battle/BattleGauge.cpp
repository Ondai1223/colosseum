// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle/BattleGauge.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"


#define GAUGE_TEXT_NOW     TEXT("TextBlock_NumTop")
#define GAUGE_TEXT_MAX     TEXT("TextBlock_NumBottom")
#define GAUGE_BAR_NAME      TEXT("ProgressBar")
#define GAUGE_TEXT_ParameterName   TEXT("TextBlock_ParameterName")

void UBattleGauge::SetNowPoint(int NewNowPoint)
{
    UProgressBar* GaugeBar = Cast<UProgressBar>(GetWidgetFromName(GAUGE_BAR_NAME));
    if (GaugeBar)
    {
        GaugeBar->SetPercent(FMath::Clamp(static_cast<float>(NewNowPoint) / static_cast<float>(MaxPoint), 0.0f, 1.0f));
    }
    UTextBlock* NowPointText = Cast<UTextBlock>(GetWidgetFromName(GAUGE_TEXT_NOW));
    if (NowPointText)
    {
        NowPointText->SetText(FText::AsNumber(NewNowPoint));
    }
}


void UBattleGauge::SetMaxPoint(int NewMaxPoint)
{
    MaxPoint = NewMaxPoint;
    UTextBlock* MaxPointText = Cast<UTextBlock>(GetWidgetFromName(GAUGE_TEXT_MAX));
    if (MaxPointText)
    {
        MaxPointText->SetText(FText::AsNumber(NewMaxPoint));
    }
}

void UBattleGauge::SetParameterName(FString NewParameterName)
{
    UTextBlock* ParameterNameText = Cast<UTextBlock>(GetWidgetFromName(GAUGE_TEXT_ParameterName));
    if (ParameterNameText)
    {
        ParameterNameText->SetText(FText::FromString(NewParameterName));
    }
}

