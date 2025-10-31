// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoManager.h"
#include "Battle/BattleHelper.h"
#include "EngineUtils.h"
#include "Battle/MasoFire.h"
#include "Battle/MasoWater.h"
#include "Battle/MasoThunder.h"
#include "Battle/MasoPanel.h"
#include "Battle/MasoPanelData.h"
#include "Math\RandomStream.h"

#define PanelRight  0
#define PanelLeft  1
// Sets default values
AMasoManager::AMasoManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMasoManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMasoManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// パネルの魔素配列に魔素を登録する.
void AMasoManager::JoinMaso(int X, int Y)
{   
    // ヘルパークラスを使用する
    BattleHelper helper;
    // 添え字を計算
    int Num = helper.CalcPanelNum(X, Y);
    TObjectPtr<AMasoPanel> TargetPanel;
    int MasoArrayNum{};
    FMasoPanelData NewPanelData; // 付与する魔素パネルのデータ

    if (Num >= 0)
    {
        TargetPanel = MasoPanelArray[Num];
        MasoArrayNum = TargetPanel->GetMasoPanelDataArraySize();
        if (MasoArrayNum >= 2)
        {
            // 魔素格納してる配列に２つ以上入っていたら魔素を付与しない
            UE_LOG(LogTemp, Warning, TEXT("There are already two Maso"));
            return;
        }
    }

    // ０～２の範囲で数値を出す.
    int TypeNum = FMath::RandRange(0, 2);
    UE_LOG(LogTemp, Warning, TEXT("randnum: %d"), TypeNum);
    // 魔素クラスのインスタンス化
    // 一旦０～２で属性を決める.
    // TODO:特技の属性によって付与する魔素を決めるようにする.
    TScriptInterface<IMasoInterface> MasoInterface;
    if (TypeNum == 0)
    {
        // 火属性の魔素インスタンス
        TObjectPtr<UMasoFire> MasoFire = NewObject<UMasoFire>(this, TEXT("UMasoFire"));
        MasoInterface = MasoFire;
    }
    if (TypeNum == 1)
    {
        // 水属性の魔素インスタンス
        TObjectPtr<UMasoWater> MasoWater = NewObject<UMasoWater>(this, TEXT("UMasoWater"));
        MasoInterface = MasoWater;
    }
    if (TypeNum == 2)
    {
        // 雷属性の魔素インスタンス
        TObjectPtr<UMasoThunder> MasoThunder = NewObject<UMasoThunder>(this, TEXT("UMasoThunder"));
        MasoInterface = MasoThunder;
    }

    if (TargetPanel)
    {
        if (TargetPanel->GetMasoPanelDataFromIndex(0)) 
        {
             FMasoPanelData* OldPanelData = TargetPanel->MasoPanelDataPtr;
             if (OldPanelData->PanelSideIndex == PanelRight) 
             {
                 NewPanelData.Maso = MasoInterface;
                 NewPanelData.PanelSideIndex = PanelLeft;
                 TargetPanel->JoinMasoPanelData(NewPanelData);
                 ChangeMasoPanelMaterial(TargetPanel, PanelLeft, true);
             }
        }else 
        {
            NewPanelData.Maso = MasoInterface;
            NewPanelData.PanelSideIndex = PanelRight;
            TargetPanel->JoinMasoPanelData(NewPanelData);
            ChangeMasoPanelMaterial(TargetPanel, PanelRight, true);
        }
    }

}

// 魔素パネルのマテリアルを変更する.
// 付与と消去時に使用する.
// join == true 付与する.
// join == false 削除する.
void AMasoManager::ChangeMasoPanelMaterial(TObjectPtr<AMasoPanel> MasoPanel, int PanelSideIndex, bool join)
{
    TScriptInterface<IMasoInterface> Maso;
    TObjectPtr<UMaterialInterface> MasoMaterial;
    TArray<UStaticMeshComponent*> MeshComponents; 
    MasoPanel->GetComponents<UStaticMeshComponent>(MeshComponents); // 魔素パネルにあるコンポーネントを取得
    UE_LOG(LogTemp, Warning, TEXT("ComponentNo.%d"), PanelSideIndex);

    if (MeshComponents.Num() > 0) 
    {
        // 魔素パネルの左右ごとに色を変える
        // MasoArrayNum = 0: 右
        // MasoArrayNum = 1: 左
        UStaticMeshComponent* CylinderComponent = MeshComponents[PanelSideIndex];


        if (MasoPanel->GetMasoPanelDataFromMasoNum(PanelSideIndex))
        {
            Maso = MasoPanel->MasoPanelDataPtr->Maso; // 魔素パネルデータの魔素を取得

            if (join) // trueなら魔素を付与
            {
                if (Maso) 
                {
                    // 魔素からマテリアルを取得する.
                    MasoMaterial = Maso->getMasoMaterial(); // 魔素クラスに基づいたマテリアルを取得
                    CylinderComponent->SetMaterial(0, MasoMaterial);
                    CylinderComponent->SetHiddenInGame(false);
                    UE_LOG(LogTemp, Warning, TEXT("魔素No.%d魔素を付与"), PanelSideIndex);
                }
            }else 
            {
                UE_LOG(LogTemp, Warning, TEXT("魔素No.%d魔素を削除"), PanelSideIndex);
                CylinderComponent->SetHiddenInGame(true);
            }
        }
        
    }
}
// Player2の陣地にある魔素の消滅までのターン数アップデート
void AMasoManager::UpdatePlayer1Maso()
{
    for (int i = 0; i < Player2MasoPanel.Num(); ++i)
    {
        // Player2側のパネルを取得
        TObjectPtr<AMasoPanel> panel = Player2MasoPanel[i];
        int ArraySize = panel->GetMasoPanelDataArraySize();
        for (int j = ArraySize - 1; j >= 0; --j)
        {
            // パネルがもっている魔素パネルデータを取得
            if (panel->GetMasoPanelDataFromIndex(j)) {
                FMasoPanelData* data = panel->MasoPanelDataPtr;
                
                data->DisappearTurn--; // ターン数のアップデート
                UE_LOG(LogTemp, Warning, TEXT("魔素No.%d魔素のターンが減少します残り%dターン"), data->PanelSideIndex, data->DisappearTurn);
                if (data->DisappearTurn == 0)
                {
                    // ターンが0ならば消滅処理スタート
                    UE_LOG(LogTemp, Warning, TEXT("0ターンなので魔素がきえます"));
                    ChangeMasoPanelMaterial(panel, data->PanelSideIndex, false);
                    panel->RemoveMasoPanelData(j);
                }
            }
        }
    }
}

// Player1の陣地にある魔素の消滅までのターン数アップデート
void AMasoManager::UpdatePlayer2Maso()
{
    for (int i = 0; i < Player1MasoPanel.Num(); ++i)
    {
        // Player1側のパネルを取得
        TObjectPtr<AMasoPanel> panel = Player1MasoPanel[i];
        int ArraySize = panel->GetMasoPanelDataArraySize();
        for (int j = ArraySize-1; j >= 0; --j)
        {
            // パネルがもっている魔素パネルデータを取得
            if (panel->GetMasoPanelDataFromIndex(j)) {
                FMasoPanelData* data = panel->MasoPanelDataPtr;

                data->DisappearTurn--; // ターン数のアップデート
                UE_LOG(LogTemp, Warning, TEXT("魔素No.%d魔素のターンが減少します残り%dターン"), data->PanelSideIndex, data->DisappearTurn);
                if (data->DisappearTurn == 0)
                {
                    // ターンが0ならば消滅処理スタート
                    UE_LOG(LogTemp, Warning, TEXT("0ターンなので魔素がきえます"));
                    ChangeMasoPanelMaterial(panel, data->PanelSideIndex, false);
                    panel->RemoveMasoPanelData(j);
                }
            }
        }
    }
}

// TODO: パネルの魔素全削除する関数.

void AMasoManager::SearchMasoPanelFromWorld()
{
    UWorld* World = GetWorld();

    if (World)
    {
        BattleHelper helper;
        for (TActorIterator<AMasoPanel> It(World); It; ++It)
        {
            AMasoPanel* MasoPanel = *It;
            if (MasoPanel)
            {
                MasoPanelArray.Add(MasoPanel);
            }
        }

        // 魔素パネルを配置する.
        for (int Num = 0; Num < MasoPanelArray.Num(); ++Num)
        {
            TObjectPtr<AMasoPanel> MasPanel = MasoPanelArray[Num];

            int X, Y;
            helper.CalcPanelPosition(&X, &Y, Num);
            FVector Location = helper.CalcPanelLocation(X, Y);
            MasPanel->GetRootComponent()->SetRelativeLocation(Location);

            if (Y < GAME_LOCATION_DEPTH / 2)
            {
                Player1MasoPanel.Add(MasPanel);
            }
            else {
                Player2MasoPanel.Add(MasPanel);
                // Player2のパネルを１８０度回転させる.
                FRotator Rotation = FRotator(0.0f, 180.0f, 0.0f);
                MasPanel->GetRootComponent()->SetRelativeRotation(Rotation);
            }
            
        }
    }
}

