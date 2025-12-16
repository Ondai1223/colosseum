// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleSelect/RoleSelectGameModeBase.h"
#include "RoleSelect/RoleSelectHelper.h"
#include "RoleSelect/RoleArrangement.h"


/**
 *ロールセレクトゲームモードベース
 */

void ARoleSelectGameModeBase::BeginRoleSelectGameMode()
{
    // ロールセレクトゲームモード開始処理

    UWorld* World = GetWorld();
    if (World == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("World is null in BeginRoleSelectGameMode"));
    }
    else
    {
        //  選択カーソル
        RoleSelectCursorActor = World->SpawnActor<ARoleSelectCursor>(ARoleSelectCursor::StaticClass());
        if (RoleSelectCursorActor == nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to spawn RoleSelectCursorActor in BeginRoleSelectGameMode"));
        }
        else
        {
            RoleSelectCursorActor->CreateRoleArrangementCursor();
            WorkUnitData.StartPosX = RoleSelectCursorActor->MoveCursorData.X;
            WorkUnitData.StartPosY = RoleSelectCursorActor->MoveCursorData.Y;
        }
    }

    WorkUnitData.TeamID = EUnitTeamID::EUTID_Team1;
    WorkUnitData.Job = EUnitJob::EUJ_Tank;

    CreateWorkUnit(WorkPlayer1Units,EUnitTeamID::EUTID_Team1);
    CreateWorkUnit(WorkPlayer2Units, EUnitTeamID::EUTID_Team2);


    //  ロール選択配置インターフェース作成
    RoleArrangementInterface = NewObject<ARoleArrangement>(this, ARoleArrangement::StaticClass());


    if (RoleArrangementInterface)
    {
        RoleArrangementInterface->BeginRoleArrangement(this);
        NowProccessState = ERoleSelectState::ERS_RoleSelect;
    }


}


void ARoleSelectGameModeBase::TickRoleSelectGameMode( float DeltaSeconds )
{
    // ロールセレクトゲームモード処理
    if (RoleArrangementInterface)
    {
        ERoleArrangementState State = RoleArrangementInterface->TickRoleArrangement(this, DeltaSeconds);
        switch (State)
        {
            case ERoleArrangementState::ERAS_Arranging:
                //  ロール配置中
                NowProccessState = ERoleSelectState::ERS_Arrangement;
                break;
            case ERoleArrangementState::ERAS_Completed:
                //  配置完了
                NowProccessState = ERoleSelectState::ERS_RoleSelect;
                break;
        }

    }
}

void ARoleSelectGameModeBase::SelectUnitWorkSpace()
{
    TArray<TObjectPtr<AUnit>>* Units = nullptr;
    if (WorkUnitData.TeamID == EUnitTeamID::EUTID_Team1)
    {
        Units = &WorkPlayer1Units;
    }
    else
    {
        Units = &WorkPlayer2Units;
    }

    for (TArray<TObjectPtr<AUnit>>::TIterator Ite(*Units); Ite; ++Ite)
    {
        (*Ite)->SetVisible(false);
    }

    RoleSelectHelper helper;

    (*Units)[WorkUnitIndex]->Set3DLocation(helper.Calc3DLocation(WorkUnitData.StartPosX,WorkUnitData.StartPosY));
    (*Units)[WorkUnitIndex]->SetVisible(true);
}


void ARoleSelectGameModeBase::CreateWorkUnit(TArray<TObjectPtr<AUnit>>& Units, EUnitTeamID TeamID)
{
    UWorld* World = GetWorld();
    if (World == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("World is null in CreateWorkUnit"));
        return;
    }


   const EUnitJob JobList[] = {
        EUnitJob::EUJ_Tank,
        EUnitJob::EUJ_Rounder,
        EUnitJob::EUJ_Healer,
        EUnitJob::EUJ_Magician
   };

   const int MaxWorkUnitNum = sizeof(JobList) / sizeof(EUnitJob);


    for (int i = 0; i < MaxWorkUnitNum; ++i)
    {
        TObjectPtr<AUnit> NewUnit = World->SpawnActor<AUnit>(AUnit::StaticClass());
        if (NewUnit == nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to spawn unit in CreateWpokUnit"));
            continue;
        }
        FUnitData UnitData;
        UnitData.TeamID = TeamID;
        UnitData.Job = JobList[i]; // 仮にタンクに設定
        NewUnit->SetUnitData(UnitData);
        NewUnit->CreateUnitData();
        NewUnit->Set3DScale(ROLE_CRATE_UNIT_SCALE);
        NewUnit->SetVisible(false); // 最初は非表示にする
        Units.Add(NewUnit);
    }
}
