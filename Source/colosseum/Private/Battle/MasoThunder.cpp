// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoThunder.h"

// ネイティブコンストラクタ
// メンバ変数の初期化
UMasoThunder::UMasoThunder()
{
	FSoftObjectPath MasoPanelMaterialPath("/Game/Battle/Material/M_MasoThunder.M_MasoThunder");
	MasoMaterial = Cast<UMaterialInterface>(MasoPanelMaterialPath.TryLoad());
}

// 水魔素のマテリアル取得
TObjectPtr<UMaterialInterface> UMasoThunder::getMasoMaterial()
{
	return MasoMaterial;
}