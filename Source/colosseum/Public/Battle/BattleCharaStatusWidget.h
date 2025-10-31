// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Battle/BattleHelper.h"
#include "Blueprint/UserWidget.h"
#include "Battle/UnitBattleParameter.h"
#include "Battle/BattleGauge.h"
#include "Common/CharaFace.h"
#include "BattleCharaStatusWidget.generated.h"

/**
 * バトルユニットステータス
 */
UCLASS()
class COLOSSEUM_API UBattleCharaStatusWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct();


public:
    void SetUnitBattleParameter(class AUnitBattleParameter* BattleUnit);

    void SetHpGauge(class UBattleGauge* InHpGauge);

    void SetMpGauge(class UBattleGauge* InMpGauge);

    //  バトルステータス初期設定
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void BeginBattleStatus();
    virtual void BeginBattleStatus_Implementation();

    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void ReflectBattleStatus();
    virtual void ReflectBattleStatus_Implementation();


    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void SelectBattleStatus();
    virtual void SelectBattleStatus_Implementation();


    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void CanselBattleStatus();
    virtual void CanselBattleStatus_Implementation();


public:
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    EUnitTeamID GetUnitTeamID() const;

    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void DisplayUnitBattleParameter();


    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void ChangeFace();

    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void ChangeEndAction();

    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void ChangeDead();


    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    int GetHp() const;

    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void SetHp(int NewHp);

    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    int GetMaxHp() const;

    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void SetMaxHp(int NewMaxHp);

    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    int GetMp() const;

    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void SetMp(int NewMp);

    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    int GetMaxMp() const;

    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void SetMaxMp(int NewMaxMp);


    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void OpenStatus();

    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void CloseStatus();

    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    bool IsOpenStatus() const;


    float GetHpRatio() const;

    float GetMpRatio() const;

    AUnitBattleParameter* GetUnitBattleParameter() const { return BattleUnitParameter; }


public:
    TObjectPtr<UCharaFace>  CharactorFace;  //  顔


private:

    TObjectPtr<AUnitBattleParameter> BattleUnitParameter;

    TObjectPtr<UBattleGauge> HpGauge;  
    TObjectPtr<UBattleGauge> MpGauge;

    bool IsStatusOpen = false;
};
