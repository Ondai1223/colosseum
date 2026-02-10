// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Unit/UnitTeamID.h"
#include "Unit/UnitJob.h"
#include "RoleSelectUnitStartPosition.generated.h"



class ARoleArrangementUnitStage;
/**
 *  ユニット配置
 */
UCLASS()
class COLOSSEUM_API URoleSelectUnitStartPosition : public UUserWidget
{
	GENERATED_BODY()
	


public:
    //  ユニット配置スクリーンのアタッチ
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
    void SetStartPositionScreen();
    virtual void SetStartPositionScreen_Implementation();


public:
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void SetArrangementUnit(EUnitJob Job,int SlotNo = 0);



public:
    //  チームID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    EUnitTeamID TeamID = EUnitTeamID::EUTID_None;


    UPROPERTY(Transient)
    TObjectPtr<ARoleArrangementUnitStage>   RoleArrangementUnitStage;
};
