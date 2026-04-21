// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "Battle/UnitBattleParameter.h"
#include "Cointoss/CoinTossCharacterWidget.h"
#include "CoinTossWidget.generated.h"

/**
 * 
 */
UCLASS()
class COLOSSEUM_API UCoinTossWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized();

	void UpdateTurnDisplay(UTexture2D* NewTexture);

	// 1P先行時の処理
	UFUNCTION(BlueprintCallable, Category = "Cointoss")
	void FirstPlay1P(UTexture2D* NewTexture);

	// 2P先行時の処理
	UFUNCTION(BlueprintCallable, Category = "Cointoss")
	void FirstPlay2P(UTexture2D* NewTexture);

	// 1Pと2Pのユニットのバトルパラメーターをセットする関数
	UFUNCTION(BlueprintCallable, Category = "Cointoss")
	void SetUnitBattleParameter(TArray<AUnitBattleParameter*> BattleUnits);

protected:

	// コインの画像WBPの名前と同じ変数名で取得
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* Image_Coin;

	// 1Pと2Pの先行表示を切り替えるWidgetSwitcher, WBPのの変数名前と同じ変数名で取得
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher_First;

private:

	UPROPERTY(Transient)
	TObjectPtr<UCoinTossCharacterWidget> CharacterWidget;
	
};
