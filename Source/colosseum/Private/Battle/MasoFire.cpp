// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoFire.h"

// ネイティブコンストラクタ
// メンバ変数の初期化
UMasoFire::UMasoFire()
{
	FSoftObjectPath MasoPanelMaterialPath("/Game/Battle/Material/M_MasoFire.M_MasoFire");
	MasoMaterial = Cast<UMaterialInterface>(MasoPanelMaterialPath.TryLoad());

	FireNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/FixEffect/magice_essence/Ef_Elm_Fire_02.Ef_Elm_Fire_02"));
}

// 炎魔素のマテリアル取得
TObjectPtr<UMaterialInterface> UMasoFire::getMasoMaterial()
{
	return MasoMaterial;
}

FString UMasoFire::getMasoType()
{
	return TYPE;
}

TObjectPtr<UNiagaraSystem> UMasoFire::getNaiagaraSystem()
{
	return FireNiagaraSystem;
}
