// Fill out your copyright notice in the Description page of Project Settings.

#include "RoleSelect/RoleSelectPage.h"
#include "Common/CharaFace.h"
#include "RoleSelect/RoleSelecter.h"
#include "RoleSelect/RoleArrangementUnitStage.h"
#include "EngineUtils.h"
#include "Camera/CameraComponent.h"
#include "RoleSelect/RoleSelectScreen.h"

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
    FQuat Result = FQuat::Slerp(BeforeQuat, NextQuat, FMath::Sin(FMath::DegreesToRadians(ROLE_SELECT_MOVE_PARAMETER) * RoleSelecter->CalcLerp()));
    RoleSelectScreen->RoleSelectCamera->SetRelativeRotation(Result);
}



void URoleSelectPage::TickSlotProc(ABattleController* BattleController, float DT)
{
    if (!BattleController || !RoleSelectScreen)
    {
        return;
    }


    int PlayerIndex = BattleController->NetPlayerIndex;




    switch (SlotState)
    {
        case ERpoleSelectSlotState::ERSSS_None:
        {

            FVector2D LeftAxis = BattleController->GetLeftAxis();


            if (BattleController->IsOkTrigger())
            {
                //  決定トリガ入力
                SlotState = ERpoleSelectSlotState::ERSSS_Selecting;
                //  ロール選択へ
                PageSetup();
               CreateRoleSelecter();
                SetRoleSelectArrow();
                RoleSelecterNormal();



                RoleSelecter->SetMaxTime(ROLE_SELECT_TIME);
                RoleSelecter->NowTime = RoleSelecter->MaxTime;
                break;

            }
            if (BattleController->IsCanselTrigger())
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
                    SlotState = ERpoleSelectSlotState::ERSSS_Arrangement;
                    //  ロール選択へ
                    EUnitJob    jobid = RoleArrangementUnitStage->GetLastArrangementUnitJob();

                    SetRoleNameInfoFromJobID(jobid);
                    SelectedJob = jobid;
                    SelecteBeforedJob = jobid;

                    PageSetup();
                    RoleSelecter->SetMaxTime(ROLE_SELECT_TIME);
                    RoleSelecter->NowTime = RoleSelecter->MaxTime;
                    ArrangementSetup();
                    RoleArrangementUnitStage->StartPositionState = EAUState::EAUState_Begin;
                    break;
                }
            }

            if (LeftAxis.Length() > FLT_EPSILON) {
                float AbsX = FMath::Abs(LeftAxis.X);
                float AbsY = FMath::Abs(LeftAxis.Y);
                if (AbsX > AbsY)
                {

                }
            }
        }
        break;
    case ERpoleSelectSlotState::ERSSS_Selecting:
        //  職業選択

        RoleSelecter->AddDT(DT);


        CalcRoleLoop();
        if (RoleSelecter->IsEnd())
        {
            FVector2D LeftAxis = BattleController->GetLeftAxis();


            if (BattleController->IsOkTrigger())
            {
                //  配置画面へ
                SlotState = ERpoleSelectSlotState::ERSSS_Arrangement;
                ArrangementSetup();
                break;
            }
            if (BattleController->IsCanselTrigger())
            {
                SlotState = ERpoleSelectSlotState::ERSSS_None;
                RoleSelecterClose();
                RoleSelecterDark();
                ClearRoleSelectArrow();
                //PrevSlot();
                ActiveSlot();
                RoleSelecter->NowTime = RoleSelecter->MaxTime;
                break;
            }


            if (LeftAxis.Length() > FLT_EPSILON) {
                float AbsX = FMath::Abs(LeftAxis.X);
                float AbsY = FMath::Abs(LeftAxis.Y);



                SelecteBeforedJob = GetRoleSelectFromCursorIndex();

                if (AbsX > AbsY)
                {
                    if (LeftAxis.X < 0.0f)
                    {
                        --RoleSelectIndex;
                        //  右
                        if (RoleSelectIndex < 0)
                        {
                            RoleSelectIndex += RoleSelectCharFace.Num();
                        }
                    }
                    if (LeftAxis.X > 0.0f)
                    {
                        //  左
                        ++RoleSelectIndex;
                        if (RoleSelectIndex >= RoleSelectCharFace.Num())
                        {
                            RoleSelectIndex -= RoleSelectCharFace.Num();
                        }
                    }
                    SelectedJob = GetRoleSelectFromCursorIndex();

                    RoleSelecter->Startup();

                    ClearRoleSelectArrow();
                    SetRoleSelectArrow();
                    SetRoleNameInfoFromJobID(GetRoleSelectFromCursorIndex());
                }
            }
        }
        break;

    case ERpoleSelectSlotState::ERSSS_Arrangement:
        //  配置
        if (RoleArrangementUnitStage)
        {
            if (RoleArrangementUnitStage->StartPositionState == EAUState::EAUState_Selected)
            {
                //  選択したユニットデータを取得

                //  一気に一番下の階層に戻る

                //  一つ上を閉じる
                ArrangementClose();
                //  二つ上を閉じる
                //RoleSelecterClose();
                RoleSelecterDark();
                ClearRoleSelectArrow();
                //  次のスロットへ
                NextSlot();


                //  配置処理は待機へ
                RoleArrangementUnitStage->StartPositionState = EAUState::EAUState_None;

                SlotState = ERpoleSelectSlotState::ERSSS_None;
            }
            else if (RoleArrangementUnitStage->StartPositionState == EAUState::EAUState_ReadyWait)
            {
                //  一つ上を閉じる
                ArrangementClose();
                RoleSelecterClose();
                ClearRoleSelectArrow();
                //  ロール確定判定へ
                NextSlot();
                SlotState = ERpoleSelectSlotState::ERRSS_CheckReady;
            }
            else if (RoleArrangementUnitStage->StartPositionState == EAUState::EAUState_SelectPositionCansel)
            {
                //  配置をキュンセルしロール画面へ戻る
                ArrangementClose();

                RoleSelecterOpen();
                RoleSelecterNormal();

                //  処理待機
                RoleArrangementUnitStage->StartPositionState = EAUState::EAUState_SelectPositionCansel;
                SlotState = ERpoleSelectSlotState::ERRSS_ArrangementCansel;
                RoleSelecter->SetMaxTime(ROLE_SELECT_TIME);
                RoleSelecter->NowTime = RoleSelecter->MaxTime;

                SetRoleSelectCursorPosition(SelectedJob);
            }
        }
        break;

    case ERpoleSelectSlotState::ERRSS_ArrangementCansel:
        //  ユニット配置キャンセル
        if (RoleArrangementUnitStage)
        {
            if (RoleArrangementUnitStage->StartPositionState == EAUState::EAUState_SelectPositionCansel)
            {
                RoleArrangementUnitStage->StartPositionState = EAUState::EAUState_None;
                SlotState = ERpoleSelectSlotState::ERSSS_Selecting;
                RoleSelecter->NowTime = RoleSelecter->MaxTime;
                break;
            }
        }
        break;
    case ERpoleSelectSlotState::ERRSS_CheckReady:
        if (RoleArrangementUnitStage)
        {
            if (BattleController->IsCanselTrigger())
            {
                //  最終確認キャンセルへ
                //  ユニット配置に戻る
                RoleArrangementUnitStage->StartPositionState = EAUState::EAUState_Begin;
                SlotState = ERpoleSelectSlotState::ERSSS_Arrangement;


                EUnitJob jobid = RoleArrangementUnitStage->JobID;
                SetRoleNameInfoFromJobID(jobid);
                PageSetup();
                RoleSelecter->SetMaxTime(ROLE_SELECT_TIME);
                RoleSelecter->NowTime = RoleSelecter->MaxTime;
                ArrangementSetup();
                PrevSlot();
                RoleSelecter->NowTime = RoleSelecter->MaxTime;



                break;
            }

            if (BattleController->IsOkTrigger())
            {
                SlotState = ERpoleSelectSlotState::ERRSS_Ready;
                //  出撃準備完了へ
                GetReady();
                break;
            }

        }


        break;
    }

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
            FString WorldName = It->GetActorLabel();
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

            UCameraComponent* CameraComp = Cast<UCameraComponent>(RoleSelectScreen->FindComponentByClass(UCameraComponent::StaticClass()));
            if (CameraComp)
            {
                RoleSelectScreen->RoleSelectCamera = CameraComp;
                RoleSelectScreen->RoleSelectCamera->SetRelativeRotation(FRotator(0.0f, 90.0f , 0.0f));
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("RoleSelectScreen Not Find CameraComponent?!"));
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


void URoleSelectPage::SetRoleSelectCursorPosition(EUnitJob job)
{
    RoleSelectIndex = GetRoleSelectCursorIndex(job);
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

