// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Battle/BattleSelectPanel.h"
#include "BattleSelector.generated.h"

/**
 *  バトルコマンド選択パネルの管理
 */
UCLASS(Blueprintable)
class COLOSSEUM_API ABattleSelector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleSelector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:

    //  ワールドからセレクトパネルを検索
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void SearchSelectPanelFromWorld();

    //  パネルのオンオフ
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void SetPanel(int X , int Y , bool on);

    //  パネルのON、OFF確認
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    bool IsPanelEnable(int X, int Y) const;

    //  すべてのパネルを非表示
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void AllOffPanel();

    //  陣地選択可不可の設定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void SetSelectPanelTeamValid(EUnitTeamID TeamID, bool valid);

public:

    TArray<TObjectPtr<ABattleSelectPanel>> SelectPanelArray; // パネル保存先
};


