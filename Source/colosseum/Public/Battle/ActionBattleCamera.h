// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
class ABattleGameMode;
/**
 * カメラ制御クラス（NewObjectやnewで生成しないこと）
 */
class COLOSSEUM_API ActionBattleCamera
{
public:
	ActionBattleCamera();
	~ActionBattleCamera();


    // カメラの位置を設定
    void Initialize(ABattleGameMode* GameMode , const FVector& LookAt , float Zoom , float Secounds);

    // カメラ位置の更新
    bool RunNormal(float DeltaSeconds);

    // カメラ位置の更新（逆再生）
    bool RunReverse(float DeltaSeconds);

    FVector ToLookAtLocation; // 目標の注視点
    FVector ToEyeLocation; // 目標のカメラの位置
    float Lerp; // 補間の進行度（0.0f から 1.0f まで）
private:
    // 補間の進行度を設定
    void SetLerp(float NowLerp);
private:
    TObjectPtr<ABattleGameMode> BattleGameMode; // 戦闘ゲームモードの参照
    FVector FromLookAtLocation; // 元のカメラの注視点
    FVector FromEyeLocation; // 元のカメラの位置
    float FromZoom; // 元のズーム値

    float ToZoom; // 目標のズーム値


    float LerpTime; // 補間にかかる時間
};
