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
	// MasoPanelDataを配列に追加.
	void JoinMasoPanelData(FMasoPanelData PanelData);

	// MasoPanelData配列の大きさ取得.
	int GetMasoPanelDataArraySize();

	// 右と左指定してMasoPanelDataを取得.(右か左指定した魔素のみに処理を行いたいとき)
	bool GetMasoPanelDataFromMasoNum(int Masoindex);

	// 配列のindexからMasoPanelDataを取得.(登録されている魔素すべてに処理を行いたいとき)
	bool GetMasoPanelDataFromIndex(int index);

	// 配列のindexからMasoPanelDataを削除.
	void RemoveMasoPanelData(int index);

public:
	FMasoPanelData* MasoPanelDataPtr; // 一時保管用のポインタ
private:
	UPROPERTY(Transient)
	TArray<FMasoPanelData> MasoPanelDataArray; // パネルのデータを所持する配列.

};
