// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Battle/BuffDebuffBase.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "BuffDebuffWidget.generated.h"

/**
 * 
 */
UCLASS()
class COLOSSEUM_API UBuffDebuffWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct();

	void AddBuffDebuffIcon(UBuffDebuffBase* BuffDebuff);

	void RemoveBuffDebuffIcon(UBuffDebuffBase* BuffDebuff);
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UHorizontalBox* HorizontalBox_73;

private:
	UPROPERTY(Transient)
	TMap<UBuffDebuffBase*, UImage*> BuffIconMap;
	
};
