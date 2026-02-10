// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/UnitHealerAnimation.h"

    // 待機アニメーションの再生
void UUnitHealerAnimation::PlayAnimationWait(float ShiftTime)
{
    Super::PlayAnimationWait(ShiftTime);
    NowAnimState = EUnitHealerAnimState::EUHAS_Idle;
    SetBoolState();
}

// 移動アニメーションの再生
void UUnitHealerAnimation::PlayAnimationMove(float ShiftTime)
{
    Super::PlayAnimationMove(ShiftTime);
    NowAnimState = EUnitHealerAnimState::EUHAS_Move;
    SetBoolState();
}

// 攻撃のアニメーションの再生
void UUnitHealerAnimation::PlayAnimationAttack(float ShiftTime)
{
    Super::PlayAnimationAttack(ShiftTime);
}

// ダメージのアニメーションの再生
void UUnitHealerAnimation::PlayAnimationDamage(float ShiftTime)
{
    Super::PlayAnimationDamage(ShiftTime);
}

// 死亡のアニメーションの再生
void UUnitHealerAnimation::PlayAnimationDeath(float ShiftTime)
{
    Super::PlayAnimationDeath(ShiftTime);
}

//  ガード
void UUnitHealerAnimation::PlayAnimationGuard(float ShiftTime)
{
    Super::PlayAnimationGuard(ShiftTime);
}

//  スキルアタックの再生
void UUnitHealerAnimation::PlayAnimationSkillAttack(float ShiftTime)
{
    Super::PlayAnimationSkillAttack(ShiftTime);
}

//  バフの再生
void UUnitHealerAnimation::PlayAnimationBuf(float ShiftTime)
{
    Super::PlayAnimationBuf(ShiftTime);
}


void UUnitHealerAnimation::SetBoolState()
{
    IsIdle = (NowAnimState == EUnitHealerAnimState::EUHAS_Idle);
    IsMove = (NowAnimState == EUnitHealerAnimState::EUHAS_Move);
}


