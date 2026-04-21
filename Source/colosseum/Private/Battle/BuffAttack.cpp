// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/BuffAttack.h"

#define BUFFICON_PATH TEXT("/Game/UI/Textures/InGame/T_Buff_Attack.T_Buff_Attack")
#define BATTLE_BUFF_SKILL_EFFECT TEXT("/Game/FixEffect/BattleEffect/Ef_Btl_Buff.Ef_Btl_Buff")

UBuffAttack::UBuffAttack()
{
	BuffDebuffIcon = LoadObject<UTexture2D>(nullptr, BUFFICON_PATH);
	BuffDebuffType = EBuffDebuffType::EBT_ATTACK;
	BuffCategory = EBuffCategory::Buff;
	BuffDebuffSystem = LoadObject<UNiagaraSystem>(nullptr, BATTLE_BUFF_SKILL_EFFECT);
}

float UBuffAttack::CalcPower(float BasePower)
{
	float result = BasePower * Multiplier;
	return result;
}
