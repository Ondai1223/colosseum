// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/BattleActionDiffence.h"
#include "Battle/BattleGameMode.h"


//  選択パネルの設定
//  CenterGameX     :   中心となるX座標
//  CenterGameY     :   中心となるX座標
//  GameMode        :   ゲームモード
void UBattleActionDiffence::SetSelectPanel(int CenterGameX, int CenterGameY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode, uint32 SkillID)
{
    GameMode->BattleSelector->SetPanel(CenterGameX, CenterGameY, true);
}


//  スキル選択開始
//  ActionUnit      :   スキルを行使するユニット
//  GameMode        :   ゲームモード
void UBattleActionDiffence::SelectSkillBegin(TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode)
{
    ;   //  防御では使用しない
}

//  スキル選択のTick
//  -1でまだ選択が終わっていない
//  -2でキャンセル
//  0以上で選択したスキル
int UBattleActionDiffence::SelectSkillTick(TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode)
{
    //  防御では使用しない
    return BATTLE_ACTION_SKILL_SELECT_CANSEL;
}
//  アクション計算
//  ActionResult    :   アクション結果格納先
//  TargetLocations :   ターゲットするゲーム座標
//  ActionUnit      :   アクションを起こすユニット
//  GameMode        :   ゲームモード
//  SkillID         :   スキルID(特技を選択した時のみ有効）
void UBattleActionDiffence::CalcAction(FActionResultData* ActionResult, const TArray<FGameLocation>& TargetLocations, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode, uint32 SkillID)
{
    ActionResult->ActionUnit = ActionUnit;
    //  防御の場合は、パラメータなし
}

//  アクション結果を反映
//  ActionResult    :   結果格納先
//  GameMode        :   ゲームモード
void UBattleActionDiffence::ReflectAction(FActionResultData& ActionResult, ABattleGameMode* GameMode)
{
    ActionResult.ActionUnit->SetActionDiffence();
    // DefencePowerのログ確認
    float defensePower = ActionResult.ActionUnit->GetDefencePower();
    UE_LOG(LogTemp, Warning, TEXT("defensePower: %f"), defensePower);
}

//  アクション開始
void UBattleActionDiffence::BeginAction(FActionResultData& ActionResult, ABattleGameMode* GameMode)
{
    ;   //  防御アニメーション開始
}

//  アクションTick
//  ActionResult    :   アクション結果
//  DeltaSecounds   :   細分時間
//  GameMode        :   ゲームモード
//  @Return         :   true 終了 : false 続行
bool UBattleActionDiffence::TickAction(FActionResultData& ActionResult, float DeltaSecounds, ABattleGameMode* GameMode)
{
    ;   //  防御アニメーション終了待ち
    return true;
}
