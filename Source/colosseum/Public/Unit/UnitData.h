// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitJob.h"
#include "UnitTeamID.h"
#include "UnitData.generated.h"
/**
 *  ユニットデータ
 */
USTRUCT(BlueprintType)
struct FUnitData
{
    GENERATED_BODY()

    float HpMax = 100; // ユニットの体力
    float MpMax = 100; // ユニットのマナ
    float AttackPower = 50; // ユニットの攻撃力
    float DefensePower = 20; // ユニットの防御力
    float Mobility = 2; // ユニットの移動力
    EUnitJob Job = EUnitJob::EUJ_None; // ユニットのジョブ
    EUnitTeamID TeamID = EUnitTeamID::EUTID_None;   //  ユニットのチームID
    uint8 StartPosX = 0;    // ユニットの開始位置X座標
    uint8 StartPosY = 0;    // ユニットの開始位置Y座標

};
