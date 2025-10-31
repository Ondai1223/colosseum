// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Unit/Interface/UnitAnimationInterface.h"
#include "UnitAnimInstance.generated.h"

#define CATEGORY_UnitAnime    TEXT("ユニットアニメ")  // ユニットカテゴリ
/**
 *  ユニットのアニメーションインスタンス
 */
UCLASS()
class COLOSSEUM_API UUnitAnimInstance : public UAnimInstance , public IUnitAnimationInterface
{
	GENERATED_BODY()

public:
    //ABPのTickと同様に毎フレーム呼び出される処理のオーバーライドです。 
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;



public:


    // 待機アニメーションの再生
    virtual  void PlayAnimationWait(float ShiftTime = SHIFT_ANIME_TIME) override
    {
        ShiftAnimeTime = ShiftTime;
        IsGuard = false;
    }

    // 移動アニメーションの再生
    virtual  void PlayAnimationMove(float ShiftTime = SHIFT_ANIME_TIME) override
    {
        ShiftAnimeTime = ShiftTime;
    }

    // 攻撃のアニメーションの再生
    virtual  void PlayAnimationAttack(float ShiftTime = SHIFT_ANIME_TIME) override
    {
        ShiftAnimeTime = ShiftTime;
    }

    // ダメージのアニメーションの再生
    virtual  void PlayAnimationDamage(float ShiftTime = SHIFT_ANIME_TIME) override
    {
        ShiftAnimeTime = ShiftTime;
    }

    // 死亡のアニメーションの再生
    virtual  void PlayAnimationDeath(float ShiftTime = SHIFT_ANIME_TIME) override
    {
        ShiftAnimeTime = ShiftTime;
    }

    //  ガード
    virtual  void PlayAnimationGuard(float ShiftTime = SHIFT_ANIME_TIME) override
    {
        ShiftAnimeTime = ShiftTime;
        IsGuard = true;
    }

    //  スキルアタックの再生
    virtual  void PlayAnimationSkillAttack(float ShiftTime = SHIFT_ANIME_TIME) override
    {
        ShiftAnimeTime = ShiftTime;
    }

    //  バフの再生
    virtual  void PlayAnimationBuf(float ShiftTime = SHIFT_ANIME_TIME) override
    {
        ShiftAnimeTime = ShiftTime;
    }


public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_UnitAnime)
    float ShiftAnimeTime = SHIFT_ANIME_TIME;  // タンクのアニメーション状態

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_UnitAnime)
    bool IsGuard = false;

};
