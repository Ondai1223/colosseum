// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Common/ComonDefine.h"
#include "PlayerNameWidget.generated.h"

/**
 * プレーヤーネームウィジェット
 */
UCLASS(Blueprintable)
class COLOSSEUM_API UPlayerNameWidget : public UUserWidget
{
	GENERATED_BODY()


public:
    //  イベント

    //  設定したプレーヤーネームの反映
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Common)
    void ReflectionPlayerName();
    virtual void ReflectionPlayerName_Implementation();


public:


public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Common)
    FString PlayerName = "TEST";
};
