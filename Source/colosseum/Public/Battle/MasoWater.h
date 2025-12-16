// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Battle/Interface/MasoInterface.h"
#include "NiagaraSystem.h"
#include "MasoWater.generated.h"

#define WaterType "Water"
/**
 * 
 */
UCLASS()
class COLOSSEUM_API UMasoWater : public UObject, public IMasoInterface
{
	GENERATED_BODY()

public:
	UMasoWater();

	virtual TObjectPtr<UMaterialInterface> getMasoMaterial() override;

	virtual FString getMasoType() override;

	virtual TObjectPtr<UNiagaraSystem> getNaiagaraSystem() override;


private:
	// MasoPanelに使用するマテリアル
	TObjectPtr<UMaterialInterface> MasoMaterial;
	
	// 魔素のタイプ
	FString TYPE = WaterType;

	UPROPERTY(Transient)
	TObjectPtr<UNiagaraSystem> WaterNiagaraSystem;
};
