// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Battle/Interface/MasoInterface.h"
#include "NiagaraSystem.h"
#include "MasoFire.generated.h"

#define FireType "Fire"
/**
 * 
 */
UCLASS()
class COLOSSEUM_API UMasoFire : public UObject, public IMasoInterface
{
	GENERATED_BODY()

public:
	UMasoFire();

	virtual TObjectPtr<UMaterialInterface> getMasoMaterial() override;

	virtual FString getMasoType() override;

	virtual TObjectPtr<UNiagaraSystem> getNaiagaraSystem() override;

private:
	// MasoPanelに使用するマテリアル
	TObjectPtr<UMaterialInterface> MasoMaterial;

	// 魔素のタイプ
	FString TYPE = FireType;

	UPROPERTY(Transient)
	TObjectPtr<UNiagaraSystem> FireNiagaraSystem;
};
