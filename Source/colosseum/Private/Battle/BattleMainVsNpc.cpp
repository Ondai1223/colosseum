// Fill out your copyright notice in the Description page of Project Settings.


/**
 *  プレーヤーVSNPC
 */
#include "Battle/BattleMainVsNpc.h"
#include "Battle/BattleGameMode.h"


#define NPC_MOVE_WAIT_TIME  0.25f

 // バトル開始処理
void ABattleMainVsNpc::BeginBattleState(ABattleGameMode* GameMode)
{
    //  親クラスを呼ぶ
    Super::BeginBattleState(GameMode);

    if (GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player2)
    {
        //  NPCなのでカーソル非表示(カーソルの位置の更新だけしておく)
        CursorModel->SetVisibility(false);
    }
}

// バトルループ処理
ETickBattleState ABattleMainVsNpc::TickBattleState(ABattleGameMode* GameMode, float DeltaSeconds)
{
    if (GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player2)
    {   //  NPC
        switch (BattleMainState)
        {
        case EBattleMainState::BMS_UnitSelect:
            //  ユニット選択状態
        {
            TObjectPtr<AUnitBattleParameter> NpcUnit = SelectNpcUnit(GameMode);
            if (NpcUnit)
            {
                //  ユニットが選択された
                GameMode->SelectUnitStatus(NpcUnit);
                GameMode->CanselWithOutUnitStatus(NpcUnit);
                //  ユニットコマンドの表示
                BattleMainState = EBattleMainState::BMS_CommandSelect;
                SelectUnit = NpcUnit;
                SelectUnit->SetGameMode(GameMode);
                BattleCameraAction.Initialize(GameMode, NpcUnit->Get3DLocation(), 0.5f, 0.5f); // カメラの初期化
                Player2Cursor.X = NpcUnit->GetGameX();
                Player2Cursor.Y = NpcUnit->GetGameY();
                SyncCursor();
                CursorModel->SetVisibility(true);
                return ETickBattleState::EBS_Tick;
            }
        }
            BattleMainState = EBattleMainState::MBS_EndAction;
            return ETickBattleState::EBS_Tick;

        case EBattleMainState::BMS_CommandSelect:
            //  コマンドセレクト
            if (!BattleCameraAction.RunNormal(DeltaSeconds)) {
                return ETickBattleState::EBS_Tick; // カメラアクションが実行中の場合は実行中を返す
            }
            AttackTargets.Empty();

            if (!SelectUnit->IsAttackEnd() && BattleAttackInterface)
            {
                //  攻撃対象ユニットがいるか
                BattleHelper    helper;
                TArray<FGameLocation>    Locations;
                FGameLocation           Location;

                int CenterX = SelectUnit->GetGameX();
                int CenterY = SelectUnit->GetGameY();

                int Num = -1;
                Num = helper.CalcPanelNum(CenterX + 1, CenterY);
                if (Num >= 0) {
                    Location.X = CenterX + 1;
                    Location.Y = CenterY;
                    Locations.Add(Location);
                }

                Num = helper.CalcPanelNum(CenterX - 1, CenterY);
                if (Num >= 0) {
                    Location.X = CenterX - 1;
                    Location.Y = CenterY;
                    Locations.Add(Location);
                }

                Num = helper.CalcPanelNum(CenterX , CenterY + 1);
                if (Num >= 0) {
                    Location.X = CenterX;
                    Location.Y = CenterY + 1;
                    Locations.Add(Location);
                }

                Num = helper.CalcPanelNum(CenterX, CenterY - 1);
                if (Num >= 0) {
                    Location.X = CenterX;
                    Location.Y = CenterY - 1;
                    Locations.Add(Location);
                }

                if (Locations.Num() > 0)
                {
                    FActionResultData   TestActionResult;
                    //  攻撃計算
                    BattleAttackInterface->CalcAction(&TestActionResult, Locations, SelectUnit, GameMode, 0);
                    TArray<TObjectPtr<AUnitBattleParameter>>    Targets;

                    if (TestActionResult.ActionAttackResult.AttackTargets.Num() > 0) {
                        for (TArray<FActionAttackTargetData>::TConstIterator Ite(TestActionResult.ActionAttackResult.AttackTargets) ;  Ite ; ++Ite)
                        {
                            const FActionAttackTargetData& ResultData = *Ite;

                            if (ResultData.TargetUnit->GetTeamID() == EUnitTeamID::EUTID_Team1)
                            {
                                //  ターゲットがプレーヤーなら攻撃の考慮あり
                                if (ResultData.HpDamage > 0 || ResultData.MpDamage > 0)
                                {
                                    //  HPダメージかMPダメージなら攻撃をする
                                    Targets.Add(ResultData.TargetUnit);
                                }
                            }
                        }
                    }

                    if (Targets.Num() > 0)
                    {
                        //  攻撃を選択
                        AttackTargets = Targets;
                        BattleMainState = EBattleMainState::BMS_SelectAttack;

                        BattleAttackInterface->SetSelectPanel(CenterX, CenterY, SelectUnit, GameMode, 0);

                        return ETickBattleState::EBS_Tick;
                    }
                }
            }

            if (!SelectUnit->IsMoveEnd() && BattleMoveInterface)
            {
                //  移動
                int X = SelectUnit->GetGameX();
                int Y = SelectUnit->GetGameY();

                SelectUnit->FixMove();  //  最初の値を設定しておく

                BattleMainState = EBattleMainState::BMS_SelectMove;
                if (BattleMoveInterface)
                {
                    //  移動範囲パネルを表示
                    BattleMoveInterface->SetSelectPanel(X, Y, SelectUnit, GameMode, 0);

                    FGameLocation           Location;
                    TArray<FGameLocation>    Locations;

                    for ( Y = 0; Y < GAME_LOCATION_DEPTH; ++Y)
                    {
                        for ( X = 0; X < GAME_LOCATION_WIDTH; ++X)
                        {
                            bool IsSelectPanelEnable = GameMode->BattleSelector->IsPanelEnable(X, Y);

                            
                            TObjectPtr<AUnitBattleParameter> CheckUnit = GameMode->GetUnit(X, Y);
                            if (CheckUnit == nullptr)
                            {
                                if (IsSelectPanelEnable)
                                {
                                    //  移動可能パネル追加
                                    Location.X = X;
                                    Location.Y = Y;
                                    Locations.Add(Location);
                                }
                            }
                        }
                    }

                    if (Locations.Num() > 1)
                    {
                        //  移動先計算

                        //  とりあえずランダムで移動
                        float num = static_cast<float>(Locations.Num()) - 0.1f;

                        int LocasionNum = static_cast<int>(FMath::SRand()* num);

                        Location = Locations[LocasionNum];

                        //  移動先が現在位置と同じじゃなければ移動
                        if (Location.X != SelectUnit->GetGameX() || Location.Y != Location.Y)
                        {
                            ClearActionResult();
                            Player2Cursor.X = Location.X;
                            Player2Cursor.Y = Location.Y;
                            SyncCursor();
                            //  カーソル非表示
                            CursorModel->SetVisibility(false);
                            Locations.Empty();
                            Locations.Add(Location);

                            BattleMoveInterface->CalcAction(&ActionResult, Locations, SelectUnit, GameMode, 0);
                            BattleMoveInterface->ReflectAction(ActionResult, GameMode);
                            BattleMoveInterface->BeginAction(ActionResult, GameMode);

                            MoveToLocation = Location;
                            BeginFlag = true;
                            WaitTime = NPC_MOVE_WAIT_TIME;
                            BattleMainState = EBattleMainState::BMS_SelectMove;
                            return ETickBattleState::EBS_Tick;
                        }
                        GameMode->BattleSelector->AllOffPanel();
                    }
                    //  防御へ
                }
            }


            {
                //  防御
                int X = SelectUnit->GetGameX();
                int Y = SelectUnit->GetGameY();

                Player2Cursor.X = X;
                Player2Cursor.Y = Y;
                SyncCursor();

                //  移動選択
                if (BattleDiffenceInterface)
                {
                    BattleDiffenceInterface->SetSelectPanel(X, Y, SelectUnit, GameMode, 0);
                }
                else
                {
                    GameMode->BattleSelector->SetPanel(X, Y, true);
                }

            }

            SelectUnit->EndBattleCommand(); // ユニットのコマンドキャンセルイベントを呼び出す
            BattleMainState = EBattleMainState::BMS_SelectDiffence;
            return ETickBattleState::EBS_Tick;

        case EBattleMainState::BMS_SelectAttack:    // 攻撃を選択
            //  カメラワーク
            if (!BattleCameraAction.RunReverse(DeltaSeconds)) {
                return ETickBattleState::EBS_Tick; // カメラアクションが実行中の場合は実行中を返す
            }

            if (AttackTargets.Num() > 0)
            {
                TObjectPtr<AUnitBattleParameter>    Target = AttackTargets[0];
                GameMode->SelectUnitStatus(Target);
                GameMode->BattleSelector->AllOffPanel();
                if (BattleAttackInterface)
                {
                    ClearActionResult();

                    Player2Cursor.X = Target->GetGameX();
                    Player2Cursor.Y = Target->GetGameY();
                    SyncCursor();
                    CursorModel->SetVisibility(false);
                    AttackAction(GameMode, Target->GetGameX(), Target->GetGameY());
                    BattleMainState = EBattleMainState::BMS_AttackTick;
                    return ETickBattleState::EBS_Tick;
                }
            }

            BattleMainState = EBattleMainState::MBS_EndAction;
            return ETickBattleState::EBS_Tick;


        case EBattleMainState::BMS_SelectMove:
            if (!BattleCameraAction.RunReverse(DeltaSeconds)) {
                return ETickBattleState::EBS_Tick; // カメラアクションが実行中の場合は実行中を返す
            }
            if (BeginFlag)
            {
                BeginFlag = false;
                int X = MoveToLocation.X;
                int Y = MoveToLocation.Y;

                Player2Cursor.X = X;
                Player2Cursor.Y = Y;
                SyncCursor();
                CursorModel->SetVisibility(true);
            }

            WaitTime -= DeltaSeconds;
            if (WaitTime <= 0.0f)
            {
                WaitTime = 0.0f;
                CursorModel->SetVisibility(false);
                GameMode->BattleSelector->AllOffPanel();

                BattleMainState = EBattleMainState::BMS_MoveTick;
            }
            return ETickBattleState::EBS_Tick;

        case EBattleMainState::BMS_MoveOkOrCansel:
            //  移動値を固定
            SelectUnit->FixMove();
            SelectUnit->SetActionEnd();
            BattleMainState = EBattleMainState::MBS_EndAction;
            return ETickBattleState::EBS_Tick; //


        case EBattleMainState::BMS_SelectDiffence: // 防御を選択
            if (!BattleCameraAction.RunReverse(DeltaSeconds)) {
                return ETickBattleState::EBS_Tick; // カメラアクションが実行中の場合は実行中を返す
            }

            GameMode->BattleSelector->AllOffPanel();
            Player2Cursor.X = SelectUnit->GetGameX();
            Player2Cursor.Y = SelectUnit->GetGameY();
            SyncCursor();
            ClearActionResult();
            DiffenceAction(GameMode, SelectUnit->GetGameX(), SelectUnit->GetGameY());
            BattleMainState = EBattleMainState::BMS_DiffenceTick;

            return ETickBattleState::EBS_Tick;
        }
    }

    return Super::TickBattleState(GameMode, DeltaSeconds);
}

//  バトルコマンドを開く
void ABattleMainVsNpc::BeginBattleCommand(ABattleGameMode* GameMode)
{
    if (GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player1)
    {
        Super::BeginBattleCommand(GameMode);
    }
}
//  バトルコマンドを閉じる
void ABattleMainVsNpc::EndBattleCommand(ABattleGameMode* GameMode)
{
//    if (GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player1)
    {
        Super::EndBattleCommand(GameMode);
    }
}

void ABattleMainVsNpc::SyncCursor()
{
    Player2Cursor.BeforeX = Player2Cursor.X;
    Player2Cursor.BeforeY = Player2Cursor.Y;

    BattleHelper    helper;
    FVector location = helper.CalcPanelLocation(Player2Cursor.X, Player2Cursor.Y);
    CursorModel->SetRelativeLocation(location); // カーソルの位置を更新
}

// NPCユニットの選択
TObjectPtr<AUnitBattleParameter> ABattleMainVsNpc::SelectNpcUnit(ABattleGameMode* GameMode)
{
    //  HPの低い順にユニットを選択する
    TObjectPtr<AUnitBattleParameter>    NpcUnit = nullptr;

    for (TArray<TObjectPtr<AUnitBattleParameter>>::TIterator Ite(GameMode->Player2UnitsActors) ; Ite ; ++ Ite)
    {
        TObjectPtr<AUnitBattleParameter> Unit = *Ite;
        if (!Unit->IsActionEnd())
        {
            if (!NpcUnit || NpcUnit->GetHp() < Unit->GetHp())
            {
                //  HPの低いユニットで行動可能なユニットを選択
                NpcUnit = Unit;
            }
        }
    }

    //  NPCユニットを返す
    return NpcUnit;
}



