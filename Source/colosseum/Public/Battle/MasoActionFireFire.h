// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Battle/MasoActionBase.h"
#include "MasoActionFireFire.generated.h"

/**
 * 
 */
UCLASS()
class COLOSSEUM_API UMasoActionFireFire : public UMasoActionBase
{
	GENERATED_BODY()

public:
	UMasoActionFireFire();

	virtual void CalcAction(FActionResultData* ActionResult, const uint8 PanelX, const uint8 PanelY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode) override;

	virtual void ReflectAction(FActionResultData& ActionResult, ABattleGameMode* GameMode) override;

	virtual void ActionEffect(TObjectPtr<AMasoPanel> MasoPanel) override;

	virtual float GetActionTime() override;
	
	virtual EActionType GetActionType()override;
};
