// Fill out your copyright notice in the Description page of Project Settings.


/*
 *  ユニットタンクのアニメーションインスタンス
 */

#include "Unit/UnitTankAnimInstance.h"

 // 待機アニメーションの再生
void UUnitTankAnimInstance::PlayAnimationWait(float ShiftTime)
{
    Super::PlayAnimationWait(ShiftTime);
    NowAnimState = EUnitTankAnimState::EUTAS_Idle;
}

// 移動アニメーションの再生
void UUnitTankAnimInstance::PlayAnimationMove(float ShiftTime)
{
    Super::PlayAnimationMove(ShiftTime);
    NowAnimState = EUnitTankAnimState::EUTAS_Move;
}

// 攻撃のアニメーションの再生
void UUnitTankAnimInstance::PlayAnimationAttack(float ShiftTime)
{
    Super::PlayAnimationAttack(ShiftTime);
}

// ダメージのアニメーションの再生
void UUnitTankAnimInstance::PlayAnimationDamage(float ShiftTime)
{
    Super::PlayAnimationDamage(ShiftTime);
}

// 死亡のアニメーションの再生
void UUnitTankAnimInstance::PlayAnimationDeath(float ShiftTime )
{
    Super::PlayAnimationDeath(ShiftTime);
}

void UUnitTankAnimInstance::PlayAnimationGuard(float ShiftTime)
{
    Super::PlayAnimationGuard(ShiftTime);

}

//  スキルアタックの再生
void UUnitTankAnimInstance::PlayAnimationSkillAttack(float ShiftTime)
{
    Super::PlayAnimationSkillAttack(ShiftTime);
}

//  バフの再生
void UUnitTankAnimInstance::PlayAnimationBuf(float ShiftTime)
{
    Super::PlayAnimationBuf(ShiftTime);

}

void UUnitTankAnimInstance::SetBoolState()
{
    IsIdle = NowAnimState == EUnitTankAnimState::EUTAS_Idle;
    IsMove = NowAnimState == EUnitTankAnimState::EUTAS_Move;
}

