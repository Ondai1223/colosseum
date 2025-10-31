// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/BattleActionSkill.h"
#include "Battle/BattleGameMode.h"
//  選択パネルの設定
//  CenterGameX     :   中心となるX座標
//  CenterGameY     :   中心となるX座標
//  GameMode        :   ゲームモード
void UBattleActionSkill::SetSelectPanel(int CenterGameX, int CenterGameY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode, uint32 SkillID)
{
    GameMode->BattleSelector->SetPanel(CenterGameX + 1, CenterGameY, true);
    GameMode->BattleSelector->SetPanel(CenterGameX - 1, CenterGameY, true);
    GameMode->BattleSelector->SetPanel(CenterGameX, CenterGameY + 1, true);
    GameMode->BattleSelector->SetPanel(CenterGameX, CenterGameY - 1, true);
}


//  スキル選択開始
//  ActionUnit      :   スキルを行使するユニット
//  GameMode        :   ゲームモード
void UBattleActionSkill::SelectSkillBegin(TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode)
{
    // TODO: マスターデータ作成後対応。ESkillArea等を用意し、Area毎にUnitからの相対位置を計算する予定
}

//  スキル選択のTick
//  -1でまだ選択が終わっていない
//  -2でキャンセル
//  0以上で選択したスキル
int UBattleActionSkill::SelectSkillTick(TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode)
{
    // TODO: UnitのIDからマスターデータ参照でSkillID取得。SkillID→Skill情報の取得で実装する予定
    return 0;   //  とりあえず、スキル番号0を返す
}

//  アクション計算
//  ActionResult    :   アクション結果格納先
//  TargetLocations :   ターゲットするゲーム座標
//  ActionUnit      :   アクションを起こすユニット
//  GameMode        :   ゲームモード
//  SkillID         :   スキルID(特技を選択した時のみ有効）
void UBattleActionSkill::CalcAction(FActionResultData* ActionResult, const TArray<FGameLocation>& TargetLocations, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode, uint32 SkillID)
{
    ActionResult->ActionUnit = ActionUnit;
    ActionResult->ActionSkillResult.SkillID = SkillID;

    for (TArray<FGameLocation>::TConstIterator Ite(TargetLocations); Ite; ++Ite)
    {
        FActionTargetAndLocation TargetLocation;
        TargetLocation.Location.X = Ite->X;
        TargetLocation.Location.Y = Ite->Y;
        TargetLocation.Target = GameMode->GetUnit(Ite->X, Ite->Y);
        ActionResult->ActionSkillResult.TargetUnits.Add(TargetLocation);
    }


}

//  アクション結果を反映
//  ActionResult    :   結果格納先
//  GameMode        :   ゲームモード
void UBattleActionSkill::ReflectAction(FActionResultData& ActionResult, ABattleGameMode* GameMode)
{
    // TODO: 一旦BattleActionAttackに合わせておく。マスターデータ対応後、計算式を書く
    for (TArray<FActionAttackTargetData>::TIterator Ite(ActionResult.ActionAttackResult.AttackTargets); Ite; ++Ite)
    {
        float NextHp = Ite->TargetUnit->GetHp() - Ite->HpDamage;
        float NextMp = Ite->TargetUnit->GetMp() - Ite->MpDamage;

        Ite->TargetUnit->SetHp(NextHp);
        Ite->TargetUnit->SetMp(NextMp);
    }
}

//  アクション開始
void UBattleActionSkill::BeginAction(FActionResultData& ActionResult, ABattleGameMode* GameMode)
{
}

//  アクションTick
//  ActionResult    :   アクション結果
//  DeltaSecounds   :   細分時間
//  GameMode        :   ゲームモード
//  @Return         :   true 終了 : false 続行
bool UBattleActionSkill::TickAction(FActionResultData& ActionResult, float DeltaSecounds, ABattleGameMode* GameMode)
{
    // 通常攻撃に合わせておく
    for (TArray<FActionAttackTargetData>::TIterator Ite(ActionResult.ActionAttackResult.AttackTargets); Ite; ++Ite)
    {
        if (Ite->TargetUnit == nullptr)
        {
            continue;
        }
        
        if (Ite->TargetUnit->IsDead())
        {
            Ite->TargetUnit->SetVisible(false);
        }
    }

    return true;
}
