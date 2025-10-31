// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Battle/BattleHelper.h"
#include "BattleGauge.generated.h"

/**
 * �Q�[�W�̃E�C�W�F�b�g
 */
UCLASS()
class COLOSSEUM_API UBattleGauge : public UUserWidget
{
	GENERATED_BODY()
public:

    // ���݂̃|�C���g��ݒ�
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void SetNowPoint(int NewNowPoint);

    // �ő�|�C���g��ݒ�
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void SetMaxPoint(int NewMaxPoint);

private:
    int MaxPoint = 100; // �ő�|�C���g
};
