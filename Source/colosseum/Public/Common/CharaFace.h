// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/ComonDefine.h"
#include "Blueprint/UserWidget.h"
#include "Unit/UnitJob.h"
#include "Unit/UnitTeamID.h"
#include "CharaFace.generated.h"
/**
 * 
 */
UCLASS()
class COLOSSEUM_API UCharaFace : public UUserWidget
{
	GENERATED_BODY()
public:


    //  キャラクタの顔変更
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Common)
    void ChangeFace();
    virtual void ChangeFace_Implementation();


    //  アクション終了時に呼ばれる
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Common)
    void EndActionMode();
    virtual void EndActionMode_Implementation();

    //  通常状態へ戻す
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Common)
    void RunActionMode();
    virtual void RunActionMode_Implementation();

    //  死亡
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Common)
    void DeadMode();
    virtual void DeadMode_Implementation();

public:

    //  ジョブID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Common)
    EUnitJob    JobFaceID = EUnitJob::EUJ_None;

    //  チームID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Common)
    EUnitTeamID TeamID = EUnitTeamID::EUTID_None;

    //  死亡フラグ
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Common)
    bool Dead = false;

    //  アクション終了フラグ
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Common)
    bool ActionEnd = false;
};
