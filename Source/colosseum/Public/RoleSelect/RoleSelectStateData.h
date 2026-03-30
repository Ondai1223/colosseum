// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RoleSelect/RoleSelectDefines.h"
#include "RoleSelect/RoleSelectENums.h"
#include "Unit/UnitData.h"
#include "RoleSelectStateData.generated.h"
/**
 * ロール選択で使用するデータ(通信用:クライアントで使うデータ)
 */
USTRUCT(BlueprintType)
struct COLOSSEUM_API FRoleSelectStateData
{
    GENERATED_BODY();

    //-------------------------------------------------------------
    //  どのデータタイプを使用しているか
    ERoleSelectDataType DataType = ERoleSelectDataType::ERSDT_None;

    //-------------------------------------------------------------
    //  ネゴシエーション(ERSDT_Nagosiation)
    FString SyncServerString = ""; // 同期用の文字列()

    //-------------------------------------------------------------
    //  スロットステート(ERSDT_SlotState)
    ERpoleSelectSlotState   SlotState = ERpoleSelectSlotState::ERSSS_None; //  スロットの状態

    //-------------------------------------------------------------
    //  スロットインデックス(ERSDT_SlotSelectIndex)
    int32 SlotSelectIndex = 0;       // スロット選択のインデックス

    //-------------------------------------------------------------
    //  出撃準備完了(ERSDT_GetReady)
    bool GetReady = false;     // 準備完了フラグ


    //-------------------------------------------------------------
    //-------------------------------------------------------------
    //  ロール選択ステート(ERSDT_RoleSelect)
    ERoleSelectState RoleSelectState = ERoleSelectState::ERS_None; // ロール選択の状態

    //-------------------------------------------------------------
    //  ロール選択（現在のジョブ）:(ERSDT_RoleSelectIndex)
    int32 RoleSelectIndex = 0; // 選択したインデックス


    //-------------------------------------------------------------
    //  ロール選択（現在のジョブ）:(ERSDT_RoleSelectJob)
    EUnitJob RoleSelectJob = EUnitJob::EUJ_None; // 選択した職業

    //-------------------------------------------------------------
    //  ロール選択（前回のジョブ）:(ERSDT_RoleSelectJobBefore)
    EUnitJob RoleSelectJobBefore = EUnitJob::EUJ_None;

    //-------------------------------------------------------------
    //  前回のジョブから遷移するときの時間(ERSDT_RoleSelectTime)
    float RoleSelectTime = 1.0f; // ロール選択の時間

    //-------------------------------------------------------------
    //  ジョブ遷移時間(ERSDT_RoleSelectTimeMax)
    float RoleSelectTimeMax = 1.0f; // ロール選択の時間の最大値

    //-------------------------------------------------------------
    //-------------------------------------------------------------
    //  ユニット配置(ERSDT_ArrangementState)
    EAUState ArrangementUnitState = EAUState::EAUState_None; // ユニット配置の状態

    //-------------------------------------------------------------
    //  ユニット配置X座標(ERSDT_ArrangementStartX)
    int32 ArrangementStartPosX = 1; // ユニット配置のX座標

    //-------------------------------------------------------------
    //  ユニット配置X座標(ERSDT_ArrangementStartY)
    int32 ArrangementStartPosY = 0; // ユニット配置のY座標





    //-------------------------------------------------------------
    // このステートを維持ステートに適用するかのフラグ
    //-------------------------------------------------------------
    bool IsStayApply = false;    // 適用するかのフラグ


    //-------------------------------------------------------------
    // コールID
    //-------------------------------------------------------------
    ERoleSelectCallID   CallID = ERoleSelectCallID::ERSCID_None;
};
