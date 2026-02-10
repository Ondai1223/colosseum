// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleMenuButton.generated.h"

/**
 * 
 */
UCLASS()
class COLOSSEUM_API UTitleMenuButton : public UUserWidget
{
	GENERATED_BODY()

public:
	//  ウイジェット構築
	virtual void NativeConstruct();
	
};
