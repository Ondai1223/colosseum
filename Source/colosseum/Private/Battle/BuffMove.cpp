// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/BuffMove.h"

#define BUFFICON_PATH TEXT("/Game/UI/Textures/InGame/T_Buff_Move.T_Buff_Move")
#define BATTLE_BUFF_SKILL_EFFECT TEXT("/Game/FixEffect/BattleEffect/Ef_Btl_Buff.Ef_Btl_Buff")

UBuffMove::UBuffMove()
{
	BuffDebuffIcon = LoadObject<UTexture2D>(nullptr, BUFFICON_PATH);
	BuffDebuffType = EBuffDebuffType::EBT_MOVE;
	BuffCategory = EBuffCategory::Buff;
	BuffDebuffSystem = LoadObject<UNiagaraSystem>(nullptr, BATTLE_BUFF_SKILL_EFFECT);
}

float UBuffMove::CalcPower(float BasePower)
{
	float result = +Multiplier;
	return result;
}
