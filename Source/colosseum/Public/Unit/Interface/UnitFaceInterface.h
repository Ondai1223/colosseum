// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UnitFaceInterface.generated.h"



UENUM(BlueprintType)
enum class EUnitFace : uint8
{
    EUF_Normal      UMETA(DisplayName = "通常"),        // 通常
    EUF_Damaged     UMETA(DisplayName = "ダメージ"),    // ダメージ
};

/**
 *  表情変化インターフェース
 */


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUnitFaceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COLOSSEUM_API IUnitFaceInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

    //  任意の表情に変更
    virtual void ChangeUnitFace(EUnitFace NewFace) = 0;
};
