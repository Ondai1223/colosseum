// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Battle/MasoPanel.h"
#include "MasoManager.generated.h"

UCLASS()
class COLOSSEUM_API AMasoManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasoManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//  魔素パネルを見つけて配置する
	UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
	void SearchMasoPanelFromWorld();

	// 魔素登録
	void JoinMaso(int X, int Y);

	// パネルの色変更
	void ChangeMasoPanelMaterial(TObjectPtr<AMasoPanel> MasoPanel, int MasoPanelNum, bool join);
	
	// Player1の魔素パネルのターン更新
	void UpdatePlayer1Maso();
	
	// Player2の魔素パネルのターン更新
	void UpdatePlayer2Maso();

private:
	UPROPERTY(Transient)
	TArray<TObjectPtr<AMasoPanel>> MasoPanelArray; //魔素パネルの配列

	UPROPERTY(Transient)
	TArray<TObjectPtr<AMasoPanel>> Player1MasoPanel; //プレイヤー１のパネル配列

	UPROPERTY(Transient)
	TArray<TObjectPtr<AMasoPanel>> Player2MasoPanel; //プレイヤー２のパネル配列

	int MasoNo = 0;

};
