// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Battle/MasoActionBase.h"
#include "MasoActionThunderThunder.generated.h"

/**
 * 
 */
UCLASS()
class COLOSSEUM_API UMasoActionThunderThunder : public UMasoActionBase
{
	GENERATED_BODY()

public:
	UMasoActionThunderThunder();

	virtual void ApplyAction() override;

	virtual void ActionEffect(TObjectPtr<AMasoPanel> MasoPanel) override;
	
	virtual EActionType GetActionType()override;
};
