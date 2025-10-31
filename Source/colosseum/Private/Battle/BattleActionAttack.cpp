// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle/BattleActionAttack.h"
#include "Battle/BattleGameMode.h"

#define DEFFENCE_PARAMETER  15 //防御力のパラメータ
//  選択パネルの設定
//  CenterGameX     :   中心となるX座標
//  CenterGameY     :   中心となるX座標
//  GameMode        :   ゲームモード
void UBattleActionAttack::SetSelectPanel(int CenterGameX, int CenterGameY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode, uint32 SkillID)
{
    //  攻撃範囲の設定
    GameMode->BattleSelector->SetPanel(CenterGameX + 1, CenterGameY,true);
    GameMode->BattleSelector->SetPanel(CenterGameX - 1, CenterGameY,true);
    GameMode->BattleSelector->SetPanel(CenterGameX, CenterGameY + 1,true);
    GameMode->BattleSelector->SetPanel(CenterGameX, CenterGameY - 1,true);
}


//  スキル選択開始
//  ActionUnit      :   スキルを行使するユニット
//  GameMode        :   ゲームモード
void UBattleActionAttack::SelectSkillBegin(TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode)
{
    ;   //  攻撃では使用しない
}

//  スキル選択のTick
//  -1でまだ選択が終わっていない
//  -2でキャンセル
//  0以上で選択したスキル
int UBattleActionAttack::SelectSkillTick(TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode)
{
    ;   //  攻撃では使用しない
    return BATTLE_ACTION_SKILL_SELECT_CANSEL;
}

//  アクション計算
//  ActionResult    :   アクション結果格納先
//  TargetLocations :   ターゲットするゲーム座標
//  ActionUnit      :   アクションを起こすユニット
//  GameMode        :   ゲームモード
//  SkillID         :   スキルID(特技を選択した時のみ有効）
void UBattleActionAttack::CalcAction(FActionResultData* ActionResult, const TArray<FGameLocation>& TargetLocations, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode, uint32 SkillID)
{
    //  ダメージ計算
    //  共通のアクションユニットの設定
    ActionResult->ActionUnit = ActionUnit;

    for (TArray<FGameLocation>::TConstIterator Ite(TargetLocations); Ite; ++Ite)
    {
        TObjectPtr Target = GameMode->GetUnit(Ite->X, Ite->Y);
        if (Target) {
            FActionAttackTargetData TargetData;
            TargetData.TargetUnit = Target;

            /* ここから */
            // UnitBattleParameterからUnitのパラメータを取得して計算する.
            // 
            // 攻撃する側: ActionUnit(SelectUnit) 攻撃力を参照
            // 攻撃を受ける側: Target 防御力を参照
            // ダメージ計算： 攻撃力(行)/防御力(被)＊攻撃倍率(15)＝ダメージ
            // 通常攻撃ではスキルを使用しないので,MPは減らない.
            //

            float attackPower = ActionUnit->GetAttackPower();
            float defensePower = Target->GetDefencePower();
            float calculatedDamage = attackPower / defensePower * DEFFENCE_PARAMETER;
            
            // Clamp(変数, Min, Max);変数の取りうる値を制限する.
            FMath::Clamp(calculatedDamage, 0, Target->GetMaxHp());
           

            UE_LOG(LogTemp, Warning, TEXT("calculatedDamage: %f, attackPower: %f, defensePower: %f"), calculatedDamage, attackPower, defensePower);

            TargetData.HpDamage = calculatedDamage;    //  HPダメージ
            /* ここまで */

            TargetData.MpDamage = 0.0f;
            ActionResult->ActionAttackResult.AttackTargets.Add(TargetData);
        }
    }
}

//  アクション結果を反映
//  ActionResult    :   結果格納先
//  GameMode        :   ゲームモード
void UBattleActionAttack::ReflectAction(FActionResultData& ActionResult, ABattleGameMode* GameMode)
{
    //  数値の反映
    //  ここでは数値の反映だけを行います。アニメーションなどはBeginAction,TickAction内で行ってください

    for (TArray<FActionAttackTargetData>::TIterator Ite(ActionResult.ActionAttackResult.AttackTargets); Ite; ++Ite)
    {
        float initHp = Ite->TargetUnit->GetHp();
        float NextHp = Ite->TargetUnit->GetHp() - Ite->HpDamage;
        float NextMp = Ite->TargetUnit->GetMp() - Ite->MpDamage;

        Ite->TargetUnit->SetHp(NextHp);
        Ite->TargetUnit->SetMp(NextMp);
        UE_LOG(LogTemp, Warning, TEXT("Hp: %f--> NextHp: %f"), initHp, NextHp);
    }
}

//  アクション開始
void UBattleActionAttack::BeginAction(FActionResultData& ActionResult, ABattleGameMode* GameMode)
{
    //  アニメーションなどの開始
}

//  アクションTick
//  ActionResult    :   アクション結果
//  DeltaSecounds   :   細分時間
//  GameMode        :   ゲームモード
//  @Return         :   true 終了 : false 続行
bool UBattleActionAttack::TickAction(FActionResultData& ActionResult, float DeltaSecounds, ABattleGameMode* GameMode)
{
    //  アニメーションなどの終了待ち

    for (TArray<FActionAttackTargetData>::TIterator Ite(ActionResult.ActionAttackResult.AttackTargets); Ite; ++Ite)
    {
        //  お前はもう死んでいる
        if (Ite->TargetUnit->IsDead()) {
#if 0
            Ite->TargetUnit->SetVisible(false);
#else
            Ite->TargetUnit->PlayAnimationDeath();
#endif
        }
    }

    return true;    //  trueで終了
}
