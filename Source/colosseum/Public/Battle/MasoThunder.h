// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Battle/Interface/MasoInterface.h"
#include "MasoThunder.generated.h"

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


private:
	// MasoPanelに使用するマテリアル
	TObjectPtr<UMaterialInterface> MasoMaterial;
};
