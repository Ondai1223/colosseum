// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UnitAnimationInterface.generated.h"

#define SHIFT_ANIME_TIME    0.25f
 // This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUnitAnimationInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *  ユニットアニメーションインターフェース
 */
class COLOSSEUM_API IUnitAnimationInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    // 待機アニメーションの再生
    virtual  void PlayAnimationWait(float ShiftTime = SHIFT_ANIME_TIME) = 0;

    // 移動アニメーションの再生
    virtual  void PlayAnimationMove(float ShiftTime = SHIFT_ANIME_TIME) = 0;

    // 攻撃のアニメーションの再生
    virtual  void PlayAnimationAttack(float ShiftTime = SHIFT_ANIME_TIME) = 0;

    // ダメージのアニメーションの再生
    virtual  void PlayAnimationDamage(float ShiftTime = SHIFT_ANIME_TIME) = 0;

    // 死亡のアニメーションの再生
    virtual  void PlayAnimationDeath(float ShiftTime = SHIFT_ANIME_TIME) = 0;

    //  ガード
    virtual  void PlayAnimationGuard(float ShiftTime = SHIFT_ANIME_TIME) = 0;

    //  スキルアタックの再生
    virtual  void PlayAnimationSkillAttack(float ShiftTime = SHIFT_ANIME_TIME) = 0;

    //  バフの再生
    virtual  void PlayAnimationBuf(float ShiftTime = SHIFT_ANIME_TIME) = 0;


};
