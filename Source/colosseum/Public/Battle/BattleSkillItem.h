// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Battle/SkillData.h"
#include "Battle/BattleCommon.h"
#include "BattleSkillItem.generated.h"

/**
 * 特技項目のウジェットクラス
 */
UCLASS()
class COLOSSEUM_API UBattleSkillItem : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    // 選択された時のイベント
    UFUNCTION(BlueprintNativeEvent, Category = "Battle|Skill")
    void OnSelected();
    virtual void OnSelected_Implementation();

    // 選択解除された時のイベント
    UFUNCTION(BlueprintNativeEvent, Category = "Battle|Skill")
    void OnDeselected();
    virtual void OnDeselected_Implementation();

    UFUNCTION(BlueprintNativeEvent, Category = "Battle|Skill")
    void OnConfirmed();
    virtual void OnConfirmed_Implementation();

    // 特技Iconを設定
    UFUNCTION(BlueprintNativeEvent, Category = "Battle|Skill")
    void SetSkillIcon(EBattleSkillIcon IconID);
    virtual void SetSkillIcon_Implementation(EBattleSkillIcon IconID);


    // 特技名を設定しUIに反映
    UFUNCTION(BlueprintCallable, Category = "Battle|Skill")
    void SetSkillName(const FText& InName);

    // 特技データを設定
    UFUNCTION(BlueprintCallable, Category = "Battle|Skill")
    void SetSkillData(const FSkillDataType& InData);



protected:
    // 再帰的にウィジェットを検索
    UWidget* FindWidgetRecursive(UWidget* Root, FName Name);

public:
    // 特技データ
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle|Skill")
    FSkillDataType SkillData;

    // 特技名を表示するテキスト
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle|Skill")
    FText SkillName;

    // 選択時に表示する矢印ウィジェット
    UPROPERTY(BlueprintReadWrite, Category = "Battle|Skill")
    TObjectPtr<UUserWidget> CommonArrow;

    // 特技名を表示するテキストブロック（任意、なければ自動検索）
    UPROPERTY(BlueprintReadWrite, Category = "Battle|Skill", meta = (BindWidgetOptional))
    TObjectPtr<UTextBlock> TextBlock_SkillName;
};
