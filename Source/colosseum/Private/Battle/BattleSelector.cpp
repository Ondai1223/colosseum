// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/BattleSelector.h"
#include "Battle/BattleGameMode.h"
#include "Battle/BattleHelper.h"
#include "EngineUtils.h"
#include "Battle/BattleSelectPanel.h"




// Sets default values
ABattleSelector::ABattleSelector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABattleSelector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattleSelector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//  ワールドからセレクトパネルを検索
void ABattleSelector::SearchSelectPanelFromWorld()
{
    UWorld* World = GetWorld();

    if (World)
    {
        BattleHelper helper;
        for (TActorIterator<ABattleSelectPanel> It(World); It; ++It)
        {
            ABattleSelectPanel* SelectPanel = *It;
            if (SelectPanel)
            {
                SelectPanelArray.Add(SelectPanel);
            }
        }

        //  パネルを配置
        for (int Num = 0; Num < SelectPanelArray.Num(); ++Num)
        {
            TObjectPtr<ABattleSelectPanel> SelPanel = SelectPanelArray[Num];

            int X, Y;
            helper.CalcPanelPosition(&X, &Y, Num);

            FVector Location = helper.CalcPanelLocation(X, Y);
            SelPanel->GetRootComponent()->SetRelativeLocation(Location);
            SelPanel->GetRootComponent()->SetVisibility(false,true);
        }
    }
}

//  パネルのオンオフ
void ABattleSelector::SetPanel(int X, int Y, bool on)
{
    BattleHelper    helper;

    //  添え字を算出
    int Num = helper.CalcPanelNum(X, Y);
    if (Num >= 0) {
        SelectPanelArray[Num]->GetRootComponent()->SetVisibility(on, true);
    }
}


bool ABattleSelector::IsPanelEnable(int X, int Y) const
{
    BattleHelper    helper;

    //  添え字を算出
    int Num = helper.CalcPanelNum(X, Y);
    if (Num >= 0) {
        return SelectPanelArray[Num]->GetRootComponent()->IsVisible();
    }
    return false;
}

void ABattleSelector::AllOffPanel()
{
    for (int Num = 0; Num < SelectPanelArray.Num(); ++Num)
    {
        SelectPanelArray[Num]->GetRootComponent()->SetVisibility(false,true);
    }
}


void ABattleSelector::SetSelectPanelTeamValid(EUnitTeamID TeamID, bool valid)
{
    const uint8 Width = GAME_LOCATION_WIDTH;
    const uint8 Depth = GAME_LOCATION_DEPTH / 2;
    uint8 StartX = 0;
    uint8 StartY = 0;
    uint8 EndX = Width + StartX;
    uint8 EndY = Depth + StartY;

    if (TeamID == EUnitTeamID::EUTID_Team2)
    {
        //  チーム２の選択パネルの設定
        StartY = Depth;
        EndY = Depth + StartY;
    }

    for (uint8 Y = StartY; Y < EndY; ++Y)
    {
        for (uint8 X = StartX; X < EndX; ++X)
        {
            SetPanel(X, Y, valid);
        }
    }
}
