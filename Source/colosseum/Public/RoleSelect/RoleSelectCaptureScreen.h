// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Unit/UnitData.h"
#include "RoleSelect/RoleSelectDefines.h"
#include "RoleSelectCaptureScreen.generated.h"

/**
 * ロールセレクトキャプチャースクリーン
 */
UCLASS()
class COLOSSEUM_API URoleSelectCaptureScreen : public UUserWidget
{
	GENERATED_BODY()
	

public:

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = CATEGORY_RoleSelect)
    EUnitTeamID TeamID = EUnitTeamID::EUTID_None; // チームID
};
