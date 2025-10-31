// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle/BattleMain.h"
#include "Battle/BattleGameMode.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ABattleMain::ABattleMain()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CursorModel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CursorMesh"));

    if (CursorModel)
    {
        RootComponent = CursorModel; // メッシュコンポーネントをルートコンポーネントに設定
    }

    Player1Cursor.X = Player1Cursor.BeforeX = 1;
    Player1Cursor.Y = Player1Cursor.BeforeY = 1;

    Player2Cursor.X = Player2Cursor.BeforeX = 1;
    Player2Cursor.Y = Player2Cursor.BeforeY = 2;
}

// Called when the game starts or when spawned
void ABattleMain::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ABattleMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Called to bind functionality to input
/*
void ABattleMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
*/

void ABattleMain::BeginBattleState(ABattleGameMode* GameMode)
{
    // 戦闘開始前の先制後攻の決定イベントの実装
    BattleMainState = EBattleMainState::BMS_UnitSelect; // BattleMainの状態を設定
    CursorModel->SetVisibility(true);

    FVector location;
    if (GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player1) {
        location = GameMode->GetBattleCursorLocation(Player1Cursor.X, Player1Cursor.Y); // プレイヤー1のカーソル位置を取得
    }
    else {
        location = GameMode->GetBattleCursorLocation(Player2Cursor.X, Player2Cursor.Y); // プレイヤー1のカーソル位置を取得
    }

    CursorModel->SetRelativeLocation(location); // カーソルの位置を設定

};


ETickBattleState ABattleMain::TickBattleState(ABattleGameMode* GameMode, float DeltaSeconds)
{
    // 戦闘開始前の先制後攻の表示イベントの実装
 


    switch(BattleMainState) {
        case EBattleMainState::BMS_UnitSelect:  //  ユニット選択
            // ユニット選択状態の処理
            if (MoveUnitSelectCursor(GameMode, DeltaSeconds) == true) {
                //  コマンド受付
                return ETickBattleState::EBS_Tick; // 実行中を返す
            }
            // ここにユニット選択のロジックを追加
            if (GameMode->BattleController->IsOkTrigger()) {
                //  決定ボタンを押した
                FMoveCursorData& cursor = (GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player1) ? Player1Cursor : Player2Cursor;


                //  ユニットデータ検索
                TObjectPtr<AUnitBattleParameter> BattleUnit = GameMode->GetUnit(cursor.X, cursor.Y);
                if (!BattleUnit)
                {
                    //  地形の表示？

                }
                else if (!BattleUnit->IsActionEnd())
                {
                    //  ユニットデータあり
                    //  ユニットデータが操作キャラか
                    bool ControlUnit = (BattleUnit->GetTeamID() == EUnitTeamID::EUTID_Team1 && GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player1) || (BattleUnit->GetTeamID() == EUnitTeamID::EUTID_Team2 && GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player2);

                    if (!ControlUnit) {
                        //  ユニットのステータス表示？
                    }
                    else {
                        //  ユニットのステータス表示
                        GameMode->SelectUnitStatus(BattleUnit);
                        //  ユニットコマンドの表示
                        BattleMainState = EBattleMainState::BMS_CommandSelect;
                        SelectUnit = BattleUnit;
                        SelectUnit->SetGameMode(GameMode);

#if 0
                        GameMode->InGameWidget->BeginBattleCommand(GameMode, SelectUnit);
#else
                        BeginBattleCommand(GameMode);
#endif
                        BattleCameraAction.Initialize(GameMode, BattleUnit->Get3DLocation(), 0.5f , 0.5f); // カメラの初期化

                        break;
                    }
                }

            }
            break;
        case EBattleMainState::BMS_CommandSelect:
            if (!BattleCameraAction.RunNormal(DeltaSeconds)) {
                return ETickBattleState::EBS_Tick; // カメラアクションが実行中の場合は実行中を返す
            }
            GameMode->InGameWidget->TickBattleCommand(DeltaSeconds);
#if 0
            if (CursorModel->IsVisible() == false)
            {
                CursorModel->SetVisibility(true);
            }
#endif
            GameMode->InGameWidget->SelectLock = false;

            if (GameMode->InGameWidget->Command != EBattleCommand::EBC_CONTINUE)
            {
                GameMode->InGameWidget->ReleaseBattleCommand(DeltaSeconds);
            }

            switch (GameMode->InGameWidget->Command)
            {
            case EBattleCommand::EBC_ATTACK:
                BattleMainState = EBattleMainState::BMS_SelectAttack;
                {
                    int X = SelectUnit->GetGameX();
                    int Y = SelectUnit->GetGameY();
                    if (BattleAttackInterface)
                    {
                        BattleAttackInterface->SetSelectPanel(X, Y, SelectUnit, GameMode, 0);
                    }
                }
                return ETickBattleState::EBS_Tick;
            case EBattleCommand::EBC_DIFFENCE:

                {
                    //  防御
                    int X = SelectUnit->GetGameX();
                    int Y = SelectUnit->GetGameY();
                    //  
                    if (BattleDiffenceInterface)
                    {
                        BattleDiffenceInterface->SetSelectPanel(X, Y, SelectUnit, GameMode, 0);
                    }
                    else
                    {
                        GameMode->BattleSelector->SetPanel(X, Y, true);
                    }
                }
#if 0
                SelectUnit->EndBattleCommand(); // ユニットのコマンドキャンセルイベントを呼び出す
#else
                EndBattleCommand(GameMode);
#endif
                BattleMainState = EBattleMainState::BMS_SelectDiffence;
                return ETickBattleState::EBS_Tick;

            case EBattleCommand::EBC_SKILL:
                {
                    int32 X = SelectUnit->GetGameX();
                    int32 Y = SelectUnit->GetGameY();
                
                    // TODO: 自陣、敵陣の選択はマスターデータ参照でSetSelectPanel()内で行う
                    if (BattleSkillInterface)
                    {
                        BattleSkillInterface->SetSelectPanel(X, Y, SelectUnit, GameMode, SkillID);
                    }
                }
#if 0
                SelectUnit->EndBattleCommand(); // ユニットのコマンドキャンセルイベントを呼び出す
#else
                EndBattleCommand(GameMode);
#endif
                BattleMainState = EBattleMainState::BMS_SelectSkill;
                return ETickBattleState::EBS_Tick;
            case EBattleCommand::EBC_MOVE:
                {
                    int X = SelectUnit->GetGameX();
                    int Y = SelectUnit->GetGameY();

                    SelectUnit->FixMove();  //  最初の値を設定しておく

                    BattleMainState = EBattleMainState::BMS_SelectMove;
                    GameMode->InGameWidget->ReleaseBattleCommand(DeltaSeconds);
                    if (BattleMoveInterface)
                    {
                        BattleMoveInterface->SetSelectPanel(X, Y, SelectUnit, GameMode, 0);
                    }
            }
                return ETickBattleState::EBS_Tick;
            case EBattleCommand::EBC_CANSEL:
                if (SelectUnit->IsMoveEnd())
                {
                    SelectUnit->SetGameX(SelectUnit->GetMoveStartX());
                    SelectUnit->SetGameY(SelectUnit->GetMoveStartY());
                    SelectUnit->ClearMoveEnd();
               

                    BattleHelper    helper;
                    MoveCanselCameraAction.Initialize(GameMode, helper.CalcPanelLocation(SelectUnit->GetGameX(), SelectUnit->GetGameY()), 0.5f, 0.5f);
                    BattleMainState = EBattleMainState::BMS_MoveCansel;
                    return ETickBattleState::EBS_Tick; //
                }
                BattleMainState = EBattleMainState::BMS_CommandCansel;

                GameMode->CanselUnitStatus(SelectUnit);
#if 0
                SelectUnit->EndBattleCommand(); // ユニットのコマンドキャンセルイベントを呼び出す
#else
                EndBattleCommand(GameMode);
#endif

                return ETickBattleState::EBS_Tick;
            default:
                break;
            }
            return ETickBattleState::EBS_Tick; //


        case EBattleMainState::BMS_MoveCansel:
            if (!MoveCanselCameraAction.RunNormal(DeltaSeconds))
            {
                return ETickBattleState::EBS_Tick; //
            }
            {
                BattleHelper    helper;
                SelectUnit->Set3DLocation(helper.CalcPanelLocation(SelectUnit->GetGameX(), SelectUnit->GetGameY()));
#if 0
                GameMode->InGameWidget->BeginBattleCommand(GameMode, SelectUnit);
#else
                BeginBattleCommand(GameMode);
#endif
                BattleMainState = EBattleMainState::BMS_CommandSelect;

                BattleCameraAction.ToEyeLocation = MoveCanselCameraAction.ToEyeLocation;
                BattleCameraAction.ToLookAtLocation = MoveCanselCameraAction.ToLookAtLocation;
                BattleCameraAction.Lerp = 1.0f;
                FMoveCursorData& cursor = (GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player1) ? Player1Cursor : Player2Cursor;
                cursor.X = cursor.BeforeX = SelectUnit->GetGameX();
                cursor.Y = cursor.BeforeY = SelectUnit->GetGameY();
                CursorModel->SetVisibility(true);
                FVector CusorLocation = GameMode->GetBattleCursorLocation(cursor.X, cursor.Y);
                CursorModel->SetRelativeLocation(CusorLocation); // カーソルの位置を更新

            }

            //  移動完了

            return ETickBattleState::EBS_Tick; //
        case EBattleMainState::BMS_SelectAttack:
            //  ユニットの選択
            if (!BattleCameraAction.RunReverse(DeltaSeconds)) {
                return ETickBattleState::EBS_Tick; // カメラアクションが実行中の場合は実行中を返す
            }

            if (MoveUnitSelectCursor(GameMode, DeltaSeconds) == true) {
                //  コマンド受付
                return ETickBattleState::EBS_Tick; // 実行中を返す
            }

            if (GameMode->BattleController->IsOkTrigger())
            {
                //  カーソル位置を取得
                FMoveCursorData& cursor = (GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player1) ? Player1Cursor : Player2Cursor;
                //  ユニット検索
                TObjectPtr<AUnitBattleParameter>    BattleParameter = GameMode->GetUnit(cursor.X, cursor.Y);
                //  パネルが選択可能か
                bool IsSelectPanelEnable = GameMode->BattleSelector->IsPanelEnable(cursor.X, cursor.Y);


                if (IsSelectPanelEnable && BattleParameter)
                {

                    if (SelectUnit != BattleParameter)
                    {
                        if (BattleParameter)
                        {
                            GameMode->SelectUnitStatus(BattleParameter);
                        }
                    }
                    //  選択可能パネルをすべて消す
                    GameMode->BattleSelector->AllOffPanel();
                    //  攻撃ユニット選択
                    //  BttleParameterに攻撃対象
                    //  SelectUnitに攻撃するユニット
                    ClearActionResult();
#if 0
                    if (BattleAttackInterface)
                    {
                        TArray<FGameLocation>    Locations;
                        FGameLocation   Location;

                        Location.X = cursor.X;
                        Location.Y = cursor.Y;
                        Locations.Add(Location);
                        //  攻撃とスキルフラグをOFF
                        SelectUnit->SetAttackEnd();
                        SelectUnit->SetSkillEnd();
                        //  攻撃計算
                        BattleAttackInterface->CalcAction(&ActionResult, Locations, SelectUnit,GameMode,0);

                        //  計算結果を反映
                        BattleAttackInterface->ReflectAction(ActionResult,GameMode);

                        //  攻撃アクションの開始
                        BattleAttackInterface->BeginAction(ActionResult, GameMode);

                        //　魔素付与
                        GameMode->MasoManager->JoinMaso(Location.X, Location.Y);

                    }
                    else
                    {
                        UE_LOG(LogTemp, Warning, TEXT("Not Found BattleAttackInterface"));
                    }
#else
                    AttackAction(GameMode, cursor.X, cursor.Y);
#endif
                    BattleMainState = EBattleMainState::BMS_AttackTick;

                    return ETickBattleState::EBS_Tick;
                }

            }


            if (GameMode->BattleController->IsCanselTrigger()) {
                //  キャンセル
                //  選択ユニット以外キャンセル扱い
                GameMode->CanselWithOutUnitStatus(SelectUnit);
                BattleMainState = EBattleMainState::BMS_CommandSelect;
                SelectUnit->SetGameMode(GameMode);
#if 0
                GameMode->InGameWidget->BeginBattleCommand(GameMode, SelectUnit);
#else
                BeginBattleCommand(GameMode);
#endif
                CursorModel->SetVisibility(false);
                ReturnSelectUnitCursorLocation(GameMode);
                //  パネルを全部消す
                GameMode->BattleSelector->AllOffPanel();

                return ETickBattleState::EBS_Tick; //
            }
            return ETickBattleState::EBS_Tick; //

            //  移動選択
        case EBattleMainState::BMS_SelectMove:
            if (!BattleCameraAction.RunReverse(DeltaSeconds)) {
                return ETickBattleState::EBS_Tick; // カメラアクションが実行中の場合は実行中を返す
            }
            if (MoveUnitSelectCursor(GameMode, DeltaSeconds) == true) {
                //  コマンド受付
                return ETickBattleState::EBS_Tick; // 実行中を返す
            }



            if (GameMode->BattleController->IsOkTrigger())
            {

                //  カーソル位置を取得
                FMoveCursorData& cursor = (GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player1) ? Player1Cursor : Player2Cursor;

                //  パネルが選択可能か
                bool IsSelectPanelEnable = GameMode->BattleSelector->IsPanelEnable(cursor.X, cursor.Y);

                if (IsSelectPanelEnable)
                {
                    //  選択可能パネルをすべて消す
                    GameMode->BattleSelector->AllOffPanel();
                    CursorModel->SetVisibility(false);
                    ClearActionResult();
                    //  攻撃ユニット選択
                    //  BttleParameterに攻撃対象
                    //  SelectUnitに攻撃するユニット
                    if (BattleMoveInterface)
                    {
                        TArray<FGameLocation>    Locations;
                        FGameLocation   Location;

                        Location.X = cursor.X;
                        Location.Y = cursor.Y;
                        Locations.Add(Location);

                        //  攻撃計算
                        BattleMoveInterface->CalcAction(&ActionResult, Locations, SelectUnit, GameMode,0);

                        //  計算結果を反映
                        BattleMoveInterface->ReflectAction(ActionResult, GameMode);

                        //  移動アクションの開始
                        BattleMoveInterface->BeginAction(ActionResult, GameMode);

                    }
                    else
                    {
                        UE_LOG(LogTemp, Warning, TEXT("Not Found BattleMoveInterface"));
                        ActionResult.ActionMoveResult.MoveLocation.X = cursor.X;
                        ActionResult.ActionMoveResult.MoveLocation.Y = cursor.Y;
                    }

                    BattleMainState = EBattleMainState::BMS_MoveTick;

                    return ETickBattleState::EBS_Tick;
                }

            }

            if (GameMode->BattleController->IsCanselTrigger()) {
                //  キャンセル
                BattleMainState = EBattleMainState::BMS_CommandSelect;
#if 0
                GameMode->InGameWidget->BeginBattleCommand(GameMode, SelectUnit);
#else
                BeginBattleCommand(GameMode);
#endif

                //  カーソルを元の位置へ
                CursorModel->SetVisibility(false);
                ReturnSelectUnitCursorLocation(GameMode);

                //  パネルを全部消す
                GameMode->BattleSelector->AllOffPanel();

                return ETickBattleState::EBS_Tick; //
            }
            return ETickBattleState::EBS_Tick; //

            //  防御選択
        case EBattleMainState::BMS_SelectDiffence:
            if (!BattleCameraAction.RunReverse(DeltaSeconds)) {
                return ETickBattleState::EBS_Tick; // カメラアクションが実行中の場合は実行中を返す
            }

            if (MoveUnitSelectCursor(GameMode, DeltaSeconds) == true) {
                //  コマンド受付
                return ETickBattleState::EBS_Tick; // 実行中を返す
            }
            if (GameMode->BattleController->IsOkTrigger())
            {
                //  カーソル位置を取得
                FMoveCursorData& cursor = (GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player1) ? Player1Cursor : Player2Cursor;

                //  パネルが選択可能か
                bool IsSelectPanelEnable = GameMode->BattleSelector->IsPanelEnable(cursor.X, cursor.Y);

                //  選択可能パネルをすべて消す
                GameMode->BattleSelector->AllOffPanel();
                ClearActionResult();
#if 0
                if (BattleDiffenceInterface) {
                    TArray<FGameLocation>    Locations;
                    FGameLocation   Location;

                    Location.X = cursor.X;
                    Location.Y = cursor.Y;
                    Locations.Add(Location);

                    //  防御計算
                    BattleDiffenceInterface->CalcAction(&ActionResult, Locations, SelectUnit, GameMode,0);

                    //  防御結果反映
                    BattleDiffenceInterface->ReflectAction(ActionResult, GameMode);

                    //  防御アクション開始
                    BattleDiffenceInterface->BeginAction(ActionResult, GameMode);

                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Not Found BattleDiffenceInterface"));
                }
#else
                DiffenceAction(GameMode, cursor.X, cursor.Y);

#endif
                BattleMainState = EBattleMainState::BMS_DiffenceTick;
                return ETickBattleState::EBS_Tick; //
            }

            if (GameMode->BattleController->IsCanselTrigger()) {
                //  キャンセル
                BattleMainState = EBattleMainState::BMS_CommandSelect;
                //  カーソルを元の位置へ
                CursorModel->SetVisibility(false);
                ReturnSelectUnitCursorLocation(GameMode);
#if 0
                GameMode->InGameWidget->BeginBattleCommand(GameMode, SelectUnit);
#else
                BeginBattleCommand(GameMode);
#endif
                //  パネルを全部消す
                GameMode->BattleSelector->AllOffPanel();

                return ETickBattleState::EBS_Tick; //
            }

            return ETickBattleState::EBS_Tick; //

            //  スキル選択
        case EBattleMainState::BMS_SelectSkill:
            if (BattleSkillInterface)
            {
                int ID = BattleSkillInterface->SelectSkillTick(SelectUnit, GameMode);
                if (ID >= 0)
                {
                    SkillID = ID;
                    int X = SelectUnit->GetGameX();
                    int Y = SelectUnit->GetGameY();
                    BattleSkillInterface->SetSelectPanel(X, Y, SelectUnit, GameMode, SkillID);
                    BattleMainState = EBattleMainState::BMS_SelectSkillPanel;
                    return ETickBattleState::EBS_Tick; //
                }
            }
            else
            {
                if (GameMode->BattleController->IsCanselTrigger()) {
                    //  キャンセル
                    BattleMainState = EBattleMainState::BMS_CommandSelect;
#if 0
                    GameMode->InGameWidget->BeginBattleCommand(GameMode, SelectUnit);
#else
                    BeginBattleCommand(GameMode);
#endif
                    //  カーソルを元の位置へ
                    CursorModel->SetVisibility(false);
                    ReturnSelectUnitCursorLocation(GameMode);


                    //  パネルを全部消す
                    GameMode->BattleSelector->AllOffPanel();
                    return ETickBattleState::EBS_Tick; //
                }


                SkillID = 0;
                int X = SelectUnit->GetGameX();
                int Y = SelectUnit->GetGameY();

                GameMode->BattleSelector->SetPanel(X + 1, Y, true);
                GameMode->BattleSelector->SetPanel(X - 1, Y, true);
                GameMode->BattleSelector->SetPanel(X, Y + 1, true);
                GameMode->BattleSelector->SetPanel(X, Y - 1, true);

                UE_LOG(LogTemp, Warning, TEXT("Not Found BattleSkillInterface"));
                BattleMainState = EBattleMainState::BMS_SelectSkillPanel;
                return ETickBattleState::EBS_Tick; //
            }
            if (GameMode->BattleController->IsCanselTrigger()) {
                //  キャンセル
                BattleMainState = EBattleMainState::BMS_CommandSelect;
#if 0
                GameMode->InGameWidget->BeginBattleCommand(GameMode, SelectUnit);
#else
                BeginBattleCommand(GameMode);
#endif

                //  カーソルを元の位置へ
                CursorModel->SetVisibility(false);
                ReturnSelectUnitCursorLocation(GameMode);


                //  パネルを全部消す
                GameMode->BattleSelector->AllOffPanel();

                return ETickBattleState::EBS_Tick; //
            }
            return ETickBattleState::EBS_Tick; //

            //  スキルを選択した後のパネル選択
        case EBattleMainState::BMS_SelectSkillPanel:
            if (!BattleCameraAction.RunReverse(DeltaSeconds)) {
                return ETickBattleState::EBS_Tick; // カメラアクションが実行中の場合は実行中を返す
            }
            if (MoveUnitSelectCursor(GameMode, DeltaSeconds) == true) {
                //  コマンド受付
                return ETickBattleState::EBS_Tick; // 実行中を返す
            }

            if (GameMode->BattleController->IsOkTrigger())
            {
                //  カーソル位置を取得
                FMoveCursorData& cursor = (GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player1) ? Player1Cursor : Player2Cursor;

                //  パネルが選択可能か
                bool IsSelectPanelEnable = GameMode->BattleSelector->IsPanelEnable(cursor.X, cursor.Y);

                if (IsSelectPanelEnable)
                {
                    //  選択可能パネルをすべて消す
                    GameMode->BattleSelector->AllOffPanel();
                    //  攻撃ユニット選択
                    //  BttleParameterに攻撃対象
                    //  SelectUnitに攻撃するユニット
                    ClearActionResult();
                    if (BattleSkillInterface)
                    {
                        TArray<FGameLocation>    Locations;
                        FGameLocation   Location;

                        Location.X = cursor.X;
                        Location.Y = cursor.Y;
                        Locations.Add(Location);

                        //  攻撃とスキルフラグをOFF
                        SelectUnit->SetAttackEnd();
                        SelectUnit->SetSkillEnd();

                        //  攻撃計算
                        BattleSkillInterface->CalcAction(&ActionResult, Locations, SelectUnit, GameMode,SkillID);

                        //  計算結果を反映
                        BattleSkillInterface->ReflectAction(ActionResult, GameMode);

                        //  攻撃アクションの開始
                        BattleSkillInterface->BeginAction(ActionResult, GameMode);



                    }
                    else
                    {
                        UE_LOG(LogTemp, Warning, TEXT("Not Found BattleSkillInterface"));
                        FActionTargetAndLocation    ActionTargetLocation;
                        ActionTargetLocation.Location.X = cursor.X;
                        ActionTargetLocation.Location.Y = cursor.Y;
                        TObjectPtr<AUnitBattleParameter>    Target = GameMode->GetUnit(cursor.X, cursor.Y);
                        ActionTargetLocation.Target = Target;

                        ActionResult.ActionSkillResult.SkillID = SkillID;

                        ActionResult.ActionSkillResult.TargetUnits.Add(ActionTargetLocation);
                    }

                    BattleMainState = EBattleMainState::BMS_SkillTick;

                    return ETickBattleState::EBS_Tick;
                }

            }


            if (GameMode->BattleController->IsCanselTrigger()) {
                //  キャンセル
                BattleMainState = EBattleMainState::BMS_SelectSkill;

                //  カーソルを元の位置へ
                CursorModel->SetVisibility(false);
                ReturnSelectUnitCursorLocation(GameMode);

                //  パネルを全部消す
                GameMode->BattleSelector->AllOffPanel();


                if (BattleSkillInterface)
                {
                    BattleSkillInterface->SelectSkillBegin(SelectUnit, GameMode);
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Not Found BattleSkillInterface"));
                }


                return ETickBattleState::EBS_Tick; //
            }
            return ETickBattleState::EBS_Tick; //
            //  攻撃アクションのTick
        case EBattleMainState::BMS_AttackTick:
            if (BattleAttackInterface) {
                if (BattleAttackInterface->TickAction(ActionResult, DeltaSeconds, GameMode))
                {
                    //  攻撃アクション終了
                    FMoveCursorData& cursor = (GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player1) ? Player1Cursor : Player2Cursor;
                    cursor.X = cursor.BeforeX = SelectUnit->GetGameX();
                    cursor.Y = cursor.BeforeY = SelectUnit->GetGameY();
                    GameMode->CanselWithOutUnitStatus(SelectUnit);

                    //  戦闘結果のチェック
                    GameMode->CheckBattleResult();

                    if (SelectUnit->IsActionEnd() || GameMode->GetBattleResult() != EBattleResult::EBR_None)
                    {
                        SelectUnit->SetActionEnd(); //(IsActionEnd()の中では、攻撃と移動が終了している場合はActionEndフラグが立たない。そのためここでアクションエンドフラグをたてる
                        BattleMainState = EBattleMainState::MBS_EndAction;
                    }
                    else
                    {
                        BattleMainState = EBattleMainState::BMS_CommandSelect;
#if 0
                        GameMode->InGameWidget->BeginBattleCommand(GameMode, SelectUnit);
#else
                        BeginBattleCommand(GameMode);
#endif
                        CursorModel->SetVisibility(true);
                        FVector CusorLocation = GameMode->GetBattleCursorLocation(SelectUnit->GetGameX(), SelectUnit->GetGameY());
                        CursorModel->SetRelativeLocation(CusorLocation); // カーソルの位置を更新

                        //  カーソル位置を取得
//                        FMoveCursorData& cursor = (GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player1) ? Player1Cursor : Player2Cursor;
                        cursor.X = cursor.BeforeX = SelectUnit->GetGameX();
                        cursor.Y = cursor.BeforeY = SelectUnit->GetGameY();

                    }
                    GameMode->ReflectionStatus();
                }
            }
            else {
                UE_LOG(LogTemp, Warning, TEXT("Not Found BattleAttackInterface"));
                BattleMainState = EBattleMainState::MBS_EndAction;
            }
            return ETickBattleState::EBS_Tick; //

            //  防御のTick
        case EBattleMainState::BMS_DiffenceTick:
            if (BattleDiffenceInterface)
            {
                //  防御アクション
                if (BattleDiffenceInterface->TickAction(ActionResult, DeltaSeconds, GameMode))
                {
                    //  防御アクション終了
                    BattleMainState = EBattleMainState::MBS_EndAction;
                }
                else
                {
                    return ETickBattleState::EBS_Tick; //
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Not Found BattleDiffenceInterface"));
                BattleMainState = EBattleMainState::MBS_EndAction;
            }
            GameMode->CanselWithOutUnitStatus(SelectUnit);

            return ETickBattleState::EBS_Tick; //

        case EBattleMainState::BMS_MoveTick:
            if (BattleMoveInterface)
            {
                //  移動アクション
                if (BattleMoveInterface->TickAction(ActionResult, DeltaSeconds, GameMode))
                {
                    //  移動アクション終了
                    SelectUnit->SetMoveEnd();
                    SelectUnit->PlayAnimationWait();

                    if (SelectUnit->IsActionEnd())
                    {
                        SelectUnit->SetActionEnd();
                        BattleMainState = EBattleMainState::BMS_MoveOkOrCansel;
                    }
                    else
                    {
                        BattleMainState = EBattleMainState::BMS_CommandSelect;
#if 0
                        GameMode->InGameWidget->BeginBattleCommand(GameMode, SelectUnit);
#else
                        BeginBattleCommand(GameMode);
#endif


                        BattleCameraAction.Initialize(GameMode, SelectUnit->Get3DLocation(), 0.5f, 0.5f); // カメラの初期化
                    }
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Not Found BattleMoveInterface"));

                SelectUnit->SetGameX(ActionResult.ActionMoveResult.MoveLocation.X);
                SelectUnit->SetGameY(ActionResult.ActionMoveResult.MoveLocation.Y);

                BattleHelper    helper;

                SelectUnit->Set3DLocation(helper.CalcPanelLocation(SelectUnit->GetGameX(), SelectUnit->GetGameY()));
                //  移動終了フラグをクリア
                SelectUnit->ClearMoveEnd();
                BattleMainState = EBattleMainState::MBS_EndAction;
            }
            return ETickBattleState::EBS_Tick; //

        case EBattleMainState::BMS_MoveOkOrCansel:
            //  移動後、決定か
            if (GameMode->BattleController->IsOkTrigger())
            {
                //  移動値を固定
                SelectUnit->FixMove();
                SelectUnit->SetActionEnd();
                BattleMainState = EBattleMainState::MBS_EndAction;
                return ETickBattleState::EBS_Tick; //
            }
            if (GameMode->BattleController->IsCanselTrigger())
            {
                SelectUnit->SetGameX(SelectUnit->GetMoveStartX());
                SelectUnit->SetGameY(SelectUnit->GetMoveStartY());
                SelectUnit->ClearMoveEnd();


                BattleHelper    helper;
                MoveCanselCameraAction.Initialize(GameMode, helper.CalcPanelLocation(SelectUnit->GetGameX(), SelectUnit->GetGameY()), 0.5f, 0.5f);
                BattleMainState = EBattleMainState::BMS_MoveCansel;
                return ETickBattleState::EBS_Tick; //
            }
            return ETickBattleState::EBS_Tick; //
            //  スキルのTick
        case EBattleMainState::BMS_SkillTick:
            if (BattleSkillInterface)
            {
                //  特技アクション
                //  特技アクション
                if (BattleSkillInterface->TickAction(ActionResult, DeltaSeconds, GameMode))
                {

                    GameMode->CanselWithOutUnitStatus(SelectUnit);
                    SelectUnit->SetSkillEnd();

                    GameMode->CheckBattleResult();

                    if (SelectUnit->IsActionEnd() || GameMode->GetBattleResult() != EBattleResult::EBR_None)
                    {
                        //  アクション終了
                        SelectUnit->SetActionEnd();
                        BattleMainState = EBattleMainState::MBS_EndAction;
                    }
                    else
                    {
                        //  コマンド選択
                        BattleMainState = EBattleMainState::BMS_CommandSelect;
#if 0
                        GameMode->InGameWidget->BeginBattleCommand(GameMode, SelectUnit);
#else
                        BeginBattleCommand(GameMode);
#endif
                        CursorModel->SetVisibility(true);
                        FVector CusorLocation = GameMode->GetBattleCursorLocation(SelectUnit->GetGameX(), SelectUnit->GetGameY());
                        CursorModel->SetRelativeLocation(CusorLocation); // カーソルの位置を更新

                        //  カーソル位置を取得
                        FMoveCursorData& cursor = (GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player1) ? Player1Cursor : Player2Cursor;
                        cursor.X = cursor.BeforeX = SelectUnit->GetGameX();
                        cursor.Y = cursor.BeforeY = SelectUnit->GetGameY();

                    }
                    GameMode->ReflectionStatus();
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Not Found BattleSkillInterface"));
                BattleMainState = EBattleMainState::MBS_EndAction;
            }
            return ETickBattleState::EBS_Tick; //


            //  アクションが終了したときにターンが終了したか調べる
        case EBattleMainState::MBS_EndAction:
            BattleMainState = EBattleMainState::BMS_UnitSelect;
            //  ユニットアクション終了
            GameMode->BattleSelector->AllOffPanel();
            SelectUnit->SetActionEnd();
            SelectUnit->GetBattleCharaStatusWidget()->ChangeEndAction();
            SelectUnit = nullptr;

            //  結果判定処理
            GameMode->CheckBattleResult();
            if (GameMode->GetBattleResult() != EBattleResult::EBR_None)
            {   //  戦闘終了
                CursorModel->SetVisibility(false);
                return ETickBattleState::EBS_End;
            }

            if (GameMode->IsNowTurnEnd())
            {
                //  カーソルOFF
                CursorModel->SetVisibility(false);
                GameMode->ClearActionEndFlag();
                // どちらのチームのターンが終わったか
                if (GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player1)
                {
                    GameMode->MasoManager->UpdatePlayer1Maso();
                    UE_LOG(LogTemp, Warning, TEXT("Player1のターン終了"));
                }
                else 
                {
                    GameMode->MasoManager->UpdatePlayer2Maso();
                    UE_LOG(LogTemp, Warning, TEXT("Player2のターン終了"));
                }
                return ETickBattleState::EBS_TurnEnd;
            }
            return ETickBattleState::EBS_Tick; // 実行中を返す
        case EBattleMainState::BMS_CommandCansel:
            if (!BattleCameraAction.RunReverse(DeltaSeconds)) {
                return ETickBattleState::EBS_Tick; // カメラアクションが実行中の場合は実行中を返す
            }
            BattleMainState = EBattleMainState::BMS_UnitSelect;
            return ETickBattleState::EBS_Tick; //
        default:
            UE_LOG(LogTemp, Warning, TEXT("Unknown BattleMainState"));
            break;
    }
    if (GameMode->BattleController->IsCanselTrigger()) {
        //  ターンの終了を選択
        SelectUnit = nullptr;
        CursorModel->SetVisibility(false); // カーソルを非表示にする
        GameMode->ClearActionEndFlag();
        return ETickBattleState::EBS_TurnEnd; // 実行中を返す
    }
    return ETickBattleState::EBS_Tick; // 実行中を返す

}

bool ABattleMain::MoveCursor(ABattleGameMode* GameMode, ABattleMain::FMoveCursorData& cursor, const FVector2D& Direction,float DeltaSeconds)
{
    if (cursor.X != cursor.BeforeX || cursor.Y != cursor.BeforeY) {
        // カーソルの位置が変更された場合
        FVector NewCursorPositin = GameMode->GetBattleCursorLocation(cursor.X, cursor.Y); // カーソルの新しい位置を取得
        FVector OldCursorPositin = GameMode->GetBattleCursorLocation(cursor.BeforeX, cursor.BeforeY); // カーソルの新しい位置を取得

        cursor.MoveLerp = FMath::Min(1.0f,cursor.MoveLerp + DeltaSeconds / cursor.MoveTime); // カーソルの移動補間値を更新

        float sinlerp = FMath::Sin(FMath::DegreesToRadians(90.0f) * cursor.MoveLerp);
        FVector CurrentPosition = FMath::Lerp(OldCursorPositin , NewCursorPositin, sinlerp); // カーソルの現在位置を補間
        CursorModel->SetRelativeLocation(CurrentPosition); // カーソルの位置を更新
        if (cursor.MoveLerp < 1.0f)
        {
            return false; // カーソルの移動が完了していない
        }
        cursor.MoveLerp = 0.0f;
        cursor.BeforeX = cursor.X; // 前回のカーソル位置を更新
        cursor.BeforeY = cursor.Y; // 前回のカーソル位置を更新


        TObjectPtr<AUnitBattleParameter> NextUnit = GameMode->GetUnit(cursor.X, cursor.Y);
        if (NextUnit == BeforeUnit || (NextUnit && NextUnit == SelectUnit))
        {
            //  同じユニット
            GameMode->SelectUnitStatus(NextUnit);
            BeforeUnit = NextUnit;
        }
        else
        {
            GameMode->CanselWithOutUnitStatus(SelectUnit);
            //  選択ユニットが変わった
            BeforeUnit = NextUnit;
            if (NextUnit)
            {
                GameMode->SelectUnitStatus(NextUnit);
            }
        }
        return true;
    }
    
    if ((FMath::Abs(Direction.X) + FMath::Abs(Direction.Y)) > FLT_EPSILON)
    {
        if (GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player1)
        {
            if ((FMath::Abs(Direction.X) > FMath::Abs(Direction.Y)))
            {
                // X方向の移動
                if (Direction.X < 0.0f) {
                    if (cursor.X < (GAME_LOCATION_WIDTH - 1)) {
                        ++cursor.X; // X座標を右に移動
                    }
                }
                else if (Direction.X > 0.0f) {
                    if (cursor.X > 0) {
                        --cursor.X; // X座標を左に移動
                    }
                }
            }
            else
            {
                // Y方向の移動
                if (Direction.Y > 0.0f) {
                    if (cursor.Y < (GAME_LOCATION_DEPTH - 1)) {
                        ++cursor.Y; // Y座標を上に移動
                    }
                }
                else if (Direction.Y < 0.0f) {
                    if (cursor.Y > 0) {
                        if (cursor.Y > 0) {
                            --cursor.Y; // Y座標を下に移動
                        }
                    }
                }
            }
        }
        else {
            if ((FMath::Abs(Direction.X) > FMath::Abs(Direction.Y)))
            {
                // X方向の移動
                if (Direction.X > 0.0f) {
                    if (cursor.X < (GAME_LOCATION_WIDTH - 1)) {
                        ++cursor.X; // X座標を右に移動
                    }
                }
                else if (Direction.X < 0.0f) {
                    if (cursor.X > 0) {
                        --cursor.X; // X座標を左に移動
                    }
                }
            }
            else
            {
                // Y方向の移動
                if (Direction.Y < 0.0f) {
                    if (cursor.Y < (GAME_LOCATION_DEPTH - 1)) {
                        ++cursor.Y; // Y座標を上に移動
                    }
                }
                else if (Direction.Y > 0.0f) {
                    if (cursor.Y > 0) {
                        if (cursor.Y > 0) {
                            --cursor.Y; // Y座標を下に移動
                        }
                    }
                }
            }
        }
        bool MovePlay = (cursor.X != cursor.BeforeX || cursor.Y != cursor.BeforeY);
        return MovePlay; // カーソルの位置が変更されたかどうかを返す
    }


    FVector CusorLocation = GameMode->GetBattleCursorLocation(cursor.X, cursor.Y);
    CursorModel->SetRelativeLocation(CusorLocation); // カーソルの位置を更新

    TObjectPtr<AUnitBattleParameter> NextUnit = GameMode->GetUnit(cursor.X, cursor.Y);
    if (NextUnit == nullptr)
    {
        GameMode->CanselWithOutUnitStatus(SelectUnit);
        BeforeUnit = NextUnit;
    }
    else if (NextUnit == BeforeUnit)
    {
        //  同じユニット
        GameMode->SelectUnitStatus(NextUnit);
        BeforeUnit = NextUnit;
    }
    else if (NextUnit == SelectUnit)
    {
        if (BeforeUnit != NextUnit)
        {
        }
        BeforeUnit = NextUnit;
    }
    else
    {
        GameMode->CanselWithOutUnitStatus(SelectUnit);
        //  選択ユニットが変わった
        BeforeUnit = NextUnit;
        if (NextUnit)
        {
            GameMode->SelectUnitStatus(NextUnit);
        }
    }


    return false;


}
bool ABattleMain::MoveCursor(ABattleGameMode* GameMode, const FVector2D& Direction, float DeltaSeconds)
{
    bool MoveFlag = false;
    if (GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player1)
    {
        MoveFlag = MoveCursor(GameMode,Player1Cursor,Direction, DeltaSeconds); // プレイヤー1のカーソル位置を取得
    }
    else
    {
        MoveFlag = MoveCursor(GameMode, Player2Cursor, Direction, DeltaSeconds); // プレイヤー1のカーソル位置を取得
    }
    return MoveFlag; // カーソルの移動が完了したかどうかを返す
}

bool ABattleMain::MoveUnitSelectCursor(ABattleGameMode* GameMode , float DeltaSeconds)
{
    if (CursorModel->IsVisible() == false)
    {
        CursorModel->SetVisibility(true);
    }
    return MoveCursor(GameMode, GameMode->BattleController->GetLeftAxis(), DeltaSeconds); // プレイヤーのカーソル位置を取得
}

//  アクションリザルトの初期化
void ABattleMain::ClearActionResult()
{
    ActionResult.ActionUnit = nullptr;
    ActionResult.ActionAttackResult.AttackTargets.Empty();
    ActionResult.ActionMoveResult.RouteLocation.Empty();
    ActionResult.ActionSkillResult.TargetUnits.Empty();
}



// 攻撃
void ABattleMain::AttackAction(ABattleGameMode* GameMode , int X , int Y)
{
    if (BattleAttackInterface)
    {
        ClearActionResult();
        TArray<FGameLocation>    Locations;
        FGameLocation   Location;

        Location.X = X;
        Location.Y = Y;
        Locations.Add(Location);
        //  攻撃とスキルフラグをOFF
        SelectUnit->SetAttackEnd();
        SelectUnit->SetSkillEnd();
        //  攻撃計算
        BattleAttackInterface->CalcAction(&ActionResult, Locations, SelectUnit, GameMode, 0);

        //  計算結果を反映
        BattleAttackInterface->ReflectAction(ActionResult, GameMode);

        //  攻撃アクションの開始
        BattleAttackInterface->BeginAction(ActionResult, GameMode);

        //　魔素付与
        GameMode->MasoManager->JoinMaso(Location.X, Location.Y);

    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Not Found BattleAttackInterface"));
    }
}

//  防御
void ABattleMain::DiffenceAction(ABattleGameMode* GameMode, int X, int Y)
{
    if (BattleDiffenceInterface) {
        TArray<FGameLocation>    Locations;
        FGameLocation   Location;

        Location.X = X;
        Location.Y = Y;
        Locations.Add(Location);

        //  防御計算
        BattleDiffenceInterface->CalcAction(&ActionResult, Locations, SelectUnit, GameMode, 0);

        //  防御結果反映
        BattleDiffenceInterface->ReflectAction(ActionResult, GameMode);

        //  防御アクション開始
        BattleDiffenceInterface->BeginAction(ActionResult, GameMode);

    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Not Found BattleDiffenceInterface"));
    }
}


void ABattleMain::BeginBattleCommand(ABattleGameMode* GameMode)
{
    GameMode->InGameWidget->BeginBattleCommand(GameMode, SelectUnit);
}

void ABattleMain::EndBattleCommand(ABattleGameMode* GameMode)
{
    SelectUnit->EndBattleCommand(); // ユニットのコマンドキャンセルイベントを呼び出す
}




//  カーソル位置を選択ユニットに戻す
void ABattleMain::ReturnSelectUnitCursorLocation(ABattleGameMode* GameMode)
{
    if (SelectUnit)
    {
        int X = SelectUnit->GetGameX();
        int Y = SelectUnit->GetGameY();
        BattleHelper    helper;
        CursorModel->SetRelativeLocation(helper.CalcPanelLocation(X, Y));

        FMoveCursorData& cursor = (GameMode->GetCurrentBattleTurn() == EBattleTurn::EBT_Player1) ? Player1Cursor : Player2Cursor;

        cursor.BeforeX = cursor.X = X;
        cursor.BeforeY = cursor.Y = Y;
    }
}

// Niagaraでカーソルモデルを作成
void ABattleMain::CreateCursorModel()
{
    // NiagaraSystemを取得
    CursorNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/FixEffect/Cursoul/Ef_Cursoul.Ef_Cursoul"));

    if (CursorNiagaraSystem)
    {
        // NiagaraComponentを取得
        CursorEffectComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
            CursorNiagaraSystem,
            RootComponent,
            NAME_None,
            FVector::ZeroVector,
            FRotator::ZeroRotator,
            FVector::OneVector,
            EAttachLocation::KeepRelativeOffset,
            true,
            ENCPoolMethod::None,
            true,
            true
        );
    }else{
        UE_LOG(LogTemp, Warning, TEXT("Failed to load NiagaraSystem"));
    }
}
