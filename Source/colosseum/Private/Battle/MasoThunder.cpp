// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoThunder.h"

// ネイティブコンストラクタ
// メンバ変数の初期化
UMasoThunder::UMasoThunder()
{
	FSoftObjectPath MasoPanelMaterialPath("/Game/Battle/Material/M_MasoThunder.M_MasoThunder");
	MasoMaterial = Cast<UMaterialInterface>(MasoPanelMaterialPath.TryLoad());
	ThunderNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/FixEffect/magice_essence/Ef_Elm_Thunder_02.Ef_Elm_Thunder_02"));
}

// 雷魔素のマテリアル取得
TObjectPtr<UMaterialInterface> UMasoThunder::getMasoMaterial()
{
	return MasoMaterial;
}

FString UMasoThunder::getMasoType()
{
	return TYPE;
}

TObjectPtr<UNiagaraSystem> UMasoThunder::getNaiagaraSystem()
{
	return ThunderNiagaraSystem;
}
