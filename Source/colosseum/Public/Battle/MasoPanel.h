// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Battle/MasoPanelData.h"
#include "MasoPanel.generated.h"

UCLASS()
class COLOSSEUM_API AMasoPanel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasoPanel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 右と左指定してMasoPanelDataを配列に追加.
	void JoinMasoPanelData(int32 Key, FMasoPanelData PanelData);

	// MasoPanelData配列の大きさ取得.
	int GetMasoPanelDataMapSize();

	// 右と左指定してMasoPanelDataを取得.
	bool GetMasoPanelData(int32 Key);

	// 指定したKeyに値があるか判定.
	bool HasMasoData(int32 Key);

	// 登録されているKeyを取得.
	void GetMasoKeys(TArray<int32>& OutKeys);

	// 配列のindexからMasoPanelDataを削除.
	void RemoveMasoPanelData(int32 Key);

	// 配列のMasoPanelDataを全削除.
	void AllRemoveMasoPanelData();

	void SetIsActive(bool Active);

	bool GetIsActive();

public:
	FMasoPanelData* PanelDataPtr;

	int PanelX;
	int PanelY;

private:
	UPROPERTY(Transient)
	TMap<int32, FMasoPanelData> MasoPanelDataMap; // パネルのデータを所持する配列.

	UPROPERTY(Transient)
	bool IsActivate = false; // 魔素の効果が実行中かどうか.

};
