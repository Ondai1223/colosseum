// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleCommandColumn.generated.h"

/**
 * �o�g���R�}���h�̃J����
 */
UCLASS()
class COLOSSEUM_API UBattleCommandColumn : public UUserWidget
{
	GENERATED_BODY()


public:
    //�@�A�C�R���̕ύX�C�x���g
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void OnChangeIcon();
    virtual void OnChangeIcon_Implementation();

    //  �J�������I�����ꂽ�C�x���g
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void OnSelectedColumn();
    virtual void OnSelectedColumn_Implementation();

public:
    //  �A�C�R���ԍ�
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    int SelectIconNo = 0;

    //  �I������Ă���J�����ԍ�
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    int SelectedColumn  = 0;

	
};
