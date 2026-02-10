// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleSelect/RoleArrangementUnitStage.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Battle/BattleCommon.h"
#include "RoleSelect/RoleSelectHelper.h"
#include "Battle/BattleHelper.h"


#define UNIT_ARRANGEMENT_NUM    3

#define CURSOR_NAME TEXT("Cursor")

// Sets default values
ARoleArrangementUnitStage::ARoleArrangementUnitStage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoleArrangementUnitStage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoleArrangementUnitStage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//  カーソルモデルの生成
void ARoleArrangementUnitStage::CreateCursorModel()
{
    if (!CursorModel)
    {
        TArray<USceneComponent*> Childlen;
        RootComponent->GetChildrenComponents(true, Childlen);


        for (TArray<USceneComponent*>::TIterator Ite(Childlen); Ite; ++Ite)
        {
            USceneComponent* pchild = *Ite;

            if (pchild->GetName() == CURSOR_NAME)
            {
                CursorModel = Cast<UStaticMeshComponent>(pchild);
                break;
            }
        }

        if (CursorModel)
        {
            //  カーソルの初期位置に配置
            CursorNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, UNIT_CURSOR_EFFECT_NAME);

            if (CursorNiagaraSystem)
            {
                // NiagaraComponentを取得
                CursorEffectComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
                    CursorNiagaraSystem,
                    CursorModel,
                    NAME_None,
                    FVector::ZeroVector,
                    FRotator::ZeroRotator,
                    FVector(1.7f, 1.7f, 1.0f),
                    EAttachLocation::KeepRelativeOffset,
                    true,
                    ENCPoolMethod::None,
                    true,
                    true
                );

                CursorModel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

            }
        }
    }
}


//  予めユニットを全部ロードしておく
void ARoleArrangementUnitStage::CreateUnitModel()
{
    if (TankUnits.Num() <= 0)CreateUnitModel(EUnitJob::EUJ_Tank, TankUnits, UNIT_ARRANGEMENT_NUM);
    if (RaunderUnits.Num() <= 0)CreateUnitModel(EUnitJob::EUJ_Rounder, RaunderUnits, UNIT_ARRANGEMENT_NUM);
    if (MagicianUnits.Num() <= 0)CreateUnitModel(EUnitJob::EUJ_Magician, MagicianUnits, UNIT_ARRANGEMENT_NUM);
    if (HealerUnits.Num() <= 0)CreateUnitModel(EUnitJob::EUJ_Healer, HealerUnits, UNIT_ARRANGEMENT_NUM);
}

void ARoleArrangementUnitStage::CreateUnitModel(EUnitJob job, TArray<TObjectPtr<AUnit>>& UnitArray, int Num)
{
    FUnitData   dmyUnit;

    dmyUnit.TeamID = TeamID;
    dmyUnit.Job = job;

    for (int i = 0; i < Num; ++i)
    {
        TObjectPtr<AUnit>   unit = NewObject<AUnit>(this);
        unit->SetUnitData(dmyUnit);
        unit->CreateUnitData();
        unit->SetVisible(false);
        UnitArray.Add(unit);
        unit->GetRootComponent()->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
//        unit->GetRootComponent()->SetupAttachment(RootComponent);
    }
}

//  配置積みユニット数を返す
int ARoleArrangementUnitStage::CalcNumArrangementUnit()
{
    int Num = 0;

    Num += CalcNumArrangementUnit(TankUnits);
    Num += CalcNumArrangementUnit(RaunderUnits);
    Num += CalcNumArrangementUnit(MagicianUnits);
    Num += CalcNumArrangementUnit(HealerUnits);

    return Num;
}

//  配置済みユニットを返す
int ARoleArrangementUnitStage::CalcNumArrangementUnit(const TArray<TObjectPtr<AUnit>>& Units) const
{
    int Num = 0;

    for (TArray<TObjectPtr<AUnit>>::TConstIterator It(Units); It; ++It)
    {
        AUnit* unit = *It;
        if (unit->IsVisible())
        {
            ++Num;
        }
    }
    return Num;
}

//  任意のジョブを配置するセットアップ
void ARoleArrangementUnitStage::ArrangementUnitSetup(EUnitJob Job , int Slot)
{
    JobID = Job;

    TArray<TObjectPtr<AUnit>>* UnitArray = nullptr;

    //  ロード済みユニットを選択
    switch (JobID)
    {
    case EUnitJob::EUJ_None:
    default:
    case EUnitJob::EUJ_Tank:
        UnitArray = &TankUnits;
        break;
    case EUnitJob::EUJ_Rounder:
        UnitArray = &RaunderUnits;
        break;
    case EUnitJob::EUJ_Magician:
        UnitArray = &MagicianUnits;
        break;
    case EUnitJob::EUJ_Healer:
        UnitArray = &HealerUnits;
        break;
    }


    TArray<TObjectPtr<AUnit>>& Units = *UnitArray;


    for (TArray<TObjectPtr<AUnit>>::TIterator It(Units); It; ++It)
    {
        TObjectPtr<AUnit>   Unit = *It;

        if (!Unit->IsVisible())
        {
            //  未使用ユニット
            SelectUnit = Unit;
            SelectUnit->SetVisible(true);
            break;
        }
    }

    if (!SelectUnit)
    {
        //  選択ユニットがない
        return;
    }


}




// ユニットがいない場所を検索して返す。(または、推奨される位置)
bool ARoleArrangementUnitStage::SearchEmptyPosition(int& X, int& Y) const
{
    static const struct
    {
        uint16 X, Y;
    }StartPositionPriorityTable[] =
    {
        {1,0},      //  前衛中心
        {0,0},      //  前衛右
        {2,0},      //  前衛左
        {1,1},      //  後衛中心
        {0,1},      //  後衛右
        {2,1},      //  後衛左
    };


    for (int i = 0 ; i < (sizeof(StartPositionPriorityTable) / sizeof(*StartPositionPriorityTable)); ++i)
    {
        int StartX = StartPositionPriorityTable[i].X;
        int StartY = StartPositionPriorityTable[i].Y;

        bool Tank = SearchEmptyPosition(StartX, StartY, TankUnits , SelectUnit);
        bool Raunder = SearchEmptyPosition(StartX, StartY, RaunderUnits, SelectUnit);
        bool Magician = SearchEmptyPosition(StartX, StartY, MagicianUnits, SelectUnit);
        bool Healer = SearchEmptyPosition(StartX, StartY, HealerUnits, SelectUnit);

        if (Tank && Raunder && Magician && Healer)
        {
            //  空いている
            X = StartX;
            Y = StartY;
            return true;
        }
    }

    return false;
}

//  カラの位置をチェック
bool ARoleArrangementUnitStage::SearchEmptyPosition(int X, int Y, const TArray<TObjectPtr<AUnit>>& Units, const TObjectPtr<AUnit>& SkipUnit) const
{

    for (TArray<TObjectPtr<AUnit>>::TConstIterator It(Units); It; ++It)
    {
        const TObjectPtr<AUnit>& Unit = *It;

        if (!Unit->IsVisible())
        {   //  表示されていないユニットは無視
            continue;
        }

        if (SkipUnit == Unit)
        {   //  判定をスキップユニットは無視
            continue;
        }
        if (Unit->GetUnitData().StartPosX == X && Unit->GetUnitData().StartPosY == Y)
        {
            //  任意の座標にユニットが存在
            return false;
        }
    }
    //  任意の座標だれもいない
    return true;
}



//  任意のスタート座標にいるユニットの検索
TObjectPtr<AUnit> ARoleArrangementUnitStage::SearchUnitFromPosition(int X, int Y)
{
    
    TObjectPtr<AUnit>   Unit;

    Unit = SearchUnitFromPosition(X, Y, TankUnits);
    if (Unit)return Unit;

    Unit = SearchUnitFromPosition(X, Y, RaunderUnits);
    if (Unit)return Unit;

    Unit = SearchUnitFromPosition(X, Y, MagicianUnits);
    if (Unit)return Unit;

    Unit = SearchUnitFromPosition(X, Y, HealerUnits);
    if (Unit)return Unit;

    return nullptr;
}

//  任意のスタート位置にいるユニットを返す
TObjectPtr<AUnit> ARoleArrangementUnitStage::SearchUnitFromPosition(int X, int Y, TArray<TObjectPtr<AUnit>>& Units)
{
    for (TArray<TObjectPtr<AUnit>>::TIterator It(Units); It; ++It)
    {
        TObjectPtr<AUnit>   Target = *It;
        FUnitData UnitData = Target->GetUnitData();
        if (Target->IsVisible() && UnitData.StartPosX == X && UnitData.StartPosY == Y)
        {
            return Target;
        }
    }
    return nullptr;
}


FVector ARoleArrangementUnitStage::CalcUnitLocation(int X, int Y) const
{
    FVector location;
    location.X = BATTLE_FILED_BLOCK_SIZE * X - (BATTLE_FILED_BLOCK_SIZE) ;
    location.Y = -BATTLE_FILED_BLOCK_SIZE * Y + (BATTLE_FILED_BLOCK_SIZE * 0.5f);
    location.Z = 0.0f;
    return location;
}

//  最後に配置したユニットのジョブを取得
EUnitJob ARoleArrangementUnitStage::GetLastArrangementUnitJob() const
{
    if (ResultUnitDatas.IsEmpty())
    {
        return JobID;
    }
    return ResultUnitDatas[ResultUnitDatas.Num() - 1].Job;
}


//  ユニット配置
void ARoleArrangementUnitStage::TickArrangementUnit(float DeltaTime, ABattleController* Controller)
{
    
    switch (StartPositionState)
    {
    case EAUState::EAUState_None:
    default:
        ;   //  何もしない
        break;
    case EAUState::EAUState_Begin:
        //  配置開始
    {
        FUnitData   UnitData;
        if (ResultUnitDatas.Num() > SlotNo)
        {   //  既に配置済み
            UnitData = ResultUnitDatas.Pop();
            UnitPosition.X = UnitData.StartPosX;
            UnitPosition.Y = UnitData.StartPosY;
            JobID = UnitData.Job;
            SelectUnit = SearchUnitFromPosition(UnitPosition.X, UnitPosition.Y);
            if (SelectUnit == nullptr)
            {   //  ここにいること自体エラー
                //  ワーニング
                UE_LOG(LogTemp, Warning, TEXT("SelectUnit が 見つからない"));
                break;
            }
        }
        else
        {
            SelectUnit = nullptr;
            //  最初に配置する座標を算出
            if (!SearchEmptyPosition(UnitPosition.X, UnitPosition.Y))
            {
                //  配置座標無し
                StartPositionState = EAUState::EAUState_None;
                UE_LOG(LogTemp, Warning, TEXT("配置の空きがない"));
                break;
            }
            TArray<TObjectPtr<AUnit>>* pUnits;

            switch (JobID)
            {
            case EUnitJob::EUJ_Tank:
            default:
                pUnits = &TankUnits;
                break;
            case EUnitJob::EUJ_Rounder:
                pUnits = &RaunderUnits;
                break;
            case EUnitJob::EUJ_Magician:
                pUnits = &MagicianUnits;
                break;
            case EUnitJob::EUJ_Healer:
                pUnits = &HealerUnits;
                break;
            }

            for (TArray<TObjectPtr<AUnit>>::TIterator It(*pUnits); It; ++It)
            {
                if (!(*It)->IsVisible())
                {
                    SelectUnit = **It;
                    break;
                }
            }
        }
        //  初期配置位置設定
        UnitData = SelectUnit->GetUnitData();
        UnitData.StartPosX = UnitPosition.X;
        UnitData.StartPosY = UnitPosition.Y;
        SelectUnit->SetUnitData(UnitData);
        FVector   location = CalcUnitLocation(UnitPosition.X, UnitPosition.Y);
        SelectUnit->Set3DLocation(location);
        SelectUnit->SetVisible(true);

        //  ポジションセレクト
        StartPositionState = EAUState::EAUState_SelectPosition;
        //  カーソルモデルも同じ座標に設定
        CursorModel->SetRelativeLocation(location);
        CursorModel->SetVisibility(true);
        NowTime = 1.0f;
    }

        break;
    case EAUState::EAUState_SelectPosition:
        NowTime = FMath::Min(NowTime + DeltaTime, MaxTime);
        if (NowTime >= MaxTime)
        {
            //  カーソル動かすタイミング
            FVector2D axis = Controller->GetLeftAxis();
            float AbsX = FMath::Abs(axis.X);
            float AbsY = FMath::Abs(axis.Y);

            if ((AbsX + AbsY) > 0.0f)
            {
                //  反応あり
                if (AbsX > AbsY)
                {
                    SelectUnit->SetVisible(false);
                    //  左右
                    if (axis.X > 0.0f)
                    {   //  手前
                        while (true)
                        {
                            ++UnitPosition.X;
                            if (UnitPosition.X >= ROLE_SELECT_WIDTH)
                            {
                                UnitPosition.X -= ROLE_SELECT_WIDTH;
                            }
                            //  移動先にユニットがいるか？
                            TObjectPtr<AUnit> Unit = SearchUnitFromPosition(UnitPosition.X, UnitPosition.Y);
                            if (Unit == nullptr)
                            {
                                break;
                            }
                        }
                    }
                    else
                    {   //  奥
                        while (true)
                        {
                            --UnitPosition.X;
                            if (UnitPosition.X < 0)
                            {
                                UnitPosition.X += ROLE_SELECT_WIDTH;
                            }
                            //  移動先にユニットがいるか？
                            TObjectPtr<AUnit> Unit = SearchUnitFromPosition(UnitPosition.X, UnitPosition.Y);
                            if (Unit == nullptr)
                            {
                                break;
                            }
                        }
                    }
                }
                else
                {
                    //  上下
                    if (axis.Y > 0.0f)
                    {
                        while (true)
                        {
                            ++UnitPosition.Y;
                            if (UnitPosition.Y >= ROLE_SELECT_DEPTH)
                            {
                                UnitPosition.Y -= ROLE_SELECT_DEPTH;
                            }
                            //  移動先にユニットがいるか？
                            TObjectPtr<AUnit> Unit = SearchUnitFromPosition(UnitPosition.X, UnitPosition.Y);
                            if (Unit == nullptr)
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        while (true)
                        {
                            --UnitPosition.Y;
                            if (UnitPosition.Y < 0)
                            {
                                UnitPosition.Y += ROLE_SELECT_DEPTH;
                            }
                            //  移動先にユニットがいるか？
                            TObjectPtr<AUnit> Unit = SearchUnitFromPosition(UnitPosition.X, UnitPosition.Y);
                            if (Unit == nullptr)
                            {
                                break;
                            }
                        }
                    }
                }
                SelectUnit->SetVisible(true);

                FVector location = CalcUnitLocation(UnitPosition.X, UnitPosition.Y);
                FUnitData   UnitData = SelectUnit->GetUnitData();
                UnitData.StartPosX = UnitPosition.X;
                UnitData.StartPosY = UnitPosition.Y;
                SelectUnit->SetUnitData(UnitData);
                SelectUnit->Set3DLocation(location);
                CursorModel->SetRelativeLocation(location);
                NowTime = 0.0f;
            }
            else
            {
                if (Controller->IsOkTrigger())
                {
                    //  任意の座標に配置
                    FUnitData   UnitData;
                    UnitData = SelectUnit->GetUnitData();
                    ResultUnitDatas.Add(UnitData);
                    if (ResultUnitDatas.Num() >= UNIT_ARRANGEMENT_NUM)
                    {
                        StartPositionState = EAUState::EAUState_ReadyWait;
                    }
                    else
                    {
                        StartPositionState = EAUState::EAUState_Selected;
                    }
                }
                else if (Controller->IsCanselTrigger())
                {
                    if (SelectUnit)
                    {
                        SelectUnit->SetVisible(false);
                        StartPositionState = EAUState::EAUState_SelectPositionCansel;
                    }
                }
            }

        }
        break;
    case EAUState::EAUState_Selected:   //  選択済み
        break;
    case EAUState::EAUState_ReadyWait:  //  確認待ち
        break;
    case EAUState::EAUState_Ready:      //  準備完了
        break;
    case EAUState::EAUState_SelectPositionCansel:
        //  配置キャンセル
        break;
    }
}

