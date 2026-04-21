// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoManager.h"
#include "Battle/BattleHelper.h"
#include "EngineUtils.h"
#include "Battle/MasoFire.h"
#include "Battle/MasoWater.h"
#include "Battle/MasoThunder.h"
#include "Battle/MasoActionBase.h"
#include "Battle/MasoActionFireFire.h"
#include "Battle/MasoActionFireWater.h"
#include "Battle/MasoActionThunderFire.h"
#include "Battle/MasoActionThunderThunder.h"
#include "Battle/MasoActionWaterThunder.h"
#include "Battle/MasoActionWaterWater.h"
#include "Battle/MasoPanel.h"
#include "Battle/MasoPanelData.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Math\RandomStream.h"

#define PanelRight  0
#define PanelLeft  1
#define FireType "Fire"
#define WaterType "Water"
#define ThunderType "Thunder"
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
void AMasoManager::JoinMaso(int X, int Y, FName Type, TObjectPtr<AUnitBattleParameter> ActionUnit, ABattleGameMode* GameMode)
{   
    // ヘルパークラスを使用する
    BattleHelper helper;
    // 添え字を計算
    int Num = helper.CalcPanelNum(X, Y);
    TObjectPtr<AMasoPanel> TargetPanel;
    
    FMasoPanelData NewPanelData; // 付与する魔素パネルのデータ

    if (Num >= 0)
    {
        TargetPanel = MasoPanelArray[Num];
        
        if (!AbleJoin(TargetPanel))
        {
            // 魔素が二つあれば付与しない.
            UE_LOG(LogTemp, Warning, TEXT("魔素が二つあるので付与しない."))
            return;
        }
    }

    // 魔素クラスのインスタンス化
    TScriptInterface<IMasoInterface> MasoInterface;
    if (Type == FireType)
    {
        // 火属性の魔素インスタンス
        TObjectPtr<UMasoFire> MasoFire = NewObject<UMasoFire>(this, TEXT("UMasoFire"));
        MasoInterface = MasoFire;
    }
    if (Type == WaterType)
    {
        // 水属性の魔素インスタンス
        TObjectPtr<UMasoWater> MasoWater = NewObject<UMasoWater>(this, TEXT("UMasoWater"));
        MasoInterface = MasoWater;
    }
    if (Type == ThunderType)
    {
        // 雷属性の魔素インスタンス
        TObjectPtr<UMasoThunder> MasoThunder = NewObject<UMasoThunder>(this, TEXT("UMasoThunder"));
        MasoInterface = MasoThunder;
    }

    if (TargetPanel)
    {
        TargetPanel->PanelX = X;
        TargetPanel->PanelY = Y;
        int32 MasoKey = -1;
        
        if (TargetPanel->HasMasoData(PanelRight)) // 右側に登録されているか？
        {
            MasoKey = PanelLeft;
			NewPanelData.ActionUnit = ActionUnit; // 二つ目を付与したユニットの情報を格納.
        }
        else 
        {
            MasoKey = PanelRight;
        }

        if (MasoKey != -1)
        {
            UE_LOG(LogTemp, Warning, TEXT("魔素付与処理を始める"));
            NewPanelData.Maso = MasoInterface;
            TargetPanel->JoinMasoPanelData(MasoKey, NewPanelData);
            ChangeMasoPanelMaterial(TargetPanel, MasoKey, true);
            if (!AbleJoin(TargetPanel))
            {
                // 魔素が２つになったら.
                UE_LOG(LogTemp, Warning, TEXT("魔素が２つあるので発動できるか確認します."));
                ActivateMasoAction(TargetPanel, GameMode);
            }
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

    if (MeshComponents.Num() > 0) 
    {
        // 魔素パネルの左右ごとに色を変える
        // MasoArrayNum = 0: 右
        // MasoArrayNum = 1: 左
        UStaticMeshComponent* CylinderComponent = MeshComponents[PanelSideIndex];


        if (MasoPanel->GetMasoPanelData(PanelSideIndex))
        {
            FMasoPanelData* data = MasoPanel->PanelDataPtr;
            Maso = data->Maso; // 魔素パネルデータの魔素を取得
            
            if (join) // trueなら魔素を付与
            {
                if (Maso) 
                {
                    UE_LOG(LogTemp, Warning, TEXT("魔素No.%d魔素を付与"), PanelSideIndex);
                    // 魔素からマテリアルを取得する.
                    MasoMaterial = Maso->getMasoMaterial(); // 魔素クラスに基づいたマテリアルを取得
                    CylinderComponent->SetMaterial(0, MasoMaterial);
                    CylinderComponent->SetHiddenInGame(false);
                    CreateNiagaraComponent(Maso->getNaiagaraSystem(), CylinderComponent, PanelSideIndex);
                    data->MasoEffect = MasoPanelEffectComponent;
                    
                }
            }else 
            {
                UE_LOG(LogTemp, Warning, TEXT("魔素No.%d魔素を削除"), PanelSideIndex);
                CylinderComponent->SetHiddenInGame(true);
                data->MasoEffect->DestroyComponent();
                data->MasoEffect = nullptr;
            }
        }
        
    }
}

// Player1が付与した魔素はPlayer2の陣地にある.
// Player1のターン終了後
// Player2の陣地にある魔素の消滅までのターン数アップデート
void AMasoManager::UpdatePlayer1Maso()
{
    TArray<int32> Keys;
    for (TObjectPtr<AMasoPanel> panel : Player2MasoPanel)
    {
        panel->GetMasoKeys(Keys);
        for (int32 Key : Keys)
        {
            if (panel->GetMasoPanelData(Key))
            {
                FMasoPanelData* data = panel->PanelDataPtr;

                if (!panel->GetIsActive())
                {
                    data->DisappearTurn--; // ターン数のアップデート
                    UE_LOG(LogTemp, Warning, TEXT("魔素のターンが減少します残り%dターン"), data->DisappearTurn);
                }

                if (data->DisappearTurn == 0)
                {
                    // ターンが0ならば消滅処理スタート
                    UE_LOG(LogTemp, Warning, TEXT("0ターンなので魔素がきえます"));
                    ChangeMasoPanelMaterial(panel, Key, false);
                    panel->RemoveMasoPanelData(Key);
                }
            }
        }
    }
}

// Player2が付与した魔素はPlayer2の陣地にある.
// Player2のターン終了後
// Player1の陣地にある魔素の消滅までのターン数アップデート
void AMasoManager::UpdatePlayer2Maso()
{
    TArray<int32> Keys;
    for (TObjectPtr<AMasoPanel> panel: Player1MasoPanel)
    {
        panel->GetMasoKeys(Keys);
        for (int32 Key: Keys)
        {
            if (panel->GetMasoPanelData(Key))
            {
                FMasoPanelData* data = panel->PanelDataPtr;
                
                if (!panel->GetIsActive())
                {
                    data->DisappearTurn--; // ターン数のアップデート
                    UE_LOG(LogTemp, Warning, TEXT("魔素のターンが減少します残り%dターン"), data->DisappearTurn);
                }

                if (data->DisappearTurn == 0)
                {
                    // ターンが0ならば消滅処理スタート
                    UE_LOG(LogTemp, Warning, TEXT("0ターンなので魔素がきえます"));
                    ChangeMasoPanelMaterial(panel, Key, false);
                    panel->RemoveMasoPanelData(Key);
                }
            }
        }
    }
}

// Player1のターン終了後Player1陣営に付与されている魔素が発動するか確認.
void AMasoManager::ResolvePlayer1PendingMasoActions(ABattleGameMode* GameMode)
{
    for (TObjectPtr<AMasoPanel> panel : Player1MasoPanel)
    {
        if (!AbleJoin(panel))
        {
            // パネルに魔素が２つある状態.
            UE_LOG(LogTemp, Warning, TEXT("魔素が２つあるので発動できるか確認します."));
            ActivateMasoAction(panel, GameMode);
        }
    }
}

// Player2のターン終了後Player2陣営に付与されている魔素が発動するか確認.
void AMasoManager::ResolvePlayer2PendingMasoActions(ABattleGameMode* GameMode)
{
    for (TObjectPtr<AMasoPanel> panel : Player2MasoPanel)
    {
        if (!AbleJoin(panel))
        {
            // パネルに魔素が２つある状態.
            UE_LOG(LogTemp, Warning, TEXT("魔素が２つあるので発動できるか確認します."));
            ActivateMasoAction(panel, GameMode);
        }
    }

}

void AMasoManager::UpdateTurnMasoActions()
{
    if(MasoActionList.Num() == 0)
    {
        return;
	}
   for(int i = MasoActionList.Num()-1; i >= 0 ; --i)
   {
       TObjectPtr<UMasoActionBase> MasoAction = MasoActionList[i];     
       if (MasoAction)
       {
           MasoAction->UpdateDuration();
           if(MasoAction->GetDuration() <= 0)
           {
               UE_LOG(LogTemp, Warning, TEXT("0ターンになりました"));
               MasoActionList.RemoveAt(i);
		   }
       }
   }
}

// まだパネルに魔素が入るかどうかMax2つ.
bool AMasoManager::AbleJoin(TObjectPtr<AMasoPanel> MasoPanel)
{
    int MasoMapNum{};
    MasoMapNum = MasoPanel->GetMasoPanelDataMapSize();

    if (MasoMapNum >= 2)
    { 
        return false;
    }
    return true;
}

// 魔素の組み合わせを決定.
// 組み合わさったらtrueを返す.
bool AMasoManager::GetCombinedMasoElements(FMasoPanelData* maso1, FMasoPanelData* maso2)
{
    FString Element1 = maso1->Maso->getMasoType();
    FString Element2 = maso2->Maso->getMasoType();

    if (Element1 == FireType && Element2 == FireType)
    {
        CurrentMasoAction = NewObject<UMasoActionFireFire>(this);
        UE_LOG(LogTemp, Warning, TEXT("火と火を組み合わせます."))
            return true;
    }
    else if (Element1 == WaterType && Element2 == WaterType)
    {
        CurrentMasoAction = NewObject<UMasoActionWaterWater>(this);
        UE_LOG(LogTemp, Warning, TEXT("水と水を組み合わせます."))
            return true;
    }
    else if (Element1 == ThunderType && Element2 == ThunderType)
    {
        CurrentMasoAction = NewObject<UMasoActionThunderThunder>(this);
        UE_LOG(LogTemp, Warning, TEXT("雷と雷を組み合わせます."))
            return true;
    }
    else if ((Element1 == FireType || Element1 == WaterType)  && (Element2 == FireType || Element2 == WaterType))
    {
        CurrentMasoAction = NewObject<UMasoActionFireWater>(this);
        UE_LOG(LogTemp, Warning, TEXT("火と水を組み合わせます."))
        return true;
    }
    else if ((Element1 == WaterType || Element1 == ThunderType) && (Element2 == WaterType|| Element2 == ThunderType))
    {
        CurrentMasoAction = NewObject<UMasoActionWaterThunder>(this);
        UE_LOG(LogTemp, Warning, TEXT("水と雷を組み合わせます."))
        return true;
    }
    else if ((Element1 == ThunderType || Element1 == FireType) && (Element2 == ThunderType || Element2 == FireType))
    {
        CurrentMasoAction = NewObject<UMasoActionThunderFire>(this);
        UE_LOG(LogTemp, Warning, TEXT("雷と火を組み合わせます."))
        return true;
    }
    return false;
}

// 発動型によって魔素の効果を発動させる.
void AMasoManager::ActivateMasoAction(TObjectPtr<AMasoPanel> MasoPanel, ABattleGameMode* GameMode)
{
    UMasoActionBase* NewAction = nullptr;
    FMasoPanelData* maso1 = nullptr;
    FMasoPanelData* maso2 = nullptr;
    ActionPanel = MasoPanel;
    MasoGameMode = GameMode;
    JointedUnit = MasoPanel->PanelDataPtr->ActionUnit;

    if (MasoPanel->GetMasoPanelData(PanelRight))
    {
        maso1 = MasoPanel->PanelDataPtr;
    }
    if (MasoPanel->GetMasoPanelData(PanelLeft))
    {
        maso2 = MasoPanel->PanelDataPtr;
    }
    if (GetCombinedMasoElements(maso1, maso2))
    {
		NewAction = CurrentMasoAction;
		CurrentMasoAction = nullptr;
    }

    if(NewAction)
    {
#if 0
        ClearActionResult();
        MasoPanel->SetIsActive(true);
        OnMasoAction();
#else		
        switch (NewAction->GetActionType())
        {
        case EActionType::EAT_Normal: //通常型の処理
            if (maso1->DisappearTurn == 2 && maso2->DisappearTurn == 2)
            {
                UE_LOG(LogTemp, Warning, TEXT("通常型：次の相手のターン終了時に発動します."))
                return;
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("通常型：魔素発動します."))
                ClearActionResult();
                MasoPanel->SetIsActive(true);
                OnMasoAction(NewAction);
            }
            break;

        case EActionType::EAT_Immediate: // 速攻型の処理
            UE_LOG(LogTemp, Warning, TEXT("速攻型：すぐに発動します."))
            ClearActionResult();
            MasoPanel->SetIsActive(true);
            OnMasoAction(NewAction);
            break;
        }
#endif
    }
}

// 魔素パネルを初期の状態にする.
void AMasoManager::ResetMasoPanel()
{
    ActionPanel->SetIsActive(false);
    ChangeMasoPanelMaterial(ActionPanel, PanelRight, false);
    ChangeMasoPanelMaterial(ActionPanel, PanelLeft, false);
    ActionPanel->AllRemoveMasoPanelData();
    UE_LOG(LogTemp, Warning, TEXT("指定された魔素パネルを初期化します."))
}

void AMasoManager::DeactivateMasoAction(TObjectPtr<AMasoPanel> MasoPanel)
{
 
}

void AMasoManager::MasoActionEffect(UMasoActionBase* MasoAction)
{
    MasoAction->ActionEffect(ActionPanel);
}

void AMasoManager::MasoActionCalculate(UMasoActionBase* MasoAction)
{
    MasoAction->CalcAction(&ActionResult, ActionPanel->PanelX, ActionPanel->PanelY, JointedUnit, MasoGameMode);
    MasoAction->ReflectAction(ActionResult, MasoGameMode);
}

float AMasoManager::GetMasoActionTime(UMasoActionBase* MasoAction)
{
    return MasoAction->GetActionTime();
}

void AMasoManager::CreateNiagaraComponent(TObjectPtr<UNiagaraSystem> MasoPanelNiagaraSystem, UStaticMeshComponent* component, int PanelSideIndex)
{
    FRotator Rotate = FRotator::ZeroRotator;
    if (PanelSideIndex == PanelRight)
    {
        Rotate = FRotator(0, 180, 0);
    }
    if (MasoPanelNiagaraSystem)
    {
        // NiagaraComponentを取得
        MasoPanelEffectComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
            MasoPanelNiagaraSystem,
            component,
            NAME_None,
            FVector::ZeroVector,
            Rotate,
            FVector::OneVector,
            EAttachLocation::KeepRelativeOffset,
            true,
            ENCPoolMethod::None,
            true,
            true
        );
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load NiagaraSystem"));
    }
}
void AMasoManager::ClearActionResult()
{
    ActionResult.ActionUnit = nullptr;
    ActionResult.ActionAttackResult.AttackTargets.Empty();
    ActionResult.ActionMoveResult.RouteLocation.Empty();
    ActionResult.ActionSkillResult.TargetUnits.Empty();
}

bool AMasoManager::IsMasoActionActive()
{
    for (UMasoActionBase* MasoAction : MasoActionList)
    {
        if (MasoAction && MasoAction->IsEffected)
        {
            return true;
	    }
    }
    return false;
}

void AMasoManager::OnMasoAction_Implementation(UMasoActionBase* LaunchedAction)
{
}

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
                // Player2のパネルを１８０度回転させる.
                FRotator Rotation = FRotator(0.0f, 180.0f, 0.0f);
                MasPanel->GetRootComponent()->SetRelativeRotation(Rotation);
            }
            else {
                Player2MasoPanel.Add(MasPanel);
            }
            
        }
    }
}

