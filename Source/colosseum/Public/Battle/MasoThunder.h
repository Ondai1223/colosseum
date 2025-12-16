// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Battle/Interface/MasoInterface.h"
#include "NiagaraSystem.h"
#include "MasoThunder.generated.h"

#define ThunderType "Thunder"
/**
 * 
 */
UCLASS()
class COLOSSEUM_API UMasoThunder : public UObject, public IMasoInterface
{
	GENERATED_BODY()
	
public:
	UMasoThunder();

	virtual TObjectPtr<UMaterialInterface> getMasoMaterial() override;

	virtual FString getMasoType() override;

	virtual TObjectPtr<UNiagaraSystem> getNaiagaraSystem() override;

private:
	// MasoPanelに使用するマテリアル
	TObjectPtr<UMaterialInterface> MasoMaterial;

	// 魔素のタイプ
	FString TYPE = ThunderType;

	UPROPERTY(Transient)
	TObjectPtr<UNiagaraSystem> ThunderNiagaraSystem;
};
