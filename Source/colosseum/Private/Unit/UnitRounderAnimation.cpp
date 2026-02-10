// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/UnitRounderAnimation.h"

void UUnitRounderAnimation::PlayAnimationWait(float ShiftTime)
{
    Super::PlayAnimationWait(ShiftTime);
    NowAnimState = EUnitRounderAnimState::EUHAS_Idle;
    SetBoolState();
}

void UUnitRounderAnimation::PlayAnimationMove(float ShiftTime)
{
    Super::PlayAnimationWait(ShiftTime);
    NowAnimState = EUnitRounderAnimState::EUHAS_Move;
    SetBoolState();
}

void UUnitRounderAnimation::PlayAnimationAttack(float ShiftTime)
{
    Super::PlayAnimationAttack(ShiftTime);
}

void UUnitRounderAnimation::PlayAnimationDamage(float ShiftTime)
{
    Super::PlayAnimationDamage(ShiftTime);
}

void UUnitRounderAnimation::PlayAnimationDeath(float ShiftTime)
{
    Super::PlayAnimationDeath(ShiftTime);
}

void UUnitRounderAnimation::PlayAnimationGuard(float ShiftTime)
{
    Super::PlayAnimationGuard(ShiftTime);
}

void UUnitRounderAnimation::PlayAnimationSkillAttack(float ShiftTime)
{
    Super::PlayAnimationSkillAttack(ShiftTime);
}

void UUnitRounderAnimation::PlayAnimationBuf(float ShiftTime)
{
    Super::PlayAnimationBuf(ShiftTime);
}

void UUnitRounderAnimation::SetBoolState()
{
    IsIdle = (NowAnimState == EUnitRounderAnimState::EUHAS_Idle);
    IsMove = (NowAnimState == EUnitRounderAnimState::EUHAS_Move);
}