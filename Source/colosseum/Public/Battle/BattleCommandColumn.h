// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleCommandColumn.generated.h"

/**
 * バトルコマンドのカラム
 */
UCLASS()
class COLOSSEUM_API UBattleCommandColumn : public UUserWidget
{
	GENERATED_BODY()


public:
    //　アイコンの変更イベント
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void OnChangeIcon();
    virtual void OnChangeIcon_Implementation();

    //  カラムが選択されたイベント
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void OnSelectedColumn();
    virtual void OnSelectedColumn_Implementation();

public:
    //  アイコン番号
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    int SelectIconNo = 0;

    //  選択されているカラム番号
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    int SelectedColumn  = 0;

	
};
