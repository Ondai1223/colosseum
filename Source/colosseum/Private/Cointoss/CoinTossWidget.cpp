// Fill out your copyright notice in the Description page of Project Settings.


#include "Cointoss/CoinTossWidget.h"

#define IMAGE_COIN TEXT("Image_Coin")
#define CHARACTER_WIDGET TEXT("WBP_CoinToss_Character")
 
void UCoinTossWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	CharacterWidget = Cast<UCoinTossCharacterWidget>(GetWidgetFromName(CHARACTER_WIDGET));
	if (CharacterWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("CharacterWidgetの取得に成功しました"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CharacterWidgetの取得に失敗しました"));
	}
}
void UCoinTossWidget::UpdateTurnDisplay(UTexture2D* NewTexture)
{
	Image_Coin->SetBrushFromTexture(NewTexture);
}

void UCoinTossWidget::FirstPlay1P(UTexture2D* NewTexture)
{
	UpdateTurnDisplay(NewTexture);
	WidgetSwitcher_First->SetActiveWidgetIndex(0);
}

void UCoinTossWidget::FirstPlay2P(UTexture2D* NewTexture)
{
	UpdateTurnDisplay(NewTexture);
	WidgetSwitcher_First->SetActiveWidgetIndex(1);
}

void UCoinTossWidget::SetUnitBattleParameter(TArray<AUnitBattleParameter*> BattleUnits)
{
	int32 NumUnits = 0;
	if(BattleUnits.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("BattleUnitsが空です"));
		return;
	}
	for (AUnitBattleParameter* BattleUnit : BattleUnits)
	{
		if(BattleUnit)
		{
			CharacterWidget->ChangeFace(BattleUnit, NumUnits);
			NumUnits++;
		}
		
		
	}
}
