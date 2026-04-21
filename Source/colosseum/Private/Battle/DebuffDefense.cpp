// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/DebuffDefense.h"

#define BUFFICON_PATH TEXT("/Game/UI/Textures/InGame/T_Debuff_Defence.T_Debuff_Defence")
#define BATTLE_DEBUFF_SKILL_EFFECT TEXT("/Game/FixEffect/BattleEffect/Ef_Btl_Debuff.Ef_Btl_Debuff")

UDebuffDefense::UDebuffDefense()
{
	BuffDebuffIcon = LoadObject<UTexture2D>(nullptr, BUFFICON_PATH);
	BuffDebuffType = EBuffDebuffType::EBT_DEFENSE;
	BuffCategory = EBuffCategory::Debuff;
	BuffDebuffSystem = LoadObject<UNiagaraSystem>(nullptr, BATTLE_DEBUFF_SKILL_EFFECT);
}

float UDebuffDefense::CalcPower(float BasePower)
{
	float result = -BasePower * Multiplier;
	return result;
}
