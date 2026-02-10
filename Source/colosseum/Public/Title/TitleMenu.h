// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Overlay.h"
#include "TitleMenu.generated.h"

/**
 * タイトルView
 */
UCLASS()
class COLOSSEUM_API UTitleMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	//  ウイジェット構築
	virtual void NativeConstruct();

	void Init();

	void MenuButtonSwitch(int index);

public:
	//  選択カーソル
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Title)
	int    SelectCursor = 0;

private:
	//  矢印ウイジェット
	TArray<TObjectPtr<UOverlay>>  TitleOverlay;
	
};
