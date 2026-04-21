// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/DebuffMove.h"

#define BUFFICON_PATH TEXT("/Game/UI/Textures/InGame/T_Debuff_Move.T_Debuff_Move")
#define BATTLE_DEBUFF_SKILL_EFFECT TEXT("/Game/FixEffect/BattleEffect/Ef_Btl_Debuff.Ef_Btl_Debuff")


UDebuffMove::UDebuffMove()
{
	BuffDebuffIcon = LoadObject<UTexture2D>(nullptr, BUFFICON_PATH);
	BuffDebuffType = EBuffDebuffType::EBT_MOVE;
	BuffCategory = EBuffCategory::Debuff;
	BuffDebuffSystem = LoadObject<UNiagaraSystem>(nullptr, BATTLE_DEBUFF_SKILL_EFFECT);
}


float UDebuffMove::CalcPower(float BasePower)
{
	float result =  -Multiplier;
	return result;
}
