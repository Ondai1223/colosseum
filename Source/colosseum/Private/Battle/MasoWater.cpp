// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoWater.h"

// ネイティブコンストラクタ
// メンバ変数の初期化
UMasoWater::UMasoWater()
{
	FSoftObjectPath MasoPanelMaterialPath("/Game/Battle/Material/M_MasoWater.M_MasoWater");
	MasoMaterial = Cast<UMaterialInterface>(MasoPanelMaterialPath.TryLoad());
}

// 水魔素のマテリアル取得
TObjectPtr<UMaterialInterface> UMasoWater::getMasoMaterial()
{
	return MasoMaterial;
}