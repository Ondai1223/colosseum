// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit/UnitAnimInstance.h"
#include "UnitRounderAnimation.generated.h"

UENUM(BlueprintType)
enum class EUnitRounderAnimState : uint8
{
    EUHAS_None       UMETA(DisplayName = "なし"),    // なし
    EUHAS_Idle       UMETA(DisplayName = "待機"),    // 待機
    EUHAS_Move       UMETA(DisplayName = "移動"),    // 移動

};
/**
 * 
 */
UCLASS()
class COLOSSEUM_API UUnitRounderAnimation : public UUnitAnimInstance
{
	GENERATED_BODY()

public:
    // 待機アニメーションの再生
    virtual  void PlayAnimationWait(float ShiftTime = SHIFT_ANIME_TIME) override;

    // 移動アニメーションの再生
    virtual  void PlayAnimationMove(float ShiftTime = SHIFT_ANIME_TIME) override;

    // 攻撃のアニメーションの再生
    virtual  void PlayAnimationAttack(float ShiftTime = SHIFT_ANIME_TIME) override;

    // ダメージのアニメーションの再生
    virtual  void PlayAnimationDamage(float ShiftTime = SHIFT_ANIME_TIME) override;

    // 死亡のアニメーションの再生
    virtual  void PlayAnimationDeath(float ShiftTime = SHIFT_ANIME_TIME) override;

    //  ガード
    virtual  void PlayAnimationGuard(float ShiftTime = SHIFT_ANIME_TIME) override;

    //  スキルアタックの再生
    virtual  void PlayAnimationSkillAttack(float ShiftTime = SHIFT_ANIME_TIME) override;

    //  バフの再生
    virtual  void PlayAnimationBuf(float ShiftTime = SHIFT_ANIME_TIME) override;

    UFUNCTION(BlueprintCallable, Category = CATEGORY_UnitAnime)
    void SetBoolState();

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CATEGORY_UnitAnime)
    bool IsIdle = true;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CATEGORY_UnitAnime)
    bool IsMove = false;




    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_UnitAnime)
    EUnitRounderAnimState  NowAnimState = EUnitRounderAnimState::EUHAS_Idle;


	
};
