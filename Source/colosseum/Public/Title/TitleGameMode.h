// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Title/TitleController.h"
#include "TitleGameMode.generated.h"

/**
 * タイトルゲームモード
 */
UCLASS()
class COLOSSEUM_API ATitleGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// ゲームモードのTickイベント
	UFUNCTION(BlueprintCallable, Category = CATEGORY_Title)
	void TickGameMode(float DeltaSeconds);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Title)
	TObjectPtr<ATitleController> TitleController;
	
};
