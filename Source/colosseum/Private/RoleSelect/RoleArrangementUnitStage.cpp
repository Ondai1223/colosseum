// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleSelect/RoleArrangementUnitStage.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Battle/BattleCommon.h"
#include "RoleSelect/RoleSelectGameState.h"
#include "RoleSelect/RoleSelectHelper.h"
#include "Battle/BattleHelper.h"
#include "RoleSelect/RoleSelectPlayerState.h"


#define UNIT_ARRANGEMENT_NUM    3

#define CURSOR_NAME TEXT("Cursor")

// Sets default values
ARoleArrangementUnitStage::ARoleArrangementUnitStage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
#if 0
    USceneComponent* scene = CreateDefaultSubobject<USceneComponent>(TEXT("ArrangementUnitStage"));
    if (scene)
    {
        RootComponent = scene;
    }
#endif
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

                //CursorModel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
                CursorModel->SetRelativeLocation(CalcUnitLocation(UnitPosition.X, UnitPosition.Y));

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
        TObjectPtr<AUnit>   unit = GetWorld()->SpawnActor<AUnit>(AUnit::StaticClass());
        unit->SetUnitData(dmyUnit);
        unit->CreateUnitData();
        unit->SetVisible(false);
        unit->SetActorRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
        UnitArray.Add(unit);
        unit->GetRootComponent()->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

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
TObjectPtr<AUnit> ARoleArrangementUnitStage::SearchUnitFromPosition(int X, int Y, TArray<TObjectPtr<AUnit>>& Units , bool visible)
{
    for (TArray<TObjectPtr<AUnit>>::TIterator It(Units); It; ++It)
    {
        TObjectPtr<AUnit>   Target = *It;
        FUnitData UnitData = Target->GetUnitData();
        bool Visible = Target->IsVisible();
        bool flag = false;

        if (visible == false)
        {
            flag = !Visible;
        }
        else
        {
            flag = Visible == true && UnitData.StartPosX == X && UnitData.StartPosY == Y;
        }

        if (flag)
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
#if 1
    return location;
#else
    return FVector::ZeroVector;
#endif
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


void ARoleArrangementUnitStage::VisibleArrangementUnit()
{
    for (TArray<FUnitData>::TIterator It(ResultUnitDatas); It; ++It)
    {
        FUnitData& UnitData = *It;


        TArray<TObjectPtr<AUnit>>* Units = nullptr;

        switch (UnitData.Job)
        {
        case EUnitJob::EUJ_Tank:
            Units = &TankUnits;
            break;
        case EUnitJob::EUJ_Rounder:
            Units = &RaunderUnits;
            break;
        case EUnitJob::EUJ_Magician:
            Units = &MagicianUnits;
            break;
        case EUnitJob::EUJ_Healer:
            Units = &HealerUnits;
            break;
        default:
            continue;
        }
        TObjectPtr<AUnit> Unit = SearchUnitFromPosition(UnitData.StartPosX, UnitData.StartPosY, *Units,false);
        if (Unit)
        {
            Unit->SetUnitData(UnitData);
            Unit->SetVisible(true);
            FVector   location = CalcUnitLocation(UnitData.StartPosX, UnitData.StartPosY);
            Unit->Set3DLocation(location);
        }
    }
}


void ARoleArrangementUnitStage::ClearArrangementUnit(TArray<TObjectPtr<AUnit>>& Units)
{
    for ( TArray<TObjectPtr<AUnit>>::TIterator It(Units); It; ++It)
    {
        TObjectPtr<AUnit>   Unit = *It;
        Unit->SetVisible(false);
    }
}

void ARoleArrangementUnitStage::ClearArrangementUnit()
{
    ClearArrangementUnit(TankUnits);
    ClearArrangementUnit(RaunderUnits);
    ClearArrangementUnit(MagicianUnits);
    ClearArrangementUnit(HealerUnits);
}



//  ユニット配置
void ARoleArrangementUnitStage::TickArrangementUnit(float DeltaTime, ABattleController* Controller, ARoleSelectPlayerState* PlayerState)
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

        ClearArrangementUnit();
        VisibleArrangementUnit();

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
            SelectUnit = GetSelectUnit(JobID);
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

        PlayerState->SetReplicated_ArrangementStartPosX(UnitPosition.X);
        PlayerState->SetReplicated_ArrangementStartPosY(UnitPosition.Y);
        PlayerState->SetReplicated_ArrangementUnitState(EAUState::EAUState_SelectPosition);
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
                SelectUnit->SetVisible(false);
                if (AbsX > AbsY)
                {
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

                PlayerState->SetReplicated_ArrangementStartPosX(UnitPosition.X);
                PlayerState->SetReplicated_ArrangementStartPosY(UnitPosition.Y);
                PlayerState->SetReplicated_ArrangementUnitState(EAUState::EAUState_SelectPosition);

            }
            else
            {
                if (Controller->IsOkTrigger())
                {
                    //  任意の座標に配置
#if 0
                    FUnitData   UnitData;
                    UnitData = SelectUnit->GetUnitData();
                    ResultUnitDatas.Add(UnitData);
#endif
                    if ((ResultUnitDatas.Num() + 1) >= UNIT_ARRANGEMENT_NUM)
                    {
                        PlayerState->SendServerMessage(ARRANGEMENT_SYNC_READY_WAIT);
                        StartPositionState = EAUState::EAUState_ReadyWait;
                    }
                    else
                    {
                        PlayerState->SendServerMessage(ARRANGEMENT_SYNC_SELECTED);
                        StartPositionState = EAUState::EAUState_Selected;
                    }
                }
                else if (Controller->IsCanselTrigger())
                {
                    if (SelectUnit)
                    {
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
        if (PlayerState->GetServerMessage() == ARRANGEMENT_SYNC_CANSEL)
        {
            SelectUnit->SetVisible(false);
            break;
        }
        return;
    }
}


void ARoleArrangementUnitStage::CalcUnitPosition()
{
    FVector location = CalcUnitLocation(UnitPosition.X, UnitPosition.Y);

    if (SelectUnit)
    {
        SelectUnit->Set3DLocation(location);
    }
    if (CursorModel)
    {
        CursorModel->SetRelativeLocation(location);
    }
}

TObjectPtr<AUnit> ARoleArrangementUnitStage::GetSelectUnit(EUnitJob Job) const
{
    const TArray<TObjectPtr<AUnit>>* pUnits;
    switch(Job)
    {
    case EUnitJob::EUJ_Tank:
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
    default:
        return nullptr;
    }

    for (TArray<TObjectPtr<AUnit>>::TConstIterator It(*pUnits); It; ++It)
    {
        if ((*It)->IsVisible() == false)
        {
            return *It;
        }
    }


    return nullptr;
}

void ARoleArrangementUnitStage::BeginArrangementUnitStage()
{
    SelectUnit = GetSelectUnit(JobID);
    SelectUnit->SetVisible(true);
}

