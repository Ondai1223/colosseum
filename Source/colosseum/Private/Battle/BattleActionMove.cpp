// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle/BattleActionMove.h"
#include "Battle/BattleHelper.h"
#include "Battle/BattleGameMode.h"

#define BATTLE_UNIT_MOVE_TIME   0.5f    //  移動時間

//  選択パネルの設定
//  CenterGameX     :   中心となるX座標
//  CenterGameY     :   中心となるX座標
//  GameMode        :   ゲームモード
void UBattleActionMove::SetSelectPanel(int CenterGameX, int CenterGameY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode, uint32 SkillID)
{
    //  移動力を取得
    uint8   Moveliy = ActionUnit->GetMobility();
    uint8   CenterX = ActionUnit->GetGameX();
    uint8   CenterY = ActionUnit->GetGameY();

    //  操作ユニットのパネルは常にtrue
    GameMode->BattleSelector->SetPanel(CenterX, CenterY, true);

    for (uint8 Y = 0; Y < GAME_LOCATION_DEPTH; ++Y)
    {
        for (uint8 X = 0; X < GAME_LOCATION_WIDTH; ++X)
        {
            uint8 Cost = FMath::Abs(X - CenterX) + FMath::Abs(Y - CenterY);
            if (Moveliy >= Cost)
            {
                //  行動範囲内
                if (Cost != 0)
                {
                    //  移動コストが０意外の場合、ユニットがいるか調べる
                    TObjectPtr<AUnitBattleParameter> Unit = GameMode->GetUnit(X, Y);
                    if (!Unit)
                    {
                        GameMode->BattleSelector->SetPanel(X, Y, true);
                    }
                }
            }
        }
    }
    //  敵陣地の侵入は許さない
    GameMode->BattleSelector->SetSelectPanelTeamValid((ActionUnit->GetTeamID() == EUnitTeamID::EUTID_Team1) ? EUnitTeamID::EUTID_Team2 : EUnitTeamID::EUTID_Team1, false);

}


//  スキル選択開始
//  ActionUnit      :   スキルを行使するユニット
//  GameMode        :   ゲームモード
void UBattleActionMove::SelectSkillBegin(TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode)
{
    ;   //  移動では使わない
}

//  スキル選択のTick
//  -1でまだ選択が終わっていない
//  -2でキャンセル
//  0以上で選択したスキル
int UBattleActionMove::SelectSkillTick(TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode)
{
    return BATTLE_ACTION_SKILL_SELECT_CANSEL;   //  移動では使わない
}
//  アクション計算
//  ActionResult    :   アクション結果格納先
//  TargetLocations :   ターゲットするゲーム座標
//  ActionUnit      :   アクションを起こすユニット
//  GameMode        :   ゲームモード
//  SkillID         :   スキルID(特技を選択した時のみ有効）
void UBattleActionMove::CalcAction(FActionResultData* ActionResult, const TArray<FGameLocation>& TargetLocations, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode, uint32 SkillID)
{
    ActionResult->ActionUnit = ActionUnit;
    uint8   Moveliy = ActionUnit->GetMobility();

    //  到着ゲーム座標を格納
    ActionResult->ActionMoveResult.MoveLocation.X = TargetLocations[0].X;
    ActionResult->ActionMoveResult.MoveLocation.Y = TargetLocations[0].Y;

    uint8   CenterX = ActionUnit->GetGameX();
    uint8   CenterY = ActionUnit->GetGameY();

    //  単純なルート計算
    FGameLocation   Location;

    //  スタート地点格納
    Location.X = CenterX;
    Location.Y = CenterY;

    //  X軸の方が広いので、X軸移動を先にする
    bool IsXMoveAdd = (ActionResult->ActionMoveResult.MoveLocation.X >= Location.X);
    bool IsYMoveAdd = (ActionResult->ActionMoveResult.MoveLocation.Y >= Location.Y);
    for (;; (IsXMoveAdd) ? ++Location.X : --Location.X)
    {
        ActionResult->ActionMoveResult.RouteLocation.Add(Location);
        if (ActionResult->ActionMoveResult.MoveLocation.X == Location.X) {
            break;
        }
    }

    if (ActionResult->ActionMoveResult.MoveLocation.Y != Location.Y) {
        for ((IsYMoveAdd) ? ++Location.Y : --Location.Y;; (IsYMoveAdd) ? ++Location.Y : --Location.Y)
        {
            ActionResult->ActionMoveResult.RouteLocation.Add(Location);
            if (ActionResult->ActionMoveResult.MoveLocation.Y == Location.Y) {
                break;
            }
        }
    }
}

//  アクション結果を反映
//  ActionResult    :   結果格納先
//  GameMode        :   ゲームモード
void UBattleActionMove::ReflectAction(FActionResultData& ActionResult, ABattleGameMode* GameMode)
{
    //  内部のゲーム座標だけ計算
    ActionResult.ActionUnit->SetGameX(ActionResult.ActionMoveResult.MoveLocation.X);
    ActionResult.ActionUnit->SetGameY(ActionResult.ActionMoveResult.MoveLocation.Y);
}

//  アクション開始
void UBattleActionMove::BeginAction(FActionResultData& ActionResult, ABattleGameMode* GameMode)
{
    //  移動開始
    RouteNumMax = ActionResult.ActionMoveResult.RouteLocation.Num();
    RouteNum = 1;
    Lerp = 0.0f;
}

//  アクションTick
//  ActionResult    :   アクション結果
//  DeltaSecounds   :   細分時間
//  GameMode        :   ゲームモード
//  @Return         :   true 終了 : false 続行
bool UBattleActionMove::TickAction(FActionResultData& ActionResult, float DeltaSecounds, ABattleGameMode* GameMode)
{
    BattleHelper    helper;
    if (RouteNum >= RouteNumMax)
    {
        //  移動終了
        ActionResult.ActionUnit->Set3DLocation(helper.CalcPanelLocation(ActionResult.ActionMoveResult.MoveLocation.X, ActionResult.ActionMoveResult.MoveLocation.Y));
    }
    else 
    {
        //  移動中
        FGameLocation   Now, Next;
        Now = ActionResult.ActionMoveResult.RouteLocation[RouteNum - 1];
        Next = ActionResult.ActionMoveResult.RouteLocation[RouteNum];

        //  3D座標算出
        FVector NowLocation = helper.CalcPanelLocation(Now.X, Now.Y);
        FVector NextLocasion = helper.CalcPanelLocation(Next.X, Next.Y);

        Lerp += DeltaSecounds / BATTLE_UNIT_MOVE_TIME;
        if (Lerp >= 1.0f)
        {   //  マスの中心へ
            Lerp = 0.0f;
            ++RouteNum;
            ActionResult.ActionUnit->Set3DLocation(NextLocasion);
        }
        else
        {
            //  補間値から3D座標算出
            ActionResult.ActionUnit->Set3DLocation((NextLocasion - NowLocation) * Lerp + NowLocation);
        }
        return false;
    }
    return true;
}
