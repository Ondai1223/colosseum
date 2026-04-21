// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Blueprint/UserWidget.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class COLOSSEUM_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	void Init() override;

	void BeginLoadingScreen(const FString& MapName);

	void CreateWidgets();
	
	virtual void Shutdown() override;
protected:
	TSubclassOf<UUserWidget> BackgroundWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loading")
	TSubclassOf<UUserWidget> LoadingWidgetClass;

	TSharedPtr<SWidget> LoadingWidgetSlate;
	TSharedPtr<SWidget> StartupWidgetSlate;

	UPROPERTY(BlueprintReadOnly, Category = "Loading")
	UUserWidget* CurrentLoadingWidget;

	bool bIsStartup = false;

	UPROPERTY(BlueprintReadOnly, Category = "Loading")
	bool Loading = false;

private:	

	UUserWidget* BGWidget;
	UUserWidget* TempWidget;

	UUserWidget* StartupWidget;
};
