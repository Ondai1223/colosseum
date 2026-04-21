// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/CharaFace.h"
#include "Battle/UnitBattleParameter.h"
#include "Blueprint/UserWidget.h"
#include "CoinTossCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class COLOSSEUM_API UCoinTossCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;

	// キャラクタの顔変更
	void ChangeFace(AUnitBattleParameter* BattleUnit, int32 index);

private:
	
	TObjectPtr<UCharaFace>  CharactorFace1;
	TObjectPtr<UCharaFace>  CharactorFace2;
	TObjectPtr<UCharaFace>  CharactorFace3;
	TObjectPtr<UCharaFace>  CharactorFace4;
	TObjectPtr<UCharaFace>  CharactorFace5;
	TObjectPtr<UCharaFace>  CharactorFace6;
	
};
