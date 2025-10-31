// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Battle/UnitBattleParameter.h"
#include "Battle/ActionResultData.h"
#include "BattleActionInterface.generated.h"

class ABattleGameMode;
// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UBattleActionInterface : public UInterface
{
	GENERATED_BODY()

};


#define BATTLE_ACTION_SKILL_SELECT_CANSEL  -2   //  スキル選択キャンセル
#define BATTLE_ACTION_SKILL_SELECT_RUN      -1  //  スキル選択実行中

/**
 * バトルアクションインターフェース
 */
class COLOSSEUM_API IBattleActionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

    //  選択パネルの設定
    //  CenterGameX     :   中心となるX座標
    //  CenterGameY     :   中心となるX座標
    //  GameMode        :   ゲームモード
    virtual void SetSelectPanel(int CenterGameX, int CenterGameY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode, uint32 SkillID) {}


    //  スキル選択開始
    //  ActionUnit      :   スキルを行使するユニット
    //  GameMode        :   ゲームモード
    virtual void SelectSkillBegin(TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode) {}

    //  スキル選択のTick
    //  -1でまだ選択が終わっていない
    //  -2でキャンセル
    //  0以上で選択したスキル
    virtual int SelectSkillTick(TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode) { return -2; }
    //  アクション計算
    //  ActionResult    :   アクション結果格納先
    //  TargetLocations :   ターゲットするゲーム座標
    //  ActionUnit      :   アクションを起こすユニット
    //  GameMode        :   ゲームモード
    //  SkillID         :   スキルID(特技を選択した時のみ有効）
    virtual void CalcAction(FActionResultData* ActionResult, const TArray<FGameLocation>& TargetLocations, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode, uint32 SkillID) {}

    //  アクション結果を反映
    //  ActionResult    :   結果格納先
    //  GameMode        :   ゲームモード
    virtual void ReflectAction(FActionResultData& ActionResult, ABattleGameMode* GameMode) {}

    //  アクション開始
    virtual void BeginAction(FActionResultData& ActionResult, ABattleGameMode* GameMode) {}

    //  アクションTick
    //  ActionResult    :   アクション結果
    //  DeltaSecounds   :   細分時間
    //  GameMode        :   ゲームモード
    //  @Return         :   true 終了 : false 続行
    virtual bool TickAction(FActionResultData& ActionResult, float DeltaSecounds, ABattleGameMode* GameMode) {return true; }
};
