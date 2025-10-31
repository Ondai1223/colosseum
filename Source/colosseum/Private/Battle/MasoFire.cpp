// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoFire.h"

// ネイティブコンストラクタ
// メンバ変数の初期化
UMasoFire::UMasoFire()
{
	FSoftObjectPath MasoPanelMaterialPath("/Game/Battle/Material/M_MasoFire.M_MasoFire");
	MasoMaterial = Cast<UMaterialInterface>(MasoPanelMaterialPath.TryLoad());
}

// 水魔素のマテリアル取得
TObjectPtr<UMaterialInterface> UMasoFire::getMasoMaterial()
{
	return MasoMaterial;
}
