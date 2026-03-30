// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Battle/BattleSkillItem.h"
#include "Unit/UnitJob.h"
#include "Components/ScrollBox.h"
#include "BattleSkillWindow.generated.h"

/**
 * 特技選択ウインドウのクラス
 */
UCLASS()
class COLOSSEUM_API UBattleSkillWindow : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    // 前の特技を選択
    UFUNCTION(BlueprintCallable, Category = "Battle|Skill")
    void PrevSkill();

    // 次の特技を選択
    UFUNCTION(BlueprintCallable, Category = "Battle|Skill")
    void NextSkill();

    // 現在選択されている特技データを取得
    UFUNCTION(BlueprintCallable, Category = "Battle|Skill")
    FSkillDataType GetSelectedSkillData() const;

    // 選択状態をリセット
    UFUNCTION(BlueprintCallable, Category = "Battle|Skill")
    void ResetSelection(EUnitJob Job);

    // 現在選択されている項目のインデックスを取得
    UFUNCTION(BlueprintCallable, Category = "Battle|Skill")
    int32 GetSelectIndex() const { return SelectIndex; }

private:
    // 特技項目のリストを更新
    void UpdateSkillItems();

    // データテーブルの内容を反映
    void ApplySkillData(EUnitJob Job);

    // 選択状態を更新
    void RefreshSelection();

    // 再帰的に特技項目を探索
    void FindSkillItemsRecursive(UWidget* Root);

    // ScrollBoxを探す
    void FindScrollBoxRecursive(UWidget* Root);

private:
    // 特技項目の配列
    UPROPERTY()
    TArray<TObjectPtr<UBattleSkillItem>> SkillItems;

    // スクロールボックス
    UPROPERTY()
    TObjectPtr<UScrollBox> ScrollBox;

    // 特技データテーブル
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle|Skill", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UDataTable> SkillDataTable;

    // 現在の選択インデックス
    int32 SelectIndex = 0;

    // 特技項目のベース名（WBP側の名前に合わせる用）
    const FString SkillItemNameBase = TEXT("WBP_SkillItem_");
};
