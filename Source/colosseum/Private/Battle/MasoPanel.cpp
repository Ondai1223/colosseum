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
void AMasoPanel::JoinMasoPanelData(FMasoPanelData PanelData)
{
	MasoPanelDataArray.Add(PanelData);
}

int AMasoPanel::GetMasoPanelDataArraySize()
{
	return MasoPanelDataArray.Num();
}

bool AMasoPanel::GetMasoPanelDataFromMasoNum(int Masoindex)
{

	for (int i = 0; MasoPanelDataArray.Num(); ++i)
	{
		if (MasoPanelDataArray[i].PanelSideIndex == Masoindex)
		{
			MasoPanelDataPtr = &MasoPanelDataArray[i];
			return true;
		}
	}
	return false;
}

bool AMasoPanel::GetMasoPanelDataFromIndex(int index)
{
	if (index < MasoPanelDataArray.Num())
	{
		MasoPanelDataPtr = &MasoPanelDataArray[index];
		return true;
	}
	return false;
}

void AMasoPanel::RemoveMasoPanelData(int index)
{
	MasoPanelDataArray.RemoveAt(index);
}

