// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleSelect/RoleSelectUnitStartPosition.h"
#include "EngineUtils.h"
#include "RoleSelect/RoleArrangementUnitStage.h"



#define TEAM1_BP_NAME   TEXT("BP_RoleUnitArrangement_P1")
#define TEAM2_BP_NAME   TEXT("BP_RoleUnitArrangement_P2")

//  ユニット配置スクリーンのアタッチ
void URoleSelectUnitStartPosition::SetStartPositionScreen_Implementation()
{
    ;
}


void URoleSelectUnitStartPosition::SetArrangementUnit(EUnitJob Job,int SlotNo)
{

    if (!RoleArrangementUnitStage)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            FString BPName;

            if (TeamID == EUnitTeamID::EUTID_Team1)
            {
                BPName = TEAM1_BP_NAME;
            }
            else
            {
                BPName = TEAM2_BP_NAME;
            }

            for (TActorIterator<ARoleArrangementUnitStage> It(World); It; ++It)
            {
                FString WorldName = It->GetName();
                if (WorldName == BPName)
                {
                    RoleArrangementUnitStage = *It;
                    break;
                }
            }
        }
    }

    if (RoleArrangementUnitStage)
    {
        RoleArrangementUnitStage->JobID = Job;
        RoleArrangementUnitStage->StartPositionState = EAUState::EAUState_Begin;
        RoleArrangementUnitStage->SlotNo = SlotNo;
    }
}
