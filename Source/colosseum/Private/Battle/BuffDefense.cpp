// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/BuffDefense.h"

#define BUFFICON_PATH TEXT("/Game/UI/Textures/InGame/T_Buff_Defence.T_Buff_Defence")
#define BATTLE_BUFF_SKILL_EFFECT TEXT("/Game/FixEffect/BattleEffect/Ef_Btl_Buff.Ef_Btl_Buff")

UBuffDefense::UBuffDefense()
{
	BuffDebuffIcon = LoadObject<UTexture2D>(nullptr, BUFFICON_PATH);
	BuffDebuffType = EBuffDebuffType::EBT_DEFENSE;
	BuffCategory = EBuffCategory::Buff;
	BuffDebuffSystem = LoadObject<UNiagaraSystem>(nullptr, BATTLE_BUFF_SKILL_EFFECT);
}

float UBuffDefense::CalcPower(float BasePower)
{
	float result = BasePower * Multiplier;
	return result;
}
