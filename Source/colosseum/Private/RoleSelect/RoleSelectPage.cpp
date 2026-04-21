// Fill out your copyright notice in the Description page of Project Settings.

#include "RoleSelect/RoleSelectPage.h"
#include "Common/CharaFace.h"
#include "RoleSelect/RoleSelecter.h"
#include "RoleSelect/RoleArrangementUnitStage.h"
#include "EngineUtils.h"
#include "Camera/CameraComponent.h"
#include "RoleSelect/RoleSelectPlayerState.h"
#include "RoleSelect/RoleSelectScreen.h"
#include "RoleSelect/RoleSelectGameState.h"

#define ROLE_UNIT_ARRANGMENT_P1 TEXT("")
#define ROLE_SELECT_TIME    0.5f

#define ROLE_SELECT_MOVE_PARAMETER  90.0f
/**
 * ロールセレクトページ
 */

#define ROLESLOT_NUM 3

#define TEAM1_BP_ROLESELECT_NAME   TEXT("BP_RoleSelectScreen_P1")
#define TEAM2_BP_ROLESELECT_NAME   TEXT("BP_RoleSelectScreen_P2")
#define ROLESELECT_CAMERA_ACTOR_NAME    TEXT("Camera")



void URoleSelectPage::SetupTeam_Implementation(EUnitTeamID Team_id)
{
    ;
}

void URoleSelectPage::FaceSetup_Implementation()
{
    ;
}

void URoleSelectPage::PageSetup_Implementation()
{
    ;
}

void URoleSelectPage::ArrangementSetup_Implementation()
{
    ;
}

void URoleSelectPage::ArrangementClose_Implementation()
{
    ;
}

void URoleSelectPage::RoleSelecterOpen_Implementation()
{
    ;
}

void URoleSelectPage::RoleSelecterDark_Implementation()
{
    ;
}

void URoleSelectPage::RoleSelecterNormal_Implementation()
{
    ;
}

void URoleSelectPage::RoleSelecterClose_Implementation()
{
    ;
}


void URoleSelectPage::NextSlot_Implementation()
{
    ;
}

void URoleSelectPage::SetSlotIndex_Implementation(int SlotIndex)
{
    ;
}


void URoleSelectPage::PrevSlot_Implementation()
{
    ;
}

void URoleSelectPage::SetPlayerTeamName_Implementation(const FString& TeamName)
{
    ;
}


void URoleSelectPage::ActiveSlot_Implementation()
{
    ;
}

void URoleSelectPage::GetReady_Implementation()
{
    ;
}

void URoleSelectPage::SetRoleNameInfoFromJobID_Implementation(EUnitJob jobID)
{
}


void URoleSelectPage::SetTeamID(EUnitTeamID Team_ID)
{
    TeamID = Team_ID;
}


void URoleSelectPage::SetupRoleUnitSlotsAdd(UCharaFace* CharaFace)
{
    TObjectPtr<ARoleUnitSlot> RoleUnitSlot = NewObject<ARoleUnitSlot>();
    RoleUnitSlot->CharaFace = CharaFace;
    RoleUnitSlot->SetTeamID(TeamID);
    RoleUnitSlots.Add(RoleUnitSlot);

}

void URoleSelectPage::Startup(int SlotNo)
{
    ClearSelectCursor();
    SetSlotCursor(SlotNo);
}

void URoleSelectPage::ClearSelectCursor()
{
    for (TArray<TObjectPtr<ARoleUnitSlot>>::TIterator Ite = RoleUnitSlots; Ite; ++Ite)
    {
        (*Ite)->SetSelected(false);
    }
}

void URoleSelectPage::SetSlotCursor(int SlotNo)
{
    RoleUnitSlots[SlotNo]->SetSelected(true);
}



FQuat URoleSelectPage::GetRolequat(EUnitJob job) const
{
    switch (job)
    {
    case EUnitJob::EUJ_Tank:
        return FQuat(FRotator(0.0f, 0.0f, 0.0f));
    case EUnitJob::EUJ_Rounder:
        return FQuat(FRotator(0.0f, 90.0f, 0.0f));
    case EUnitJob::EUJ_Magician:
        return FQuat(FRotator(0.0f, 180.0f, 0.0f));
    case EUnitJob::EUJ_Healer:
        return FQuat(FRotator(0.0f, 270.0f, 0.0f));
    default:
        break;
    }
    return FQuat(FRotator(0.0f, 0.0f, 0.0f));
}



void URoleSelectPage::CalcRoleLoop()
{
    FQuat BeforeQuat = GetRolequat(SelecteBeforedJob);
    FQuat NextQuat = GetRolequat(SelectedJob);
    float lerp = FMath::Sin(FMath::DegreesToRadians(ROLE_SELECT_MOVE_PARAMETER) * RoleSelecter->CalcLerp());
    FQuat Result = FQuat::Slerp(BeforeQuat, NextQuat,lerp );
    RoleSelectScreen->RoleSelectCamera->SetRelativeRotation(Result);
}




void URoleSelectPage::ChangeState_Selecting(ARoleSelectPlayerState* PlayerState,bool NotSendCommand)
{
    PageSetup();
    CreateRoleSelecter();
    SetRoleSelectArrow();
    RoleSelecterNormal();

    RoleSelecter->Startup();
    RoleSelecter->SetMaxTime(ROLE_SELECT_TIME);
    RoleSelecter->NowTime = RoleSelecter->MaxTime;

    SelectedJob = GetRoleSelectFromCursorIndex();

    SetRoleNameInfoFromJobID(SelectedJob);
    ClearRoleSelectArrow();
    SetRoleSelectArrow();
    CalcRoleLoop();

    if (NotSendCommand == false)
    {   //  ロール選択時間の同期

        PlayerState->SetReplicated_RoleSelectJobBefore(SelecteBeforedJob);
        PlayerState->SetReplicated_RoleSelectJob(SelectedJob);
        PlayerState->SetReplicated_RoleSelectIndex(RoleSelectIndex);

        PlayerState->SetReplicated_RoleSelectTime(RoleSelecter->NowTime);
        PlayerState->SetReplicated_RoleSelectTimeMax(RoleSelecter->MaxTime);

        PlayerState->SetReplicated_SlotState(ERpoleSelectSlotState::ERSSS_SelectingAnim);
    }
    SlotState = ERpoleSelectSlotState::ERSSS_SelectingAnim;
}


void URoleSelectPage::ChangeState_SelectingNext(ARoleSelectPlayerState* PlayerState, bool NotSendCommand)
{
    ChangeState_Selecting(PlayerState, NotSendCommand);

    SelectedJob = GetRoleSelectFromCursorIndex();
    RoleSelecter->Startup();
    SetRoleNameInfoFromJobID(GetRoleSelectFromCursorIndex());
    ClearRoleSelectArrow();
    SetRoleSelectArrow();

    SetRoleNameInfoFromJobID(SelectedJob);
    SetRoleSelectArrow();
    CalcRoleLoop();

    if (NotSendCommand == false)
    {
        PlayerState->SetReplicated_RoleSelectJobBefore(SelecteBeforedJob);
        PlayerState->SetReplicated_RoleSelectJob(SelectedJob);
        PlayerState->SetReplicated_RoleSelectIndex(RoleSelectIndex);
        PlayerState->SetReplicated_RoleSelectTime(RoleSelecter->NowTime);
        PlayerState->SetReplicated_RoleSelectTimeMax(RoleSelecter->MaxTime);

        PlayerState->SetReplicated_SlotState(ERpoleSelectSlotState::ERSSS_SelectingAnim);
    }
    SlotState = ERpoleSelectSlotState::ERSSS_SelectingAnim;
}






bool URoleSelectPage::ChangeState_BeforeSlot(ARoleSelectPlayerState* PlayerState, bool NotSendCommand)
{
    //  キャンセルトリガ入力
    //  前のスロットへ
    int BackupSlotNo = 0;
    int NextSlotNo = 0;
    if (RoleArrangementUnitStage)
    {
        BackupSlotNo = RoleArrangementUnitStage->SlotNo;
    }
    PrevSlot();
    if (RoleArrangementUnitStage)
    {
        NextSlotNo = RoleArrangementUnitStage->SlotNo;
    }

    if (BackupSlotNo != NextSlotNo)
    {
        //  ロール選択へ
        EUnitJob    jobid = RoleArrangementUnitStage->GetLastArrangementUnitJob();

        SetRoleNameInfoFromJobID(jobid);
        SelectedJob = jobid;
        SelecteBeforedJob = jobid;

        PageSetup();
        RoleSelecter->SetMaxTime(ROLE_SELECT_TIME);
        RoleSelecter->NowTime = RoleSelecter->MaxTime;
        ArrangementSetup();

        if (NotSendCommand == false)
        {
            PlayerState->SetReplicated_RoleSelectTime(RoleSelecter->NowTime);
            PlayerState->SetReplicated_RoleSelectTimeMax(RoleSelecter->MaxTime);
            PlayerState->SetReplicated_ArrangementUnitState(EAUState::EAUState_Begin);
        }
        

        RoleArrangementUnitStage->StartPositionState = EAUState::EAUState_Begin;
        SlotState = ERpoleSelectSlotState::ERSSS_Arrangement;
    }
    return BackupSlotNo != NextSlotNo;
}

void URoleSelectPage::ChangeState_RoleSelectingToNone(ARoleSelectPlayerState* PlayerState, bool NotSendCommand)
{
    RoleSelecterClose();
    RoleSelecterDark();
    ClearRoleSelectArrow();
    //PrevSlot();
    ActiveSlot();
    RoleSelecter->NowTime = RoleSelecter->MaxTime;
    if (NotSendCommand == false)
    {
        PlayerState->SetReplicated_RoleSelectTime(RoleSelecter->MaxTime);
        PlayerState->SetReplicated_SlotState(ERpoleSelectSlotState::ERSSS_None);
    }
    SlotState = ERpoleSelectSlotState::ERSSS_None;
}


void URoleSelectPage::ChangeState_ToArrangement(ARoleSelectPlayerState* PlayerState, bool NotSendCommand)
{
    if (NotSendCommand == false)
    {
        PlayerState->SetReplicated_ArrangementUnitState(EAUState::EAUState_Begin);
    }
    SlotState = ERpoleSelectSlotState::ERSSS_Arrangement;
    ArrangementSetup();
    RoleArrangementUnitStage->JobID = SelectedJob;
    RoleArrangementUnitStage->StartPositionState = EAUState::EAUState_Begin;
    RoleArrangementUnitStage->BeginArrangementUnitStage();
}


void URoleSelectPage::ChangeState_PositionSet(ARoleSelectPlayerState* PlayerState, bool NotSendCommand)
{
    //  選択したユニットデータを取得

    //  一気に一番下の階層に戻る

    if (RoleArrangementUnitStage && RoleArrangementUnitStage->SelectUnit)
    {
        FUnitData   UnitData;
        UnitData = RoleArrangementUnitStage->SelectUnit->GetUnitData();
        RoleArrangementUnitStage->ResultUnitDatas.Add(UnitData);
    }

    //  一つ上を閉じる
    ArrangementClose();
    //  二つ上を閉じる
    //RoleSelecterClose();
    RoleSelecterDark();
    ClearRoleSelectArrow();
    //  次のスロットへ
    NextSlot();


    //  配置処理は待機へ
    if (NotSendCommand == false)
    {
//        RoleArrangementUnitStage->StartPositionState = EAUState::EAUState_None;
        PlayerState->SetReplicated_ArrangementUnitState(RoleArrangementUnitStage->StartPositionState);
        PlayerState->SetReplicated_SlotState(ERpoleSelectSlotState::ERSSS_None);
    }
    SlotState = ERpoleSelectSlotState::ERSSS_None;
}


void URoleSelectPage::ChangeState_ReadyWait(ARoleSelectPlayerState* PlayerState, bool NotSendCommand)
{
    if (NotSendCommand == false)
    {
        PlayerState->SetReplicated_ArrangementUnitState(RoleArrangementUnitStage->StartPositionState);
    }


    if (RoleArrangementUnitStage && RoleArrangementUnitStage->SelectUnit)
    {
        FUnitData   UnitData;
        UnitData = RoleArrangementUnitStage->SelectUnit->GetUnitData();
        RoleArrangementUnitStage->ResultUnitDatas.Add(UnitData);
    }


    //  一つ上を閉じる
    ArrangementClose();
    RoleSelecterClose();
    ClearRoleSelectArrow();
    //  ロール確定判定へ
    NextSlot();
    if (NotSendCommand == false)
    {
        PlayerState->SetReplicated_SlotState(ERpoleSelectSlotState::ERRSS_CheckReady);
    }
    SlotState = ERpoleSelectSlotState::ERRSS_CheckReady;
}

void URoleSelectPage::ChangeState_SelectPositionCansel(ARoleSelectPlayerState* PlayerState, bool NotSendCommand)
{
    //  配置をキュンセルしロール画面へ戻る
    ArrangementClose();

    RoleSelecterOpen();
    RoleSelecterNormal();

    //  処理待機
    RoleArrangementUnitStage->StartPositionState = EAUState::EAUState_None;
    RoleSelecter->SetMaxTime(ROLE_SELECT_TIME);
    RoleSelecter->NowTime = RoleSelecter->MaxTime;


    if (RoleArrangementUnitStage->SelectUnit)
    {
        RoleArrangementUnitStage->SelectUnit->SetVisible(false);
    }

    SetRoleSelectCursorPosition(SelectedJob, (NotSendCommand == false) ? PlayerState:nullptr);

    if (NotSendCommand == false)
    {
        PlayerState->SetReplicated_SlotState(ERpoleSelectSlotState::ERSSS_Selecting);
//        PlayerState->SetReplicated_ArrangementUnitState(EAUState::EAUState_Begin);
    }
    SlotState = ERpoleSelectSlotState::ERSSS_Selecting;

}
#if 0
void URoleSelectPage::ChangeState_ArrangementCansel(ARoleSelectPlayerState* PlayerState, bool NotSendCommand)
{
    if (RoleArrangementUnitStage->StartPositionState == EAUState::EAUState_SelectPositionCansel)
    {
        RoleArrangementUnitStage->StartPositionState = EAUState::EAUState_None;
//        PlayerState->SlotState = ERpoleSelectSlotState::ERSSS_Selecting;
        RoleSelecter->NowTime = RoleSelecter->MaxTime;
        SelectedJob = RoleArrangementUnitStage->JobID;
        SelecteBeforedJob = SelectedJob;
        RoleSelectIndex = GetRoleSelectCursorIndex(SelectedJob);

        if (RoleArrangementUnitStage->SelectUnit)
        {
            RoleArrangementUnitStage->SelectUnit->SetVisible(false);
            RoleArrangementUnitStage->SelectUnit = nullptr;
        }
        if (NotSendCommand == false)
        {
            PlayerState->SetReplicated_RoleSelectIndex(RoleSelectIndex);
            PlayerState->SetReplicated_RoleSelectJob(SelectedJob);
            PlayerState->SetReplicated_RoleSelectJobBefore(SelecteBeforedJob);
            PlayerState->SetReplicated_RoleSelectTime(RoleSelecter->NowTime);
            PlayerState->SetReplicated_RoleSelectTimeMax(RoleSelecter->MaxTime);
            PlayerState->SetReplicated_SlotState(ERpoleSelectSlotState::ERSSS_SelectingNext);
        }
        else
        {
            SlotState = ERpoleSelectSlotState::ERSSS_SelectingNext;
        }
    }
}
#endif


void URoleSelectPage::ChangeState_ReadyCansel(ARoleSelectPlayerState* PlayerState,bool NotSendCommand)
{
    RoleArrangementUnitStage->StartPositionState = EAUState::EAUState_Begin;
    EUnitJob jobid = RoleArrangementUnitStage->JobID;
    SetRoleNameInfoFromJobID(jobid);
    PageSetup();
    RoleSelecter->SetMaxTime(ROLE_SELECT_TIME);
    RoleSelecter->NowTime = RoleSelecter->MaxTime;
    ArrangementSetup();

    RoleArrangementUnitStage->SelectUnit = RoleArrangementUnitStage->GetSelectUnit(SelectedJob);


    PrevSlot();
    if (NotSendCommand == false)
    {
//        PlayerState->SetReplicated_SlotState(ERpoleSelectSlotState::ERSSS_Arrangement);
        PlayerState->SetReplicated_ArrangementUnitState(EAUState::EAUState_Begin);
    }

    SlotState = ERpoleSelectSlotState::ERSSS_Arrangement;
    RoleArrangementUnitStage->StartPositionState = EAUState::EAUState_Begin;
}



void URoleSelectPage::TickSlotProc(ARoleSelectPlayerState* PlayerState,ABattleController* BC, float DT)
{
    if (!PlayerState || !RoleSelectScreen)
    {
        return;
    }


    ABattleController* BattleController = BC;



    UWorld* World = GetWorld();

    TObjectPtr<ARoleSelectGameState> GameState = Cast<ARoleSelectGameState>(World->GetGameState());
    EBattleGameMode GameMode = GameState->GameMode;

    switch (GameMode)
    {
    case EBattleGameMode::EBGM_Player_VS_NPC:
        //  プレイヤーVS NPC
        if (BattleController == nullptr)
        {
            //  COM戦
            return;
        }
        break;
    case EBattleGameMode::EBGM_Player_VS_Player:
        //  プレイヤーVS プレイヤー
        if (!BattleController)
        {
            return;
        }
        break;
    case EBattleGameMode::EBGM_Player_VS_NET:
        if (World->GetGameState()->HasAuthority() == false)
        {
//            UE_LOG(LogTemp, Warning, TEXT("URoleSelectPage::TickSlotProc Client"));
        }
        else
        {
//            UE_LOG(LogTemp, Warning, TEXT("URoleSelectPage::TickSlotProc Server"));
        }

        if (!BattleController)
        {
            return;
        }
        break;
    default:
        return;
    }


    switch (SlotState)
    {
    case ERpoleSelectSlotState::ERSSS_None:
        {
            if (BattleController->IsOkTrigger())
            {
                //  ロール選択へ
                PlayerState->SetReplicated_CallID(ERoleSelectCallID::ERSCID_ChangeState_Selecting);
                ChangeState_Selecting(PlayerState);
                break;

            }
            if (BattleController->IsCanselTrigger())
            {
                PlayerState->SetReplicated_CallID(ERoleSelectCallID::ERSCID_ChangeState_BeforeSlot);
                ChangeState_BeforeSlot(PlayerState);
                break;
            }
        }
        break;
    case ERpoleSelectSlotState::ERSSS_SlotCansel:
        
        break;
    case ERpoleSelectSlotState::ERSSS_Selecting:
        //  職業選択
        RoleSelecter->NowTime = RoleSelecter->MaxTime;
        CalcRoleLoop();
        {
            FVector2D LeftAxis = BattleController->GetLeftAxis();


            if (BattleController->IsOkTrigger())
            {
                //  配置画面へ
                PlayerState->SetReplicated_CallID(ERoleSelectCallID::ERSCID_ChangeState_ToArrangement);
                ChangeState_ToArrangement(PlayerState);
                break;
            }
            if (BattleController->IsCanselTrigger())
            {
                PlayerState->SetReplicated_CallID(ERoleSelectCallID::ERSCID_ChangeState_RoleSelectingToNone);
                ChangeState_RoleSelectingToNone(PlayerState);
                break;
            }


            if (LeftAxis.Length() > FLT_EPSILON) {
                float AbsX = FMath::Abs(LeftAxis.X);
                float AbsY = FMath::Abs(LeftAxis.Y);




                if (AbsX > AbsY)
                {
                    SelecteBeforedJob = GetRoleSelectFromCursorIndex();
                    int RSIndex = RoleSelectIndex;
                    if (LeftAxis.X < 0.0f)
                    {
                        --RSIndex;
                        //  右
                        if (RSIndex < 0)
                        {
                            RSIndex += RoleSelectCharFace.Num();
                        }
                    }
                    if (LeftAxis.X > 0.0f)
                    {
                        //  左
                        ++RSIndex;
                        if (RSIndex >= RoleSelectCharFace.Num())
                        {
                            RSIndex -= RoleSelectCharFace.Num();
                        }
                    }
                    RoleSelectIndex = RSIndex;
                    SelectedJob = GetRoleSelectFromCursorIndex();
                    SetRoleSelectCursorPosition(GetRoleSelectFromCursorIndex(), PlayerState);


                    RoleSelecter->Startup();
                    ChangeState_SelectingNext(PlayerState);
#if 0
                    PlayerState->SetReplicated_RoleSelectJobBefore(SelecteBeforedJob);
                    PlayerState->SetReplicated_RoleSelectIndex(RoleSelectIndex);
                    PlayerState->SetReplicated_RoleSelectJob(SelectedJob);
                    PlayerState->SetReplicated_SlotState(ERpoleSelectSlotState::ERSSS_SelectingAnim);
                    SlotState = ERpoleSelectSlotState::ERSSS_SelectingAnim;
#endif
                }
                break;
            }
        }
        break;

    case ERpoleSelectSlotState::ERSSS_SelectingNext:
        ChangeState_SelectingNext(PlayerState);
        break;
    case ERpoleSelectSlotState::ERSSS_SelectingAnim:
        RoleSelecter->AddDT(DT);
//        PlayerState->SetReplicated_RoleSelectTime(RoleSelecter->NowTime);
        CalcRoleLoop();

        if(RoleSelecter->IsEnd())
        {
            PlayerState->SetReplicated_SlotState(ERpoleSelectSlotState::ERSSS_Selecting);
            SlotState = ERpoleSelectSlotState::ERSSS_Selecting;
        }
        else
        {
            //  ここでコマンドを発行しておかないと計算が行われない。
            PlayerState->SetReplicated_SlotState(ERpoleSelectSlotState::ERSSS_SelectingAnim);
            SlotState = ERpoleSelectSlotState::ERSSS_SelectingAnim;
        }
        break;
    case ERpoleSelectSlotState::ERSSS_SelectingCansel:
        //  ロールセレクタキャンセル
        PlayerState->SetReplicated_RoleSelectState(ERoleSelectState::ERS_None);
        PlayerState->SetReplicated_SlotState(ERpoleSelectSlotState::ERSSS_None);
        SlotState = ERpoleSelectSlotState::ERSSS_None;
        break;
    case ERpoleSelectSlotState::ERSSS_Arrangement:
        //  配置
        if (RoleArrangementUnitStage == nullptr)
        {
            ArrangementSetup();
        }
        {
#if 0
            PlayerState->SetReplicated_ArrangementStartPosX(RoleArrangementUnitStage->UnitPosition.X);
            PlayerState->SetReplicated_ArrangementStartPosY(RoleArrangementUnitStage->UnitPosition.Y);
            PlayerState->SetReplicated_ArrangementUnitState(RoleArrangementUnitStage->StartPositionState);
#endif
//            RoleArrangementUnitStage->CalcUnitPosition();

            switch (RoleArrangementUnitStage->StartPositionState)
            {
            case EAUState::EAUState_Begin:
                PlayerState->SetReplicated_SlotState(ERpoleSelectSlotState::ERSSS_Arrangement);
                SlotState = ERpoleSelectSlotState::ERSSS_Arrangement;
                break;
            case EAUState::EAUState_Selected:
                ChangeState_PositionSet(PlayerState);
                break;
            case EAUState::EAUState_ReadyWait:
                ChangeState_ReadyWait(PlayerState);
                break;
            case EAUState::EAUState_SelectPositionCansel:
                PlayerState->SetReplicated_CallID(ERoleSelectCallID::ERSCID_ChangeState_SelectPositionCansel);
                ChangeState_SelectPositionCansel(PlayerState);
                break;
            case EAUState::EAUState_StartPosX:
                PlayerState->SetReplicated_ArrangementStartPosX(RoleArrangementUnitStage->UnitPosition.X);
                RoleArrangementUnitStage->CalcUnitPosition();
                break;
            case EAUState::EAUState_StartPosY:
                PlayerState->SetReplicated_ArrangementStartPosY(RoleArrangementUnitStage->UnitPosition.Y);
                RoleArrangementUnitStage->CalcUnitPosition();
                break;
            }
#if 0
            if (RoleArrangementUnitStage->StartPositionState == EAUState::EAUState_Selected)
            {
                //  選択したユニットデータを取得
                //PlayerState->SendServerMessage(ARRANGEMENT_SYNC_SELECTED);
                ChangeState_PositionSet(PlayerState);
            }
            else if (RoleArrangementUnitStage->StartPositionState == EAUState::EAUState_ReadyWait)
            {
                //  一つ上を閉じる
                //PlayerState->SendServerMessage(ARRANGEMENT_SYNC_READY_WAIT);
                ChangeState_ReadyWait(PlayerState);
            }
            else if (RoleArrangementUnitStage->StartPositionState == EAUState::EAUState_SelectPositionCansel)
            {
                //  キャンセル
                //PlayerState->SendServerMessage(ARRANGEMENT_SYNC_CANSEL);
                ChangeState_SelectPositionCansel(PlayerState);
            }
#endif
        }
        break;

#if 0
    case ERpoleSelectSlotState::ERRSS_ArrangementCansel:
        //  ユニット配置キャンセル
        if (RoleArrangementUnitStage)
        {
            ChangeState_ArrangementCansel(PlayerState,true);
        }
        break;
#endif
    case ERpoleSelectSlotState::ERRSS_CheckReady:
        if (RoleArrangementUnitStage)
        {
            if (BattleController->IsCanselTrigger())
            {
                //  最終確認キャンセルへ
                //  ユニット配置に戻る
//                PlayerState->SendServerMessage(ARRANGEMENT_SYNC_READY_CANCEL);
                PlayerState->SetReplicated_CallID(ERoleSelectCallID::ERSCID_ChangeState_ReadyCansel);
                ChangeState_ReadyCansel(PlayerState);
                break;
            }

            if (BattleController->IsOkTrigger())
            {
//                PlayerState->SendServerMessage(ARRANGEMENT_SYNC_READY);
                PlayerState->SetReplicated_SlotState(ERpoleSelectSlotState::ERRSS_Ready);
                SlotState = ERpoleSelectSlotState::ERRSS_Ready;
                //  出撃準備完了へ
                GetReady();
                break;
            }

        }
        break;
    }

}


void URoleSelectPage::TickSlotNetWorkProc(ARoleSelectPlayerState* PlayerState, float DT)
{
    FRoleSelectStateData    DataState;
    while (!PlayerState->RoleSelectStateDataFIFO.IsEmpty() || PlayerState->NowDataState.IsStayApply)
    {
        if (!PlayerState->RoleSelectStateDataFIFO.IsEmpty())
        {   //  コマンドバッファにデータがある場合はそちらを優先して処理する
            //  前回の処理が完了していない場合は同じ内容で処理を行う
            DataState = PlayerState->RoleSelectStateDataFIFO.Last();

            if (DataState.IsStayApply)
            {
                PlayerState->NowDataState = DataState;
            }

        }
        else
        {
            //  コマンドバッファにデータがない場合は前回の内容で処理を行う
            DataState = PlayerState->NowDataState;
            if (DataState.IsStayApply == false)
            {
                //  前回の処理が完了している場合は終了
                return;
            }
        }
        switch (DataState.DataType)
        {
        case ERoleSelectDataType::ERSDT_None:
            break;
        case ERoleSelectDataType::ERSDT_Nagosiation:
            break;
        case ERoleSelectDataType::ERSDT_SlotState:
            switch (DataState.SlotState)
            {
            case ERpoleSelectSlotState::ERSSS_None:
                break;
            case ERpoleSelectSlotState::ERSSS_SlotCansel:
                ChangeState_BeforeSlot(PlayerState, true);
                break;
            case ERpoleSelectSlotState::ERSSS_Selecting:
                RoleSelecter->NowTime = RoleSelecter->MaxTime;
                CalcRoleLoop();
                break;
            case ERpoleSelectSlotState::ERSSS_SelectingAnim:
                RoleSelectIndex = PlayerState->GetReplicated_RoleSelectIndex();
//                RoleSelecter->MaxTime = PlayerState->GetReplicated_RoleSelectTimeMax();
//                RoleSelecter->NowTime = PlayerState->GetReplicated_RoleSelectTime();
                SelecteBeforedJob = PlayerState->GetReplicated_RoleSelectJobBefore();
                SelectedJob = PlayerState->GetReplicated_RoleSelectJob();
                RoleSelecter->AddDT(DT);
                CalcRoleLoop();
                ClearRoleSelectArrow();
                SetRoleSelectArrow();
                SetRoleNameInfoFromJobID(GetRoleSelectFromCursorIndex());
                break;
            case ERpoleSelectSlotState::ERSSS_SelectingNext:
                break;
            case ERpoleSelectSlotState::ERSSS_SelectingCansel:
                break;
#if 1
            case ERpoleSelectSlotState::ERSSS_Arrangement:

                if (RoleArrangementUnitStage)
                {
                    switch (DataState.ArrangementUnitState)
                    {

                    case EAUState::EAUState_None:
                        break;
                    case EAUState::EAUState_Begin:
                        //  起動
                        ArrangementSetup();
                        RoleArrangementUnitStage->JobID = SelectedJob;
                        RoleArrangementUnitStage->BeginArrangementUnitStage();
                        break;

                    case EAUState::EAUState_SelectPosition:
                        break;
                    case EAUState::EAUState_Selected:
                        ChangeState_PositionSet(PlayerState, true);
                        break;
                    case EAUState::EAUState_SelectPositionCansel:
                        ChangeState_SelectPositionCansel(PlayerState, true);
                        break;
                    case EAUState::EAUState_StartPosX:
                        RoleArrangementUnitStage->UnitPosition.X = PlayerState->GetReplicated_ArrangementStartPosX();
                        RoleArrangementUnitStage->CalcUnitPosition();
                        break;
                    case EAUState::EAUState_StartPosY:
                        RoleArrangementUnitStage->UnitPosition.Y = PlayerState->GetReplicated_ArrangementStartPosY();
                        RoleArrangementUnitStage->CalcUnitPosition();
                        break;
                    case EAUState::EAUState_ReadyWait:
                        ChangeState_ReadyWait(PlayerState, true);
                        break;
                    case EAUState::EAUState_Ready:
                        break;
                    }
                }
#endif
#if 0
                    if (RoleArrangementUnitStage->StartPositionState == EAUState::EAUState_Selected)
                    {
                        //  選択したユニットデータを取得
//                        PlayerState->SendServerMessage(ARRANGEMENT_SYNC_SELECTED);
                        ChangeState_PositionSet(PlayerState,true);
                    }
                    else if (RoleArrangementUnitStage->StartPositionState == EAUState::EAUState_ReadyWait)
                    {
                        //  一つ上を閉じる
//                        PlayerState->SendServerMessage(ARRANGEMENT_SYNC_READY_WAIT);
                        ChangeState_ReadyWait(PlayerState,true);
                    }
                    else if (RoleArrangementUnitStage->StartPositionState == EAUState::EAUState_SelectPositionCansel)
                    {
                        //  キャンセル
//                        PlayerState->SendServerMessage(ARRANGEMENT_SYNC_CANSEL);
                        ChangeState_SelectPositionCansel(PlayerState,true);
                    }
#endif
                break;
            case ERpoleSelectSlotState::ERRSS_CheckReady:
                break;
            case ERpoleSelectSlotState::ERRSS_Ready:
                GetReady();
                break;
            }
            break;
        case ERoleSelectDataType::ERSDT_SlotSelectIndex:
            break;
        case ERoleSelectDataType::ERSDT_GetReady:
            break;


        case ERoleSelectDataType::ERSDT_RoleSelectState:
            switch (DataState.RoleSelectState)
            {
            case ERoleSelectState::ERS_None:
                break;
            case ERoleSelectState::ERS_RoleSelect:
                break;
            case ERoleSelectState::ERS_Arrangement:
                if (RoleArrangementUnitStage)
                {
                    switch (DataState.ArrangementUnitState)
                    {
                    case EAUState::EAUState_Begin:
                        ArrangementSetup();
                        RoleArrangementUnitStage->JobID = SelectedJob;
                        RoleArrangementUnitStage->BeginArrangementUnitStage();
                        break;
                    case EAUState::EAUState_SelectPosition:
                        RoleArrangementUnitStage->CalcUnitPosition();
                        break;
                    case EAUState::EAUState_Selected:   //  配置した
                        ChangeState_PositionSet(PlayerState, true);
                        break;
                    case EAUState::EAUState_ReadyWait:   //  配置完了して最終確認待ち
                        ChangeState_ReadyWait(PlayerState, true);
                        break;
                    case EAUState::EAUState_SelectPositionCansel:   //  配置キャンセルしてロール選択に戻る
                        ChangeState_SelectPositionCansel(PlayerState, true);
                        break;
                    case EAUState::EAUState_StartPosX:
                        RoleArrangementUnitStage->UnitPosition.X = PlayerState->GetReplicated_ArrangementStartPosX();
                        RoleArrangementUnitStage->CalcUnitPosition();
                        break;
                    case EAUState::EAUState_StartPosY:
                        RoleArrangementUnitStage->UnitPosition.Y = PlayerState->GetReplicated_ArrangementStartPosY();
                        RoleArrangementUnitStage->CalcUnitPosition();
                        break;
                    }
                }
                break;
            }
            break;
        case ERoleSelectDataType::ERSDT_RoleSelectIndex:
            RoleSelectIndex = DataState.RoleSelectIndex;
            break;
        case ERoleSelectDataType::ERSDT_RoleSelectJob:
            SelectedJob = DataState.RoleSelectJob;
            break;
        case ERoleSelectDataType::ERSDT_RoleSelectJobBefore:
            SelecteBeforedJob = DataState.RoleSelectJobBefore;
            break;
        case ERoleSelectDataType::ERSDT_RoleSelectTime:
            RoleSelecter->NowTime = DataState.RoleSelectTime;
            break;
        case ERoleSelectDataType::ERSDT_RoleSelectTimeMax:
            RoleSelecter->MaxTime = DataState.RoleSelectTimeMax;
            break;
#if 0
        case ERoleSelectDataType::ERSDT_ArrangementState:
            if (RoleArrangementUnitStage)
            {
                RoleArrangementUnitStage->StartPositionState = PlayerState->GetReplicated_ArrangementUnitState();

                switch (RoleArrangementUnitStage->StartPositionState)
                {
                case EAUState::EAUState_SelectPosition:
                    RoleArrangementUnitStage->CalcUnitPosition();
                    break;
                case EAUState::EAUState_Selected:   //  配置した
                    ChangeState_PositionSet(PlayerState, true);
                    break;
                case EAUState::EAUState_ReadyWait:   //  配置完了して最終確認待ち
                    return;
                case EAUState::EAUState_SelectPositionCansel:   //  配置キャンセルしてロール選択に戻る
#if 1
                    ChangeState_SelectPositionCansel(PlayerState, true);
#endif
                    break;
                }
            }
            break;
        case ERoleSelectDataType::ERSDT_ArrangementStartX:
            if (RoleArrangementUnitStage)
            {
                RoleArrangementUnitStage->UnitPosition.X = PlayerState->GetReplicated_ArrangementStartPosX();
                RoleArrangementUnitStage->CalcUnitPosition();
            }
            break;
        case ERoleSelectDataType::ERSDT_ArrangementStartY:
            if (RoleArrangementUnitStage)
            {
                RoleArrangementUnitStage->UnitPosition.Y = PlayerState->GetReplicated_ArrangementStartPosY();
                RoleArrangementUnitStage->CalcUnitPosition();
            }
            break;
#endif
        case ERoleSelectDataType::ERSDT_CallID:
            //  コールID
            switch (DataState.CallID)
            {
            case ERoleSelectCallID::ERSCID_ChangeState_Selecting:
                ChangeState_Selecting(PlayerState, true);
                break;
            case ERoleSelectCallID::ERSCID_ChangeState_SelectingNext:
                ChangeState_SelectingNext(PlayerState, true);
                break;
            case ERoleSelectCallID::ERSCID_ChangeState_BeforeSlot:
                ChangeState_BeforeSlot(PlayerState, true);
                break;
            case ERoleSelectCallID::ERSCID_ChangeState_RoleSelectingToNone:
                ChangeState_RoleSelectingToNone(PlayerState, true);
                break;
            case ERoleSelectCallID::ERSCID_ChangeState_ToArrangement:
                ChangeState_ToArrangement(PlayerState, true);
                break;
            case ERoleSelectCallID::ERSCID_ChangeState_ReadyCansel:
                ChangeState_ReadyCansel(PlayerState, true);
                break;
            case ERoleSelectCallID::ERSCID_ChangeState_SelectPositionCansel:
                ChangeState_SelectPositionCansel(PlayerState,true);
                break;

            }
            break;
        }

        //  ここに着たら次のコマンドを実行する
        if (PlayerState->RoleSelectStateDataFIFO.IsEmpty() == false)
        {
            PlayerState->RoleSelectStateDataFIFO.Pop();
        }
        if (PlayerState->RoleSelectStateDataFIFO.IsEmpty())
        {
            //  コマンドがなくなったのでそのまま終了
            break;
        }
        

    }

}

void URoleSelectPage::TickSlotNPCProc(ARoleSelectPlayerState* PlayerState, float DT)
{

}



void URoleSelectPage::CreateRoleSelectGph()
{
    UWorld* World = GetWorld();
    if (World)
    {
        FString BPName;

        if (TeamID == EUnitTeamID::EUTID_Team1)
        {
            BPName = TEAM1_BP_ROLESELECT_NAME;
        }
        else
        {
            BPName = TEAM2_BP_ROLESELECT_NAME;
        }

        for (TActorIterator<ARoleSelectScreen> It(World); It; ++It)
        {
            FString WorldName = It->GetName();
            if (WorldName == BPName)
            {
                RoleSelectScreen = *It;
                break;
            }
        }
        if (!RoleSelectScreen)
        {
            UE_LOG(LogTemp, Warning, TEXT("World Not Find BP_RoleSelectScreen_P?!"));
        }
        else
        {

            if (RoleSelectScreen->RoleSelectCamera == nullptr)
            {
                UCameraComponent* CameraComp = Cast<UCameraComponent>(RoleSelectScreen->FindComponentByClass(UCameraComponent::StaticClass()));
                if (CameraComp)
                {
                    RoleSelectScreen->RoleSelectCamera = CameraComp;
                    RoleSelectScreen->RoleSelectCamera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("RoleSelectScreen Not Find CameraComponent?!"));
                }
            }
        }
    }
}

void URoleSelectPage::ClearRoleSelectArrow()
{
    for (TArray<TObjectPtr<UCharaFace>>::TIterator Ite = RoleSelectCharFace ; Ite; ++Ite)
    {
        (*Ite)->SetArrow(false);
    }
}


void URoleSelectPage::SetRoleSelectArrow()
{
    TObjectPtr<UCharaFace>  ArrowFace = RoleSelectCharFace[RoleSelectIndex];
    ArrowFace->SetArrow(true);
}

void URoleSelectPage::CreateRoleSelecter()
{
    RoleSelecter = GetWorld()->SpawnActor<ARoleSelecter>();
    RoleSelecter->MaxTime = RoleSelecter->NowTime = ROLE_SELECT_TIME;
}

void URoleSelectPage::CreateRoleArrangementUnitStage()
{
    if (!RoleArrangementUnitStage)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            for (TActorIterator<ARoleArrangementUnitStage> It(World); It; ++It)
            {
                ARoleArrangementUnitStage* praus = *It;

                if (praus->TeamID == TeamID)
                {
                    RoleArrangementUnitStage = praus;
                    break;
                }
            }
        }
    }
}


int URoleSelectPage::GetRoleSelectCursorIndex(EUnitJob job) const
{
    int Index = 0;
    switch (job)
    {
    case EUnitJob::EUJ_Tank:
        Index = 0;
        break;
    case EUnitJob::EUJ_Rounder:
        Index = 1;
        break;
    case EUnitJob::EUJ_Magician:
        Index = 2;
        break;
    case EUnitJob::EUJ_Healer:
        Index = 3;
        break;
    default:
        Index = 0;
        break;
    }
    return Index;
}


void URoleSelectPage::SetRoleSelectCursorPosition(EUnitJob job, ARoleSelectPlayerState* PlayerState)
{
    RoleSelectIndex = GetRoleSelectCursorIndex(job);
    if (PlayerState)
    {
        PlayerState->SetReplicated_RoleSelectIndex(RoleSelectIndex);
    }
    ClearRoleSelectArrow();
    SetRoleSelectArrow();
}

EUnitJob URoleSelectPage::GetRoleSelectFromCursorIndex() const
{
    static const EUnitJob id_table[] =
    {
        EUnitJob::EUJ_Tank,
        EUnitJob::EUJ_Rounder,
        EUnitJob::EUJ_Magician,
        EUnitJob::EUJ_Healer,
    };

    int idx = FMath::Clamp(RoleSelectIndex, 0, sizeof(id_table) / sizeof(*id_table) - 1);
    return id_table[idx];
}


const FString& URoleSelectPage::GetJobNameFromID(EUnitJob jobID) const
{
    static const FString JobName[] =
    {
        TEXT("タンク"),
        TEXT("ラウンダー"),
        TEXT("マジシャン"),
        TEXT("ヒーラー"),
        TEXT("不明"),
    };


    return JobName[GetRoleSelectCursorIndex(jobID)];

}

