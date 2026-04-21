// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/DebuffAttack.h"

#define BUFFICON_PATH TEXT("/Game/UI/Textures/InGame/T_Debuff_Attack.T_Debuff_Attack")
#define BATTLE_DEBUFF_SKILL_EFFECT TEXT("/Game/FixEffect/BattleEffect/Ef_Btl_Debuff.Ef_Btl_Debuff")

UDebuffAttack::UDebuffAttack()
{
	BuffDebuffIcon = LoadObject<UTexture2D>(nullptr, BUFFICON_PATH);
	BuffDebuffType = EBuffDebuffType::EBT_ATTACK;
	BuffCategory = EBuffCategory::Debuff;
	BuffDebuffSystem = LoadObject<UNiagaraSystem>(nullptr, BATTLE_DEBUFF_SKILL_EFFECT);
}

float UDebuffAttack::CalcPower(float BasePower)
{
	float result = -BasePower * Multiplier;
	return result;
}
