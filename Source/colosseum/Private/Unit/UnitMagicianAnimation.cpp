// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/UnitMagicianAnimation.h"

void UUnitMagicianAnimation::PlayAnimationWait(float ShiftTime)
{
    Super::PlayAnimationWait(ShiftTime);
    NowAnimState = EUnitMagicianAnimState::EUHAS_Idle;
    SetBoolState();
}

void UUnitMagicianAnimation::PlayAnimationMove(float ShiftTime)
{
    Super::PlayAnimationMove(ShiftTime);
    NowAnimState = EUnitMagicianAnimState::EUHAS_Move;
    SetBoolState();
}

void UUnitMagicianAnimation::PlayAnimationAttack(float ShiftTime)
{
    Super::PlayAnimationAttack(ShiftTime);
}

void UUnitMagicianAnimation::PlayAnimationDamage(float ShiftTime)
{
    Super::PlayAnimationDamage(ShiftTime);
}

void UUnitMagicianAnimation::PlayAnimationDeath(float ShiftTime)
{
    Super::PlayAnimationDeath(ShiftTime);
}

void UUnitMagicianAnimation::PlayAnimationGuard(float ShiftTime)
{
    Super::PlayAnimationGuard(ShiftTime);
}

void UUnitMagicianAnimation::PlayAnimationSkillAttack(float ShiftTime)
{
    Super::PlayAnimationSkillAttack(ShiftTime);
}

void UUnitMagicianAnimation::PlayAnimationBuf(float ShiftTime)
{
    Super::PlayAnimationBuf(ShiftTime);
}

void UUnitMagicianAnimation::SetBoolState()
{
    IsIdle = (NowAnimState == EUnitMagicianAnimState::EUHAS_Idle);
    IsMove = (NowAnimState == EUnitMagicianAnimState::EUHAS_Move);
}

