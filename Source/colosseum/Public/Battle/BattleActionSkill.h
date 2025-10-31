// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Battle/Interface/BattleActionInterface.h"
#include "BattleActionSkill.generated.h"

/**
 * 
 */
UCLASS()
class COLOSSEUM_API UBattleActionSkill : public UObject , public IBattleActionInterface
{
	GENERATED_BODY()


public:
    //  選択パネルの設定
    //  CenterGameX     :   中心となるX座標
    //  CenterGameY     :   中心となるX座標
    //  GameMode        :   ゲームモード
    virtual void SetSelectPanel(int CenterGameX, int CenterGameY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode, uint32 SkillID) override;


    //  スキル選択開始
    //  ActionUnit      :   スキルを行使するユニット
    //  GameMode        :   ゲームモード
    virtual void SelectSkillBegin(TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode) override;

    //  スキル選択のTick
    //  -1でまだ選択が終わっていない
    //  -2でキャンセル
    //  0以上で選択したスキル
    virtual int SelectSkillTick(TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode) override;
    //  アクション計算
    //  ActionResult    :   アクション結果格納先
    //  TargetLocations :   ターゲットするゲーム座標
    //  ActionUnit      :   アクションを起こすユニット
    //  GameMode        :   ゲームモード
    //  SkillID         :   スキルID(特技を選択した時のみ有効）
    virtual void CalcAction(FActionResultData* ActionResult, const TArray<FGameLocation>& TargetLocations, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode, uint32 SkillID) override;

    //  アクション結果を反映
    //  ActionResult    :   結果格納先
    //  GameMode        :   ゲームモード
    virtual void ReflectAction(FActionResultData& ActionResult, ABattleGameMode* GameMode) override;

    //  アクション開始
    virtual void BeginAction(FActionResultData& ActionResult, ABattleGameMode* GameMode) override;

    //  アクションTick
    //  ActionResult    :   アクション結果
    //  DeltaSecounds   :   細分時間
    //  GameMode        :   ゲームモード
    //  @Return         :   true 終了 : false 続行
    virtual bool TickAction(FActionResultData& ActionResult, float DeltaSecounds, ABattleGameMode* GameMode) override;

};
