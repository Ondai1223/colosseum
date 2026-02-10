// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Title/TitleGameMode.h"
#include "Title/TitleController.h"
#include "Title/TitleMenu.h"
#include "TitleWidget.generated.h"

/**
 * 
 */
UCLASS()
class COLOSSEUM_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct();

	void ChangeButton();

	void Init();
	// 通知を受け取った時に実行する関数
	UFUNCTION()
	void HandleInputChanged();

	void IncrementCursor();

	void DecrementCursor();
	

private:
	UPROPERTY(Transient)
	UTitleMenu* TitleView;

	UPROPERTY(Transient)
	ATitleController* TitleController;

	UPROPERTY(Transient)
	int SelectCursor = 0;

};
