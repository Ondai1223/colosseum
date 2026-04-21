// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle/BattleActionMove.h"
#include "Battle/BattleHelper.h"

#ifndef ENABLE_BATTLE_ACTION_INTERFACE_GAME_MODE_PROXY
#include "Battle/BattleGameMode.h"
#else
#include "Battle/BattleGameModeProxy.h"
#endif
#define BATTLE_UNIT_MOVE_TIME   1.0f    //  移動時間
#define BATTLE_UNIT_ROTATE_TIME 0.25f    //  回転時間

//  選択パネルの設定
//  CenterGameX     :   中心となるX座標
//  CenterGameY     :   中心となるX座標
//  GameMode        :   ゲームモード
void UBattleActionMove::SetSelectPanel(int CenterGameX, int CenterGameY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleActionGameModeProxy* GameMode, const FSkillDataType& SkillData)
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
void UBattleActionMove::SelectSkillBegin(TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleActionGameModeProxy* GameMode)
{
    ;   //  移動では使わない
}

//  スキル選択のTick
//  -1でまだ選択が終わっていない
//  -2でキャンセル
//  0以上で選択したスキル
int UBattleActionMove::SelectSkillTick(TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleActionGameModeProxy* GameMode, FSkillDataType& OutSkillData)
{
    return BATTLE_ACTION_SKILL_SELECT_CANSEL;   //  移動では使わない
}
//  アクション計算
//  ActionResult    :   アクション結果格納先
//  TargetLocations :   ターゲットするゲーム座標
//  ActionUnit      :   アクションを起こすユニット
//  GameMode        :   ゲームモード
//  SkillID         :   スキルID(特技を選択した時のみ有効）
void UBattleActionMove::CalcAction(FActionResultData* ActionResult, const TArray<FGameLocation>& TargetLocations, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleActionGameModeProxy* GameMode, const FSkillDataType& SkillData)
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
void UBattleActionMove::ReflectAction(FActionResultData& ActionResult, ABattleActionGameModeProxy* GameMode)
{
    //  内部のゲーム座標だけ計算
    ActionResult.ActionUnit->SetGameX(ActionResult.ActionMoveResult.MoveLocation.X);
    ActionResult.ActionUnit->SetGameY(ActionResult.ActionMoveResult.MoveLocation.Y);
}

//  アクション開始
void UBattleActionMove::BeginAction(FActionResultData& ActionResult, ABattleActionGameModeProxy* GameMode)
{
    //  移動開始
    RouteNumMax = ActionResult.ActionMoveResult.RouteLocation.Num();
    RouteNum = 1;
    Lerp = 0.0f;

    StartRotation = ActionResult.ActionUnit->GetQuaternion();
    StartRotation.Normalize();

    MoveState = EMoveActionState::EMas_None;
    if (RouteNum < RouteNumMax)
    {

        BattleHelper    helper;

        // 移動するのでアニメーション
        ActionResult.ActionUnit->PlayAnimationMove();



        NowRotation = StartRotation;

        FVector2D NowPos = FVector2D(ActionResult.ActionMoveResult.RouteLocation[0].X, ActionResult.ActionMoveResult.RouteLocation[0].Y);
        FVector2D NextPos = FVector2D(ActionResult.ActionMoveResult.RouteLocation[1].X, ActionResult.ActionMoveResult.RouteLocation[1].Y);
        if (helper.CalcLookAtRotation(&NextRotation, NowPos, NextPos))
        {
            //  向き変更あり
            NextRotation.Normalize();
            MoveState = EMoveActionState::EMas_RotUnit;
        }
        else
        {
            //  向き変更なし
            MoveState = EMoveActionState::EMas_Moving;
        }

    }
    else
    {
        //  移動なし
        MoveState = EMoveActionState::EMas_None;
    }
}

//  アクションTick
//  ActionResult    :   アクション結果
//  DeltaSecounds   :   細分時間
//  GameMode        :   ゲームモード
//  @Return         :   true 終了 : false 続行
bool UBattleActionMove::TickAction(FActionResultData& ActionResult, float DeltaSecounds, ABattleActionGameModeProxy* GameMode)
{
    BattleHelper    helper;


    switch (MoveState)
    {
    case EMoveActionState::EMas_None:
        //  落下
    case EMoveActionState::EMas_MoveEnd:
        ActionResult.ActionUnit->PlayAnimationWait();
        MoveState = EMoveActionState::EMas_None;
        return true;
    case EMoveActionState::EMas_MoveRotEnd:
        if (NowRotation == StartRotation)
        {
            //  向きが同じなら終了
            MoveState = EMoveActionState::EMas_MoveEnd;
        }
        else
        {
            //  ユニットを敵側に向かせる
            Lerp += DeltaSecounds / BATTLE_UNIT_ROTATE_TIME;
            if (Lerp >= 1.0f)
            {
                Lerp = 0.0f;
                NowRotation = StartRotation;
                NextRotation = StartRotation;
                ActionResult.ActionUnit->SetQuaternion(StartRotation);
                MoveState = EMoveActionState::EMas_MoveEnd;
            }
            else
            {
                FQuat   Rot = FQuat::Slerp(NowRotation, NextRotation, Lerp);
                Rot.Normalize();
                ActionResult.ActionUnit->SetQuaternion(Rot);
            }

        }
        break;
    case EMoveActionState::EMas_Moving:
        //  移動中
    {

        if (RouteNum  >= RouteNumMax)
        {
            //  移動終了
            ActionResult.ActionUnit->Set3DLocation(helper.CalcPanelLocation(ActionResult.ActionMoveResult.MoveLocation.X, ActionResult.ActionMoveResult.MoveLocation.Y));

            NextRotation = StartRotation;
            NowRotation = ActionResult.ActionUnit->GetQuaternion();
            MoveState = EMoveActionState::EMas_MoveRotEnd;
            break;
        }
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
            if (RouteNum >= RouteNumMax)
            {
                //  移動終了
                NextRotation = StartRotation;
                NowRotation = ActionResult.ActionUnit->GetQuaternion();
                MoveState = EMoveActionState::EMas_MoveRotEnd;
                break;
            }
            //  次のマスへ向かう準備
            Now = ActionResult.ActionMoveResult.RouteLocation[RouteNum - 1];
            Next = ActionResult.ActionMoveResult.RouteLocation[RouteNum];
            FVector2D NowPos = FVector2D(Now.X, Now.Y);
            FVector2D NextPos = FVector2D(Next.X, Next.Y);
            if (helper.CalcLookAtRotation(&NextRotation, NowPos, NextPos))
            {
                //  向き変更あり
                NextRotation.Normalize();
                MoveState = EMoveActionState::EMas_RotUnit;
            }
        }
        else
        {
            //  補間値から3D座標算出
            ActionResult.ActionUnit->Set3DLocation((NextLocasion - NowLocation) * Lerp + NowLocation);
        }
    }
        break;
    case EMoveActionState::EMas_RotUnit:
        //  ユニット回転中

        Lerp += DeltaSecounds / BATTLE_UNIT_ROTATE_TIME;

        if (Lerp >= 1.0f)
        {   //  回転終了
            Lerp = 0.0f;
            NowRotation = NextRotation;
            ActionResult.ActionUnit->SetQuaternion(NextRotation);
            MoveState = EMoveActionState::EMas_Moving;

            if (RouteNum >= RouteNumMax)
            {
                NextRotation = StartRotation;
                NowRotation = ActionResult.ActionUnit->GetQuaternion();
                MoveState = EMoveActionState::EMas_MoveRotEnd;
            }
        }
        else
        {
            //  補間値から回転算出
            FQuat   Rot = FQuat::Slerp(NowRotation, NextRotation, Lerp);
            Rot.Normalize();
            ActionResult.ActionUnit->SetQuaternion(Rot);
        }

        break;

    }
    return false;

}
