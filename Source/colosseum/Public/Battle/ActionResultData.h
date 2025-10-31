// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
class AUnitBattleParameter;

/**
 * ゲーム座標格納用
 */
struct COLOSSEUM_API FGameLocation
{
    uint16  X;  //  X座標
    uint16  Y;  //  Y座標
};


/**
 * 攻撃情報
 */
struct COLOSSEUM_API FActionAttackTargetData
{
    TObjectPtr<AUnitBattleParameter>    TargetUnit; //  ターゲットユニット
    float   HpDamage = 0.0f;                        //HPダメージ値
    float   MpDamage = 0.0f;                        //  MPダメージ値
};

/**
 * 攻撃結果
 */
struct COLOSSEUM_API FActionAttackResultData
{
    TArray<FActionAttackTargetData> AttackTargets;
};


struct COLOSSEUM_API FActionTargetAndLocation
{
    TObjectPtr<AUnitBattleParameter>    Target;
    FGameLocation                       Location;
};


/**
 * 特技
 */
struct COLOSSEUM_API FActionSkillkResultData
{
    TArray<FActionTargetAndLocation> TargetUnits;
    uint32  SkillID;            //  スキルID
};


/**
 * 移動
 */
struct COLOSSEUM_API FActionMoveResultData
{
    FGameLocation           MoveLocation;   //  移動先
    TArray<FGameLocation>   RouteLocation;  //  移動順番格納用
};

/**
 * アクション結果格納用構造体
 */
struct COLOSSEUM_API FActionResultData
{
    //  共通
    TObjectPtr<AUnitBattleParameter>            ActionUnit; //  アクションを起こすユニット

    //  攻撃
    FActionAttackResultData                      ActionAttackResult;

    //  移動
    FActionMoveResultData                       ActionMoveResult;

    //  防御(ActionUnitの防御フラグをたてるのでデータなし)

    //  特技
    FActionSkillkResultData                     ActionSkillResult;  



};
