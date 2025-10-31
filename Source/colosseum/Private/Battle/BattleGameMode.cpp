// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/BattleGameMode.h"
#include "EngineUtils.h"
#include "Camera/CameraActor.h"
#include "Unit/Unit.h"
#include "Battle/BattleTurn.h"
#include "Battle/BattleMain.h"
#include "Battle/BattleActionAttack.h"
#include "Battle/BattleTurnDecision.h"
#include "Battle/BattleHelper.h"
#include "Components/Widget.h"
#include "Unit/UnitTeamID.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "Sound/AmbientSound.h"
#include "Battle/BattleResult.h"
#include "Battle/BattleMainVsNpc.h"

#define IN_GAME_HP_GAUGE TEXT("WBP_InGame_Gauge_HP")
#define IN_GAME_MP_GAUGE TEXT("WBP_InGame_Gauge_MP")

#define BP_UNIT_PATH TEXT("/Game/Battle/Blueprints/BP_Unit.BP_Unit_C")  /// BP_Unit
#define BP_UNIT_BATTLE_PARAMETER    TEXT("/Game/Battle/Blueprints/BP_UnitBattleParameter.BP_UnitBattleParameter_C") // BP_UnitBattleParamter

#define UNIT_BATTLE_START_YAW_PLAYER1   -90.0f  //  スタート位置の角度(プレイヤー１）
#define UNIT_BATTLE_START_YAW_PLAYER2   90.0f   //  スタート位置の角度(プレイヤー２）


// コンストラクタ
ABattleGameMode::ABattleGameMode()
{
    // Set the default pawn class to your custom pawn class
    // DefaultPawnClass = AYourCustomPawn::StaticClass();
    CurrentBattleState = EBattleState::EBS_Waiting; // 初期状態は待機中
    bIsBeginState = true; // 初期状態フラグをオンにする
    CurrentBattleTurn = EBattleTurn::EBT_None;


}




// 最初に呼ばれるメソッド
void ABattleGameMode::BeginPlay()
{
    Super::BeginPlay();

}

// 毎フレーム呼ばれるメソッド
void ABattleGameMode::Tick(float DeltaSeconds)
{

    Super::Tick(DeltaSeconds);
}

void ABattleGameMode::SetupBattle()
{

    /**
     * インタフェースの設定
     */

     // 開始決定のインターフェースを設定

    SetInGameWidgetProxy(BattleGameStateBase->InGameWidgetProxy);

    TurnDecisionInterface = NewObject<ABattleTurnDecision>(this, TEXT("BattleTurnDecision")); // ダミーユニットの作成

    // ターン変更時のインタフェースを設定
    NextTurnInterface = NewObject<ABattleTurn>(this, TEXT("BattleTurn")); // ダミーユニットの作成

    //  戦闘結果表示処理
    BattleResultInterface = NewObject<ABattleResult>(this, TEXT("ABattleResult"));

    // 戦闘のインターフェースを設定
    ABattleMain* BpMain;
    
    switch (BattleGameModeType)
    {
    case EBattleGameMode::EBGM_Player_VS_NPC:
        BpMain = GetWorld()->SpawnActor<ABattleMainVsNpc>(ABattleMainVsNpc::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
        break;
    default:
        BpMain = GetWorld()->SpawnActor<ABattleMain>(ABattleMain::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
        break;
    }
    

    // MasoManagerインスタンス設定
    // ワールド内のMasoManagerを探し、メンバ変数に格納
    for (TActorIterator<AMasoManager> It(GetWorld()); It; ++It)
    {
        MasoManager = *It;
    }

    //  攻撃インタフェース
    BattleActionAttack = NewObject<UBattleActionAttack>(this, TEXT("UBattleActionAttack"));
    BpMain->BattleAttackInterface = BattleActionAttack;

    //  移動インタフェース
    BattleActionMove = NewObject<UBattleActionMove>(this, TEXT("UBattleActionMove"));
    BpMain->BattleMoveInterface = BattleActionMove;

    //  防御インタフェース
    BattleActionDiffence = NewObject<UBattleActionDiffence>(this, TEXT("UBattleActionDiffence"));
    BpMain->BattleDiffenceInterface = BattleActionDiffence;

    //  スキルインタフェース
    BattleActionSkill = NewObject<UBattleActionSkill>(this, TEXT("UBattleActionSkill"));
    BpMain->BattleSkillInterface = BattleActionSkill;


    BattleInterface = BpMain;
    BpMain->CreateCursorModel();
    BpMain->CursorModel->SetVisibility(false); // カーソルモデルを非表示にする

    BattleResultCheck = NewObject<UBattleResultCheck>(this, TEXT("UBattleResultCheck"));

    TArray<TObjectPtr<AUnit>>   BPUnit1Array;
    TArray<TObjectPtr<AUnit>>   BPUnit2Array;

    //  ユニットの作成
    CreateUnits(BPUnit1Array, Player1Units);
    CreateUnits(BPUnit2Array, Player2Units);

    InGameWidget = GetGameState<ABattleGameStateBase>()->InGameWidgetProxy;

    //  ユニットバトルパラメーターの作成
    CreateUnitBattleParameter(Player1UnitsActors, BPUnit1Array,this);
    CreateUnitBattleParameter(Player2UnitsActors, BPUnit2Array,this);

    BattleUnitsFiled->CreateUnitFiled();



    TObjectPtr<UPlayerNameWidget> Player1Name = InGameWidget->GetPlayerNameWidget(EUnitTeamID::EUTID_Team1);
    TObjectPtr<UPlayerNameWidget> Player2Name = InGameWidget->GetPlayerNameWidget(EUnitTeamID::EUTID_Team2);

    if (Player1Name)
    {
        Player1Name->PlayerName = Player1TeamName;
        Player1Name->ReflectionPlayerName();
    }
    if (Player2Name)
    {
        Player2Name->PlayerName = Player2TeamName;
        Player2Name->ReflectionPlayerName();
    }

    switch (GetNetMode())
    {
    case ENetMode::NM_ListenServer:
        {
            //  クライアントの転送
            // 
            
            //  クライアントの生成を指示
        }
        break;

    }



#if 0   //  ＢＧＭテスト
    TArray<TObjectPtr<AAmbientSound>>   ambsounds;
    for (TActorIterator<AAmbientSound> It(GetWorld()); It; ++It)
    {
        ambsounds.Add(*It);
        (*It)->Stop();
    }

#endif

}

int ABattleGameMode::CreateUnits(TArray<TObjectPtr<AUnit>>& output, const TArray<FUnitData>& UnitDataArray) const
{
    BattleHelper    helper;
    TSubclassOf<class AUnit> BPUnit = helper.Load<AUnit>(BP_UNIT_PATH);

    for (TArray<FUnitData>::TConstIterator Ite(UnitDataArray); Ite; ++Ite)
    {
        const FUnitData& UnitData = *Ite; // ユニットデータを取得
        FVector SpawnLocation = FVector::ZeroVector; // 開始位置を計算
        FRotator SpawnRotation = FRotator::ZeroRotator; // 回転はゼロに設定
        TObjectPtr<AUnit> NewUnit = GetWorld()->SpawnActor<AUnit>(BPUnit, SpawnLocation, SpawnRotation);

        if (NewUnit)
        {
            NewUnit->SetUnitData(*Ite);
            output.Add(NewUnit); // ユニットをリストに追加
        }
    }
    return UnitDataArray.Num();
}


int ABattleGameMode::CreateUnitBattleParameter(TArray<TObjectPtr<AUnitBattleParameter>>& output, const TArray<TObjectPtr<AUnit>>& Units , ABattleGameMode* GameMode) const
{

    BattleHelper    helper;
    TSubclassOf<class AUnitBattleParameter> BPUnitBattleParameter = helper.Load<AUnitBattleParameter>(BP_UNIT_BATTLE_PARAMETER);

    for (int i = 0; i < Units.Num(); ++i)
    {
        
        FVector SpawnLocation(0.0f,0.0f, 0.0f); // 開始位置を計算
        FRotator SpawnRotation = FRotator::ZeroRotator; // 回転はゼロに設定
        TObjectPtr<AUnitBattleParameter> NewBattleUnit = GetWorld()->SpawnActor<AUnitBattleParameter>(BPUnitBattleParameter, SpawnLocation, SpawnRotation);

        if (NewBattleUnit)
        {
            TObjectPtr<AUnit> Unit = Units[i];
            NewBattleUnit->SetGameMode(GameMode);
            NewBattleUnit->SetUnitData(Unit);
            output.Add(NewBattleUnit);


            NewBattleUnit->Set3DRotation(FRotator(0.0f, NewBattleUnit->GetTeamID() == EUnitTeamID::EUTID_Team1 ? UNIT_BATTLE_START_YAW_PLAYER1 : UNIT_BATTLE_START_YAW_PLAYER2, 0.0f));



            //  HPゲージなどの設定
            UBattleCharaStatusWidget* CharaStatusWidget = InGameWidget->GetPlayersStatus(NewBattleUnit->GetTeamID() , i);

            if (CharaStatusWidget == nullptr)
            {
                //  ゲージがあった。
                UE_LOG(LogTemp, Warning, TEXT("UBattleCharaStatusWidget not found!"));
            }
            else
            {
                CharaStatusWidget->SetUnitBattleParameter(NewBattleUnit);
                NewBattleUnit->SetBattleCharaStatusWidget(CharaStatusWidget);


                UBattleGauge* HpGauge = Cast<UBattleGauge>(CharaStatusWidget->GetWidgetFromName(IN_GAME_HP_GAUGE));
                UBattleGauge* MpGauge = Cast<UBattleGauge>(CharaStatusWidget->GetWidgetFromName(IN_GAME_MP_GAUGE));
                if (HpGauge == nullptr || MpGauge == nullptr)
                {
                    UE_LOG(LogTemp, Warning, TEXT("UBattleGauge not found!"));
                }
                else 
                {
                    CharaStatusWidget->SetHpGauge(HpGauge);
                    CharaStatusWidget->SetMpGauge(MpGauge);

                    NewBattleUnit->SetHpGaugeWidget(HpGauge);
                    NewBattleUnit->SetMpGaugeWidget(MpGauge);
                    CharaStatusWidget->BeginBattleStatus(); //  バトルステータスの開始
                }

            }


        }
    }

    return output.Num();

}







// ゲームモードの開始
void ABattleGameMode::BeginGameMode()
{
    UE_LOG(LogTemp, Warning, TEXT("BattleGameMode Begin!"));
    CreateDummyUnits(); // ダミーユニットの作成

    


}

// ゲームモードのTickイベント
void ABattleGameMode::TickGameMode(float DeltaSeconds)
{
    switch (CurrentBattleState)
    {
    case EBattleState::EBS_StartTurnDecision:   // ターン開始決定状態
        StartTurnDecision(DeltaSeconds);    // ターン開始の処理を呼び出す
        break;
    case EBattleState::EBS_Battle:  // 戦闘状態
        RunBattleState(DeltaSeconds); // 戦闘状態の処理を呼び出す
        break;
    case EBattleState::EBS_NextTurn:    //  次のターン移行処理
        RunNextTurnState(DeltaSeconds);
        break;
    case EBattleState::EBS_Result: //   結果表示状態
        RunResultState(DeltaSeconds); // 結果表示状態の処理を呼び出す
        break;
    case EBattleState::EBS_Waiting: // 待機中状態
        //  UE_LOG(LogTemp, Warning, TEXT("Wating called!"));
        break;
    case EBattleState::EBS_End:
        UE_LOG(LogTemp, Warning, TEXT("Go To Title!"));
        break;
    }
}


// ターン開始決定イベントの実装
void ABattleGameMode::BeginTurnDecision_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("BeginTurnDecision called!"));
    // ターン開始の決定処理をここに追加
    // 例えば、先制後攻の決定やターンの初期化など
    SetStartTurnDecisionState(EBattleTurn::EBT_Player1); // 最初はプレイヤー1のターンに設定
}

//  先制後攻の表示処理
void ABattleGameMode::TickTurnDecsision_Implementation(float DeltaSeconds)
{
    // ターン開始決定の処理をここに追加
    // 例えば、プレイヤーや敵の行動を決定するなど
    UE_LOG(LogTemp, Warning, TEXT("TickTurnDecsision called with DeltaSeconds: %f"), DeltaSeconds);

}


//  先制後攻の決定処理
void ABattleGameMode::BeginStartTurnDecision()
{

    if (TurnDecisionInterface)
    {
        TurnDecisionInterface->BeginTurnDecisionState(this); // インターフェースを通じて先制後攻の決定イベントを呼び出す
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("TurnDecisionInterface is not implemented!"));
    }

}

//  先制後攻の表示処理
//  trueで次の状態へ
//  falseで継続
bool ABattleGameMode::TickStartTurnDecision(float DeltaSeconds)
{

    if (TurnDecisionInterface)
    {
        bool Flag = TurnDecisionInterface->TickTurnDecisionState(this, DeltaSeconds); // インターフェースを通じて先制後攻の決定表示イベントを呼び出す
        return Flag;
    }

    UE_LOG(LogTemp, Warning, TEXT("TickTurnDecsision called with DeltaSeconds: %f"), DeltaSeconds);
    return false;

}



//  バトルステートの最初に呼ばれる
void ABattleGameMode::BeginRunBattleState()
{
    if (BattleInterface) {
        BattleInterface->BeginBattleState(this); // インターフェースを通じて戦闘開始イベントを呼び出す
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("BattleInterface is not implemented!"));
    }
}

//  バトルステートの実行
ETickBattleState ABattleGameMode::TickRunBattleState(float DeltaSeconds)
{
    if (BattleInterface) {
        ETickBattleState TickNext = BattleInterface->TickBattleState(this, DeltaSeconds); // インターフェースを通じて戦闘状態のTickイベントを呼び出す
        return TickNext;
    }
    UE_LOG(LogTemp, Warning, TEXT("BattleInterface is not implemented!"));
    //    return ETickBattleState::EBS_Tick;
    return ETickBattleState::EBS_TurnEnd;
}




//  結果表示イベントの開始
void ABattleGameMode::BeginRunResultState()
{
    if (BattleResultInterface) {
        BattleResultInterface->BeginResultState(this); // インターフェースを通じて結果表示イベントを呼び出す
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("BattleResultInterface is not implemented!"));
    }
}

//  結果表示状態の処理
bool ABattleGameMode::TickRunResultState(float DeltaSeconds)
{
    if (BattleResultInterface) {
        return BattleResultInterface->TickResultState(this, DeltaSeconds); // インターフェースを通じて結果表示のTickイベントを呼び出す
    }
    UE_LOG(LogTemp, Warning, TEXT("BattleResultInterface is not implemented!"));
    return false;
}

// 次のターン開始イベントの実装
void ABattleGameMode::BeginNextTurnState()
{
    if (NextTurnInterface)
    {
        NextTurnInterface->BeginNextTurnState(this); // インターフェースを通じて次のターン開始イベントを呼び出す
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("NextTurnInterface is not implemented!"));
    }
}

// 次のターンの状態を表示イベント
bool ABattleGameMode::TickNextTurnState(float DeltaSeconds)
{
    if (NextTurnInterface)
    {
        return NextTurnInterface->TickNextTurnState(this, DeltaSeconds); // インターフェースを通じて次のターン状態のTickイベントを呼び出す
    }
    UE_LOG(LogTemp, Warning, TEXT("NextTurnInterface is not implemented!"));
    return false;
}







// 戦闘状態を次の状態に遷移
void ABattleGameMode::NextBattleState()
{
    bIsBeginState = true; // 初期状態フラグをオンにする
    switch (CurrentBattleState)
    {
    case EBattleState::EBS_Waiting:
#if 1
        CurrentBattleState = EBattleState::EBS_StartTurnDecision; // 待機中からターン開始決定へ
#else
        CurrentBattleState = EBattleState::EBS_Waiting; // 待機中からターン開始決定へ
#endif
        break;
    case EBattleState::EBS_StartTurnDecision:
        CurrentBattleState = EBattleState::EBS_NextTurn; // ターン開始決定から戦闘へ
        break;
    case EBattleState::EBS_Battle:
        CurrentBattleState = EBattleState::EBS_Result; // 戦闘から結果表示へ
        break;
    case EBattleState::EBS_NextTurn:
        CurrentBattleState = EBattleState::EBS_Battle;  //  
        break;
    case EBattleState::EBS_Result:
        // 結果表示から待機中へ戻す
        CurrentBattleState = EBattleState::EBS_Waiting; // 終了から待機中へ戻す
        break;
    }
}

// 次のターンの決定
void ABattleGameMode::NextTurn()
{
    bIsBeginState = true; // 初期ターンフラグをオンにする
    CurrentBattleState = EBattleState::EBS_NextTurn;
    switch (CurrentBattleTurn)
    {
    case EBattleTurn::EBT_None:
        // ターンなしの処理
        CurrentBattleTurn = EBattleTurn::EBT_Player1; // 最初はプレイヤー1のターンにする
        break;
    case EBattleTurn::EBT_Player1:
        // プレイヤー1のターンの処理
        UE_LOG(LogTemp, Warning, TEXT("Next Player 2's turn!"));
        CurrentBattleTurn = EBattleTurn::EBT_Player2; // 次はプレイヤー2のターンにする
        break;
    case EBattleTurn::EBT_Player2:
        // プレイヤー2のターンの処理
        UE_LOG(LogTemp, Warning, TEXT("Next Player 1's turn!"));
        CurrentBattleTurn = EBattleTurn::EBT_Player1; // 次はプレイヤー1のターンにする
        break;
    }
    ++TurnCount;
}

// 戦闘結果の設定
void ABattleGameMode::SetBattleResult(EBattleResult Result)
{
    BattleResult = Result;
}

// 戦闘結果の取得
EBattleResult ABattleGameMode::GetBattleResult() const {
    return BattleResult;
}

//  現在のターン終了か
bool ABattleGameMode::IsNowTurnEnd() const
{
    const TArray<TObjectPtr<AUnitBattleParameter>>& BattleUnits = (CurrentBattleTurn == EBattleTurn::EBT_Player1) ? Player1UnitsActors : Player2UnitsActors;


    for (TArray<TObjectPtr<AUnitBattleParameter>>::TConstIterator Ite(BattleUnits); Ite; ++Ite)
    {
        if ((*Ite)->IsActionEnd() == false)
        {
            return false;
        }
    }
    return true;
}

//  すべてのアクション終了フラグをクリア
void ABattleGameMode::ClearActionEndFlag()
{
    for (TArray<TObjectPtr<AUnitBattleParameter>>::TIterator Ite(Player1UnitsActors); Ite; ++Ite)
    {
        (*Ite)->ClearAction();
        (*Ite)->GetBattleCharaStatusWidget()->ChangeEndAction();
    }
    for (TArray<TObjectPtr<AUnitBattleParameter>>::TIterator Ite(Player2UnitsActors); Ite; ++Ite)
    {
        (*Ite)->ClearAction();
        (*Ite)->GetBattleCharaStatusWidget()->ChangeEndAction();
    }

}

//  現在のチームの防御フラグをクリア
void ABattleGameMode::ClearDiffenceNowTeam()
{
    if (GetCurrentBattleTurn() == EBattleTurn::EBT_Player1)
    {
        for (TArray<TObjectPtr<AUnitBattleParameter>>::TIterator Ite(Player1UnitsActors); Ite; ++Ite)
        {
            (*Ite)->ClearActionDiffence();
        }
    }
    else
    {
        for (TArray<TObjectPtr<AUnitBattleParameter>>::TIterator Ite(Player2UnitsActors); Ite; ++Ite)
        {
            (*Ite)->ClearActionDiffence();
        }
    }
}


//  ユニットの検索(nullptrで何もない)
TObjectPtr<AUnitBattleParameter> ABattleGameMode::GetUnit(uint8 GameX, uint8 GameY)
{
    TObjectPtr<AUnitBattleParameter>   Unit;
    Unit = GetUnit(Player1UnitsActors, GameX, GameY);
    if (Unit) {
        return Unit;
    }
    Unit = GetUnit(Player2UnitsActors, GameX, GameY);
    return Unit;
}

TObjectPtr<AUnitBattleParameter> ABattleGameMode::GetUnit(TArray<TObjectPtr<AUnitBattleParameter>>& UnitActorArray, uint8 GameX, uint8 GameY) const
{
    for (TArray<TObjectPtr<AUnitBattleParameter>>::TIterator Ite(UnitActorArray); Ite; ++Ite) {
        if ((*Ite)->GetGameX() == GameX && (*Ite)->GetGameY() == GameY && (*Ite)->IsDead() == false) {
            return *Ite;
        }
    }
    TObjectPtr<AUnitBattleParameter> NullData;
    return NullData;;
}


int ABattleGameMode::GetUnitIndex(TArray<TObjectPtr<AUnitBattleParameter>>& UnitActorArray,const TObjectPtr<AUnitBattleParameter>& SelectUnit) const
{
    for ( int Index = 0 ; Index < UnitActorArray.Num() ; ++Index)
    {
        if (UnitActorArray[Index] == SelectUnit)
        {
            return Index;
        }
    }
    return -1;
}

void ABattleGameMode::SelectUnitStatus(TObjectPtr<AUnitBattleParameter>& SelectUnit)
{
    if (SelectUnit == nullptr)
    {
        CanselWithOutUnitStatus(nullptr);
        return;
    }

    SelectUnit->GetBattleCharaStatusWidget()->SelectBattleStatus();

}

void ABattleGameMode::CanselUnitStatus(const TObjectPtr<AUnitBattleParameter>& SelectUnit)
{
    if (SelectUnit)
    {
        SelectUnit->GetBattleCharaStatusWidget()->CanselBattleStatus();
    }
}

void ABattleGameMode::CanselWithOutUnitSatus(TArray<TObjectPtr<AUnitBattleParameter>>& Units, const TObjectPtr<AUnitBattleParameter>& SelectUnit) const
{
    for (TArray<TObjectPtr<AUnitBattleParameter>>::TIterator Ite(Units); Ite; ++Ite)
    {
        if (*Ite != SelectUnit)
        {
            (*Ite)->GetBattleCharaStatusWidget()->CanselBattleStatus();
        }
    }
}


void ABattleGameMode::CanselWithOutUnitStatus(const TObjectPtr<AUnitBattleParameter>& SelectUnit)
{
    CanselWithOutUnitSatus(Player1UnitsActors, SelectUnit);
    CanselWithOutUnitSatus(Player2UnitsActors, SelectUnit);
}

void ABattleGameMode::ReflectionStatus(const TObjectPtr<AUnitBattleParameter>& Unit) const
{
    if (Unit)
    {
        Unit->GetBattleCharaStatusWidget()->ReflectBattleStatus();
    }
}

void ABattleGameMode::ReflectionStatus(const TArray<TObjectPtr<AUnitBattleParameter>>& Units) const
{
    for (TArray<TObjectPtr<AUnitBattleParameter>>::TConstIterator Ite(Units); Ite; ++Ite)
    {
        ReflectionStatus(*Ite);
    }
}

void ABattleGameMode::ReflectionStatus() const
{
    ReflectionStatus(Player1UnitsActors);
    ReflectionStatus(Player2UnitsActors);
}


//  戦闘結果のチェック
void ABattleGameMode::CheckBattleResult()
{
    if (BattleResultCheck)
    {
        BattleResultCheck->CheckBattleResult(this);
    }
}



// バトル開始時の先制後攻の決定
void ABattleGameMode::StartTurnDecision(float DeltaSeconds)
{
    if (bIsBeginState) {
        // 初期状態の処理
        UE_LOG(LogTemp, Warning, TEXT("先制後攻の決定処理開始"));
        bIsBeginState = false; // 初期状態フラグをオフにする
        BeginTurnDecision(); // 先制後攻の決定イベント
    }

    TickTurnDecsision(DeltaSeconds); // 先制後攻の決定演出
}

// ターン開始決定状態の処理
void ABattleGameMode::SetStartTurnDecisionState(EBattleTurn Turn)
{
    CurrentBattleTurn = Turn; // 現在のバトルターンを設定
}


FVector ABattleGameMode::GetBattleCursorLocation(int X, int Y) const
{
    FVector Position; // 戦闘フィールド上の位置を格納する変数
    BattleHelper    helper;
    Position = helper.CalcPanelLocation(X, Y);
    return Position;
}



void ABattleGameMode::SetInGameWidgetProxy(UBattleInGameWidgetProxy* WidgetProxy)
{
    InGameWidget = WidgetProxy;
}


void ABattleGameMode::SetBattleCameraFromBP(ACameraActor* Camera)
{
    BattleCamera = Camera;
}


bool ABattleGameMode::IsPlayer1AllDead() const
{
    return IsAllDead(Player1UnitsActors);
}

bool ABattleGameMode::IsPlayer2AllDead() const
{
    return IsAllDead(Player2UnitsActors);

}
/*
void ABattleGameMode::RequestUpdate(struct FBattleCommunication const& InfoCom)
{
    if (BattleGameStateBase)
    {
        BattleGameStateBase->OnRep_CommunicationData();
    }

}
*/

bool ABattleGameMode::IsAllDead(const TArray<TObjectPtr<AUnitBattleParameter>>& Units) const
{
    for ( TArray<TObjectPtr<AUnitBattleParameter>>::TConstIterator Ite(Units); Ite; ++Ite)
    {
        if ((*Ite)->IsDead() == false)
        {
            //  まだ生きているユニットがいる
            return false;
        }
    }
    //  全員死亡している
    return true;
}



// 戦闘開始イベントの実装
void ABattleGameMode::BeginBattle_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("バトルの初期化"));
}

// 戦闘状態のTickイベントの実装
void ABattleGameMode::TickBattle_Implementation(float DeltaSeconds)
{
    UE_LOG(LogTemp, Warning, TEXT("TickBattle called with DeltaSeconds: %f"), DeltaSeconds);
}


// 次のターンへ移行イベントの実装
void ABattleGameMode::BeginNextTurn_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("次のターンへ移行開始"));
}


void ABattleGameMode::TickNextTurn_Implementation(float DeltaSeconds)
{
    UE_LOG(LogTemp, Warning, TEXT("TickNextTurn called with DeltaSeconds: %f"), DeltaSeconds);
}







// 戦闘状態の処理
void ABattleGameMode::RunBattleState(float DeltaSeconds)
{
    if (bIsBeginState) {
        // 初期状態の処理
        UE_LOG(LogTemp, Warning, TEXT("戦闘の開始"));
        bIsBeginState = false; // 初期状態フラグをオフにする
        BeginBattle(); // 戦闘開始イベント
    }
    TickBattle(DeltaSeconds); // 戦闘状態のTickイベント
}

//  結果表示イベントの開始
void ABattleGameMode::BeginResult_Implementation()
{
}
// 結果表示イベントの開始
void ABattleGameMode::TickResult_Implementation(float DeltaSeconds)
{
    UE_LOG(LogTemp, Warning, TEXT("TickResult called with DeltaSeconds: %f"), DeltaSeconds);
}

void ABattleGameMode::BeginPlayLevelBuleprint_Implementation()
{
}

void ABattleGameMode::BeginBattleGameMode()
{
    BeginPlayLevelBuleprint();
}



// 結果表示状態の処理
void ABattleGameMode::RunResultState(float DeltaSeconds)
{
    if (bIsBeginState) {
        // 初期状態の処理
        UE_LOG(LogTemp, Warning, TEXT("BeginResultEvent"));
        bIsBeginState = false; // 初期状態フラグをオフにする
        BeginResult(); // 結果表示イベント
    }
    TickResult(DeltaSeconds); // 結果表示のTickイベント
}


//  次のターン実行処理
void ABattleGameMode::RunNextTurnState(float DeltaSeconds)
{
    if (bIsBeginState) {
        //  次のターン開始
        UE_LOG(LogTemp, Warning, TEXT("BeginNextTurn"));
        bIsBeginState = false;
        BeginNextTurn();
    }
    //  次のターン表示処理
    TickNextTurn(DeltaSeconds);
}




// ダミーユニットの作成
#ifdef UNITDATA_DUMMY
void ABattleGameMode::CreateDummyUnits()
{
    TArray<FUnitData>& UnitList = Player1Units; // ユニットのリストを生成
    // テスト用

    FUnitData UnitData; // ユニットデータの生成
    UnitData.TeamID = EUnitTeamID::EUTID_Team1; // ユニットのチームIDを設定
    UnitData.Job = EUnitJob::EUJ_Tank; // ユニットのジョブをタンクに設定
    UnitData.StartPosX = 0;
    UnitData.StartPosY = 0;
    UnitList.Add(UnitData); // ユニットをリストに追加

    UnitData.Job = EUnitJob::EUJ_Rounder; // ユニットのジョブをタンクに設定
    UnitData.StartPosX = 2;
    UnitData.StartPosY = 0;
    UnitList.Add(UnitData); // ユニットをリストに追加

    UnitData.Job = EUnitJob::EUJ_Rounder; // ユニットのジョブをタンクに設定
    UnitData.StartPosX = 1;
    UnitData.StartPosY = 1;
    UnitData.Job = EUnitJob::EUJ_Magician; // ユニットのジョブをタンクに設定
    UnitList.Add(UnitData); // ユニットをリストに追加


    UnitData = FUnitData(); // ユニットデータの生成
    TArray<FUnitData>& UnitList2 = Player2Units; // ユニットのリストを生成

    UnitData.Job = EUnitJob::EUJ_Tank; // ユニットのジョブをタンクに設定
    UnitData.TeamID = EUnitTeamID::EUTID_Team2; // ユニットのチームIDを設定
    UnitData.StartPosX = 1;
    UnitData.StartPosY = 0;
    UnitList2.Add(UnitData); // ユニットをリストに追加

    UnitData.Job = EUnitJob::EUJ_Rounder; // ユニットのジョブをタンクに設定
    UnitData.StartPosX = 2;
    UnitData.StartPosY = 0;
    UnitList2.Add(UnitData); // ユニットをリストに追加

    UnitData.Job = EUnitJob::EUJ_Healer; // ユニットのジョブをタンクに設定
    UnitData.StartPosX = 1;
    UnitData.StartPosY = 1;
    UnitList2.Add(UnitData); // ユニットをリストに追加

}
#endif

// 指定座標にカメラを向ける
void ABattleGameMode::SetLookAtBattleCamera(const FVector& LookAtLocation)
{
    if (BattleCamera)
    {
        FVector CameraLocation = BattleCamera->GetActorLocation();
        FVector LookAtDirection = LookAtLocation - CameraLocation;
        LookAtDirection.Normalize();
        FRotator CameraRotation = LookAtDirection.Rotation();
        BattleCamera->SetActorRotation(CameraRotation);
        BattleCameraLookAtLocation = LookAtLocation;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("BattleCamera is not set!"));
    }
}

// 視点の移動
void ABattleGameMode::SetEyeBattleCamera(const FVector& EyeLocation)
{
    if (BattleCamera)
    {
        BattleCameraEyeLocation = EyeLocation; // 視点の位置を保存
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("BattleCamera is not set!"));
    }
}

void ABattleGameMode::SetZoomBattleCamera(float zoom)
{
    if (BattleCamera)
    {
        BattleCameraZoom = zoom; // ズーム値を保存
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("BattleCamera is not set!"));
    }
}

void ABattleGameMode::CalcBattleCamera()
{
    if (BattleCamera)
    {
        FVector BattleCameraVector = BattleCameraLookAtLocation - BattleCameraEyeLocation;
        FVector NewLocation = BattleCameraVector * BattleCameraZoom + BattleCameraEyeLocation;

        BattleCameraVector.Normalize();
        FRotator NewRotation = BattleCameraVector.Rotation();

        BattleCamera->SetActorLocation(NewLocation);
        BattleCamera->SetActorRotation(NewRotation);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("BattleCamera is not set!"));
    }
}
