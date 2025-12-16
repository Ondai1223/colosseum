// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleSelect/RoleArrangement.h"
#include "RoleSelect/RoleSelectHelper.h"
#include "RoleSelect/RoleSelectGameModeBase.h"

#define UNIT_DATA_MAX 3

// Sets default values
ARoleArrangement::ARoleArrangement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoleArrangement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoleArrangement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoleArrangement::BeginRoleArrangement(ARoleSelectGameModeBase *GameMode)
{
    TickState = ETickRoleArrangementState::ETRAS_Arranging;
}

ERoleArrangementState ARoleArrangement::TickRoleArrangement(ARoleSelectGameModeBase* GameMode, float DeltaSeconds)
{

    switch (TickState)
    {
    case ETickRoleArrangementState::ETRAS_Arranging:
        //  ロール配置中
    {
        TArray<TObjectPtr<AUnit>>& WorkUnits = GameMode->WorkUnitData.TeamID == EUnitTeamID::EUTID_Team1 ? GameMode->WorkPlayer1Units : GameMode->WorkPlayer2Units;
        TArray<TObjectPtr<AUnit>>& ArrangingUnits = GameMode->WorkUnitData.TeamID == EUnitTeamID::EUTID_Team1 ? GameMode->Player1Units : GameMode->Player2Units;
        FVector Location(0.0f, 0.0f,0.0f);
        TObjectPtr<AUnit> Unit = WorkUnits[GameMode->WorkUnitIndex];

        bool flag = GameMode->RoleSelectCursorActor->MoveCursor(DeltaSeconds, &Location);
        Unit->Set3DLocation(Location);
        int X = GameMode->RoleSelectCursorActor->MoveCursorData.X;
        int Y = GameMode->RoleSelectCursorActor->MoveCursorData.Y;
        if (flag == false)
        {
            FVector2D LeftAxis(0.0f, 0.0f);
            LeftAxis = GameMode->Controller->GetLeftAxis();
            //  移動完了

            if (LeftAxis.Length() > MOVE_CURSOR_DEAD_ZONE)
            {
                if (FMath::Abs(LeftAxis.X) > FMath::Abs(LeftAxis.Y))
                {
                    //  横移動
                    if (LeftAxis.X < 0.0f)
                    {
                        ++X;
                        if (X >= ROLE_SELECT_WIDTH)
                        {
                            X = 0;
                        }
                    }
                    else
                    {
                        //  左移動
                        --X;
                        if (X < 0)
                        {
                            X = ROLE_SELECT_WIDTH - 1;
                        }
                    }
                }
                else
                {
                    //  縦移動
                    if (LeftAxis.Y > 0.0f)
                    {
                        //  上移動
                        ++Y;
                        if (Y >= ROLE_SELECT_DEPTH)
                        {
                            Y = 0;
                        }
                    }
                    else
                    {
                        //  下移動
                        --Y;
                        if (Y < 0)
                        {
                            Y = ROLE_SELECT_DEPTH - 1;
                        }
                    }
                }
            }
            GameMode->RoleSelectCursorActor->StartMoveCursor(X, Y, MOVE_CURSOR_TIME);

            for (TArray<TObjectPtr<AUnit>>::TIterator It(ArrangingUnits); It; ++It)
            {
                TObjectPtr<AUnit> CheckUnit = *It;
                FUnitData CheckUnitData = CheckUnit->GetUnitData();
                if (CheckUnitData.StartPosX == X && CheckUnitData.StartPosY == Y)
                {
                    //  既に配置されているので配置済みのユニットは非表示
                    CheckUnit->SetVisible(false);
                }
                else
                {
                    //  配置されていないので表示
                    CheckUnit->SetVisible(true);
                }
            }
        }
        else
        {
            //  決定かキャンセルか
            if (GameMode->Controller->IsOkTrigger())
            {

                //  OKのトリガ入力
                FUnitData UnitData = Unit->GetUnitData();
                for (TArray<TObjectPtr<AUnit>>::TIterator It(ArrangingUnits); It; ++It)
                {
                    TObjectPtr<AUnit> CheckUnit = *It;
                    FUnitData CheckUnitData = CheckUnit->GetUnitData();
                    if (CheckUnitData.StartPosX == X && CheckUnitData.StartPosY == Y)
                    {
                        //  既に配置されている
                        CheckUnit->SetVisible(false);
                        ArrangingUnits.Remove(CheckUnit);
                        break;
                    }
                }

                if (ArrangingUnits.Num() < UNIT_DATA_MAX)
                {
                    Unit->PlayAnimationBuf();
                    //  配置
                    UnitData.StartPosX = X;
                    UnitData.StartPosY = Y;
                    TObjectPtr<AUnit> NewUnit = GameMode->GetWorld()->SpawnActor<AUnit>(AUnit::StaticClass());
                    NewUnit->SetUnitData(UnitData);
                    NewUnit->CreateUnitData();
                    NewUnit->Set3DScale(ROLE_CRATE_UNIT_SCALE);

                    NewUnit->Set3DLocation(Unit->Get3DLocation());
                    NewUnit->SetVisible(false); //  最初は非表示
                    ArrangingUnits.Add(NewUnit);
                    TickState = ETickRoleArrangementState::ETRAS_Animation;
                }
                else {
                    //  配置不可
                    UE_LOG(LogTemp, Warning, TEXT("Cannot place unit, maximum number reached."));
                }
            }
        }
    }


        break;
        //  アニメーション再生中
    case ETickRoleArrangementState::ETRAS_Animation:
    {
        TArray<TObjectPtr<AUnit>>& WorkUnits = GameMode->WorkUnitData.TeamID == EUnitTeamID::EUTID_Team1 ? GameMode->WorkPlayer1Units : GameMode->WorkPlayer2Units;
        TObjectPtr<AUnit> Unit = WorkUnits[GameMode->WorkUnitIndex];
        if (Unit->IsEndOfAnime())
        {
            //  アニメーション完了
            TickState = ETickRoleArrangementState::ETRAS_Arranging;
        }

    }
        break;
    case ETickRoleArrangementState::ETRAS_Completed:
        //  配置完了
        return ERoleArrangementState::ERAS_Completed;
    }
    return ERoleArrangementState::ERAS_Arranging;
}
