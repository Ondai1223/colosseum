// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoPanel.h"

// Sets default values
AMasoPanel::AMasoPanel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMasoPanel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMasoPanel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// メンバ変数に登録する.
void AMasoPanel::JoinMasoPanelData(int32 Key, FMasoPanelData PanelData)
{
	if (Key == 0 || Key == 1)
	{
		MasoPanelDataMap.Add(Key, PanelData);
		UE_LOG(LogTemp, Warning, TEXT("魔素登録完了"));
	}
	
}

int AMasoPanel::GetMasoPanelDataMapSize()
{
	return MasoPanelDataMap.Num();
}

bool AMasoPanel::GetMasoPanelData(int32 Key)
{
	PanelDataPtr = MasoPanelDataMap.Find(Key);

	if (PanelDataPtr)
	{
		UE_LOG(LogTemp, Warning, TEXT("魔素パネルのデータを取得."));
		return true;
	}
	
	return false;
}

bool AMasoPanel::HasMasoData(int32 Key)
{
	return MasoPanelDataMap.Contains(Key);
}

void AMasoPanel::GetMasoKeys(TArray<int32>& OutKeys)
{
	MasoPanelDataMap.GetKeys(OutKeys);
}

void AMasoPanel::RemoveMasoPanelData(int32 Key)
{
	if (Key == 0 || Key == 1)
	{
		MasoPanelDataMap.Remove(Key);
	}
}

void AMasoPanel::AllRemoveMasoPanelData()
{
	MasoPanelDataMap.Empty();
	UE_LOG(LogTemp, Warning, TEXT("魔素マップを空にします."))
}

void AMasoPanel::SetIsActive(bool Active)
{
	IsActivate = Active;
}

bool AMasoPanel::GetIsActive()
{
	return IsActivate;
}
