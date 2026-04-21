// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Battle/BuffDebuffBase.h"
#include "Battle/BattleCommon.h"
#include "SkillData.generated.h"

UENUM(BlueprintType)
enum class ESkillAbility : uint8
{
    Attack          UMETA(DisplayName = "攻撃"),
    Heal            UMETA(DisplayName = "回復"),
    Buff          UMETA(DisplayName = "バフ"),
    Debuff          UMETA(DisplayName = "デバフ"),
};

/**
 * 特技データテーブルの構造体
 */
USTRUCT(BlueprintType)
struct FSkillDataType : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    FText skill_name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    FName character;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    FName effect_id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    FName motion_id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    FName target_id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    FName element_id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    float btl_skl_attack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    float btl_skl_cost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    ESkillAbility skill_ability;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    EBuffDebuffType buffdebuff_type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    EBattleSkillIcon    icon_id;
};
