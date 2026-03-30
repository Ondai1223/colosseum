// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleSelect/RoleSelectPlayerState.h"
#include "Engine/World.h"
#include "GameFramework/GameStateBase.h"
#include "RoleSelect/RoleSelecter.h"
#include "RoleSelect/RoleSelectGameState.h"
/**
 *  プレーヤーロール選択ステート
 */

#define ROLESELECT_RUN_COMMAND_DATA_NUM 2   //  コマンドを実行するのに必要な要数

#define SEND_SLEEP_TIME (1.0f)

#ifdef FRAME_DO_CONCE_CHECKER

#define DO_ONCE_COUNTER_MAX (1)
#define DO_CONE_CHEKER(CheckerCounter)  ensure((CheckerCounter) < DO_ONCE_COUNTER_MAX);++(CheckerCounter)
#define DO_ONCE_COUNTER_CLEAR(CheckerCounter) (CheckerCounter) = 0

#else

#define DO_ONCE_COUNTER_MAX 
#define DO_CONE_CHEKER(CheckerCounter)
#define DO_ONCE_COUNTER_CLEAR(CheckerCounter)

#endif // FRAME_DO_CONCE_CHECKER



ARoleSelectPlayerState::ARoleSelectPlayerState()
{
    bReplicates = true;
}

void ARoleSelectPlayerState::SetOnlyRelevantToOwner(bool flag)
{
    bOnlyRelevantToOwner = flag;
}


//  ネゴシエーションメッセージの同期
//void ARoleSelectPlayerState::SyncNegotiationMessage_Implementation(const FString& Message)
//{
//    ;
//}


//  プレイヤー番号の取得
int ARoleSelectPlayerState::GetPlayerNo() const
{
    UWorld* World = GetWorld();
    if (World)
    {
        TArray<TObjectPtr<APlayerState>>& PlayerArray = World->GetGameState()->PlayerArray;

        for (TArray<TObjectPtr<APlayerState>>::TConstIterator It(PlayerArray); It; ++It)
        {
            TObjectPtr<APlayerState> pps = *It;
            ARoleSelectPlayerState* rps = Cast<ARoleSelectPlayerState>(pps.Get());
            if (rps == this)
            {
                return It.GetIndex();
            }
        }
    }
    return -1;
}


//  文字列比較
bool ARoleSelectPlayerState::CompereString(const FString& StrLeft, const FString& StrRight) const
{
    return StrLeft == StrRight;
}


//  サーバーにメッセージを送る
void ARoleSelectPlayerState::SendServerMessage(const FString& Message)
{
    IsSyncServerString = false;
    SyncServerString = Message;
}

bool ARoleSelectPlayerState::IsSyncServerMessage(const FString& Message) const
{
    return SyncServerString == Message;
}


void ARoleSelectPlayerState::TickProc(URoleSelectPage* page, float DT)
{

    DO_ONCE_COUNTER_CLEAR(DoOnceSlotState);
    DO_ONCE_COUNTER_CLEAR(DoOnceSlotSelectIndex);
    DO_ONCE_COUNTER_CLEAR(DoOnceSlotGetReady);

    DO_ONCE_COUNTER_CLEAR(DoOnceRoleSelectState);
    DO_ONCE_COUNTER_CLEAR(DoOnceRoleSelectIndex);
    DO_ONCE_COUNTER_CLEAR(DoOnceRoleSelectJob);
    DO_ONCE_COUNTER_CLEAR(DoOnceRoleSelectJobBefore);

    DO_ONCE_COUNTER_CLEAR(DoOnceRoleSelectTime);
    DO_ONCE_COUNTER_CLEAR(DoOnceRoleSelectTimeMax);

    DO_ONCE_COUNTER_CLEAR(DoOnceArrangementUnitState);
    DO_ONCE_COUNTER_CLEAR(DoOnceArrangementStartPosX);
    DO_ONCE_COUNTER_CLEAR(DoOnceArrangementStartPosY);

    if (!page)
    {
        return;
    }

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    ARoleSelectGameState* rsgs = Cast<ARoleSelectGameState>(World->GetGameState());
    ABattleController* BattleController = GetPlayerBattleController();

    bool Server = true;

    switch (rsgs->GameMode)
    {
    case EBattleGameMode::EBGM_Player_VS_Player:
    case EBattleGameMode::EBGM_Player_VS_NPC:
        Server = true;
        break;
    case EBattleGameMode::EBGM_Player_VS_NET:
        Server = HasAuthority();
        if (Server == false)
        {
            BattleController = nullptr;
        }
        break;
    }

    if (BattleController)
    {   //  コントローラーが存在する場合は、コントローラーの処理を行う。
        page->TickSlotProc(this, BattleController, DT);
        RoleSelectStateDataFIFO.Empty();
        RoleSelectStateDataFIFOBuffer.Empty();
    }
    else if (RoleSelectStateDataFIFO.IsEmpty() == false || RoleSelectStateDataFIFOBuffer.IsEmpty() == false || NowDataState.IsStayApply == true)
    {
        ClientSlotRun = true;
        RoleSelectStateDataFIFO += (RoleSelectStateDataFIFOBuffer);
        RoleSelectStateDataFIFOBuffer.Empty();

        if (rsgs->GameMode == EBattleGameMode::EBGM_Player_VS_NET && RoleSelectStateDataFIFO.IsEmpty() == false)
        {

#if 0
            if (RoleSelectStateDataFIFO.IsEmpty() == false && RoleSelectStateDataFIFO[0].DataType == ERoleSelectDataType::ERSDT_Nagosiation)
            {
                //通信対戦で同期をとるための処理
                //  サーバーは配置の状態をクライアントに送るだけ
                if (SyncServerString.IsEmpty() == false)
                {
                    if (IsSyncServerMessage(RoleSelectStateDataFIFO[0].SyncServerString))
                    {
                        //  同期がとれていない、クライアントからの返答を待つ
                        return;
                    }
                    SyncServerString.Empty();
                    IsSyncServerString = false;
                    RoleSelectStateDataFIFO.RemoveAt(0);
                }
            }
#endif
        }

        TickNewWorkProc(page, DT);
        ClientSlotRun = false;;
    }
}

void ARoleSelectPlayerState::TickNewWorkProc(URoleSelectPage * page, float DT)
{
    //  クライアントは通信で状況変化したときのために処理を行う。
    //  スロットの状態が変化したときの処理
    page->TickSlotNetWorkProc(this, DT);





#if 0
        DataState = RoleSelectStateDataFIFO[0];
        switch (DataState.DataType)
        {
        case ERoleSelectDataType::ERSDT_None:
            return;
        case ERoleSelectDataType::ERSDT_Nagosiation:
            //  ネゴシエーション
            if (IsSyncServerMessage(DataState.SyncServerString))
            {
                //  同じ文字列、同期がとれたのでつぎへ
                break;
            }
            return;
        case ERoleSelectDataType::ERSDT_SlotState:
            switch (DataState.SlotState)
            {
            case ERpoleSelectSlotState::ERSSS_None:
                if (RoleSelectStateDataFIFO.Num() >= 2)
                {
                    break;
                }
                return;
            case ERpoleSelectSlotState::ERSSS_SelectingNext:
                page->SelectedJob = page->GetRoleSelectFromCursorIndex();
                page->SetRoleNameInfoFromJobID(page->GetRoleSelectFromCursorIndex());
                page->ClearRoleSelectArrow();
                page->SetRoleSelectArrow();
                break;
            case ERpoleSelectSlotState::ERSSS_SelectingAnim:
                page->RoleSelectIndex = RoleSelectIndex = RoleSelectIndex;
                page->RoleSelecter->NowTime = RoleSelectTime;
                page->SelecteBeforedJob = RoleSelectJobBefore;
                page->SelectedJob = RoleSelectJob;
                page->CalcRoleLoop();
                if (page->RoleSelecter->IsEnd())
                {
                    page->ClearRoleSelectArrow();
                    page->SetRoleSelectArrow();
                    page->SetRoleNameInfoFromJobID(page->GetRoleSelectFromCursorIndex());
                    break;
                }
                return;
            case ERpoleSelectSlotState::ERSSS_Selecting:
                if (RoleSelectStateDataFIFO.Num() >= 2)
                {
                    page->ChangeState_Selecting(this, true);
                    break;
                }
                return;
            case ERpoleSelectSlotState::ERSSS_Arrangement:
                return;
            case ERpoleSelectSlotState::ERRSS_ArrangementCansel:
                return;
            case ERpoleSelectSlotState::ERRSS_CheckReady:
                return;
            case ERpoleSelectSlotState::ERRSS_Ready:
                return;

            }
            break;
        case ERoleSelectDataType::ERSDT_SlotSelectIndex:
            page->SetSlotIndex(DataState.SlotSelectIndex);
            break;
        case ERoleSelectDataType::ERSDT_GetReady:
            return;
        case ERoleSelectDataType::ERSDT_RoleSelectState:
            switch (DataState.RoleSelectState)
            {
            case ERoleSelectState::ERS_None:
                break;
            case ERoleSelectState::ERS_RoleSelect:
                break;
            case ERoleSelectState::ERS_Arrangement:
                break;
            }
            break;


        case ERoleSelectDataType::ERSDT_RoleSelectIndex:
            page->RoleSelectIndex = DataState.RoleSelectIndex;
            page->SetRoleNameInfoFromJobID(page->GetRoleSelectFromCursorIndex());
            page->ClearRoleSelectArrow();
            page->SetRoleSelectArrow();
            break;
        case ERoleSelectDataType::ERSDT_RoleSelectJob:
            page->SelectedJob = DataState.RoleSelectJob;
            break;
        case ERoleSelectDataType::ERSDT_RoleSelectJobBefore:
            page->SelecteBeforedJob = DataState.RoleSelectJobBefore;
            break;
        case ERoleSelectDataType::ERSDT_RoleSelectTime:
            page->RoleSelecter->NowTime = DataState.RoleSelectTime;
            break;
        case ERoleSelectDataType::ERSDT_RoleSelectTimeMax:
            page->RoleSelecter->MaxTime = DataState.RoleSelectTimeMax;
            break;
        case ERoleSelectDataType::ERSDT_ArrangementState:
            return;
        case ERoleSelectDataType::ERSDT_ArrangementStartX:
            return;
        case ERoleSelectDataType::ERSDT_ArrangementStartY:
            return;
        }

        //  ここに着たら次のコマンドを実行する
        RoleSelectStateDataFIFO.RemoveAt(0);
    }
    if (IsSlotStateFIFOEmpty())
    {
        return;
    }

    do
    {
        switch (GetBeforeSlotState())
        {
        case ERpoleSelectSlotState::ERSSS_None:
            //  前回の処理がスロットが空から選択状態になったときの処理
            if (ERpoleSelectSlotState::ERSSS_None != SlotState)
            {
                switch (SlotState)
                {
                case ERpoleSelectSlotState::ERSSS_Selecting:
                    //  ロール選択へ
                    page->ChangeState_Selecting(this);
                    RemoveSlotStateFIFO();
                    break;
                case ERpoleSelectSlotState::ERSSS_Arrangement:
                    //  配置へ
                    page->ChangeState_BeforeSlot(this);
                    RemoveSlotStateFIFO();
                    break;
                }
            }
            return;
        case ERpoleSelectSlotState::ERSSS_Selecting:
            page->RoleSelecter->NowTime = RoleSelectTime;
            page->RoleSelecter->MaxTime = RoleSelectTimeMax;

            page->SelecteBeforedJob = SelecteBeforedJob;;
            page->SelectedJob = SelectedJob;
            page->RoleSelectIndex = RoleSelectIndex;
            page->CalcRoleLoop();


            if (page->RoleSelecter->IsEnd())
            {
                page->ClearRoleSelectArrow();
                page->SetRoleSelectArrow();
                page->SetRoleNameInfoFromJobID(page->GetRoleSelectFromCursorIndex());
            }
            if (ERpoleSelectSlotState::ERSSS_Selecting != SlotState)
            {
                switch (SlotState)
                {
                case ERpoleSelectSlotState::ERSSS_None:
                    //  戻る
                    page->ChangeState_RoleSelectingToNone(this);
                    RemoveSlotStateFIFO();
                    break;
                case ERpoleSelectSlotState::ERSSS_Arrangement:
                    //  配置へ
                    page->ArrangementSetup();
                    RemoveSlotStateFIFO();
                    break;
                }
            }
            return;
        case ERpoleSelectSlotState::ERSSS_Arrangement:
            //  ユニット配置
            if (page->RoleArrangementUnitStage)
            {
                page->RoleArrangementUnitStage->UnitPosition.X = StartPostionX;
                page->RoleArrangementUnitStage->UnitPosition.Y = StartPostionY;

                FVector pos = page->RoleArrangementUnitStage->CalcUnitLocation(StartPostionX, StartPostionY);
                if (page->RoleArrangementUnitStage->SelectUnit)
                {
                    page->RoleArrangementUnitStage->SelectUnit->Set3DLocation(pos);
                    page->RoleArrangementUnitStage->CursorModel->SetRelativeLocation(pos);
                }

                page->RoleArrangementUnitStage->StartPositionState = StartPositionState;

                switch (page->RoleArrangementUnitStage->StartPositionState)
                {
                case EAUState::EAUState_SelectPosition:
                    if (GetServerMessage() == ARRANGEMENT_SYNC_READY_WAIT)
                    {
                        StartPositionState = page->RoleArrangementUnitStage->StartPositionState = EAUState::EAUState_ReadyWait;
                    }
                    else if (GetServerMessage() == ARRANGEMENT_SYNC_SELECTED)
                    {
                        StartPositionState = page->RoleArrangementUnitStage->StartPositionState = EAUState::EAUState_Selected;
                    }
                    break;
                case EAUState::EAUState_Selected:
                    //  選択したので終了待ち
                    page->ChangeState_PositionSet(this);
                    page->RoleArrangementUnitStage->ResultUnitDatas.Add(page->RoleArrangementUnitStage->SelectUnit->GetUnitData());
                    RemoveSlotStateFIFO();
                    break;
                case EAUState::EAUState_ReadyWait:
                    page->ChangeState_ReadyWait(this);
                    page->RoleArrangementUnitStage->ResultUnitDatas.Add(page->RoleArrangementUnitStage->SelectUnit->GetUnitData());
                    RemoveSlotStateFIFO();
                    break;
                case EAUState::EAUState_Ready:
                    page->ChangeState_ReadyWait(this);
                    break;
                case EAUState::EAUState_SelectPositionCansel:
                    if (GetServerMessage() == ARRANGEMENT_SYNC_CANSEL)
                    {
                        page->ChangeState_SelectPositionCansel(this);
                        RemoveSlotStateFIFO();
                        return;
                    }
                    break;
                }

            }
            return;
        case ERpoleSelectSlotState::ERRSS_ArrangementCansel:
            if (page->RoleArrangementUnitStage)
            {
                if (page->RoleArrangementUnitStage->StartPositionState == EAUState::EAUState_SelectPositionCansel)
                {
                    page->ChangeState_ArrangementCansel(this);
                    RemoveSlotStateFIFO();
                    break;
                }
            }
            return;
        case ERpoleSelectSlotState::ERRSS_CheckReady:
            if (page->RoleArrangementUnitStage)
            {
                if (GetServerMessage() == ARRANGEMENT_SYNC_READY_CANCEL)
                {
                    page->ChangeState_ReadyCansel(this);
                    RemoveSlotStateFIFO();
                    break;
                }
                if (GetServerMessage() == ARRANGEMENT_SYNC_READY)
                {
                    page->GetReady();
                    RemoveSlotStateFIFO();
                    break;
                }
            }
            return;

        }
    } while (IsSlotStateFIFOEmpty() == false);
#endif
}

bool ARoleSelectPlayerState::IsRunCommand() const
{
    return RoleSelectStateDataFIFO.Num() >= ROLESELECT_RUN_COMMAND_DATA_NUM;
}

FRoleSelectStateData ARoleSelectPlayerState::GetLastCommand() const
{
    FRoleSelectStateData    Data;
    if (RoleSelectStateDataFIFOBuffer.IsEmpty() == false)
    {
        Data = RoleSelectStateDataFIFOBuffer.Last();
    }
    else if (RoleSelectStateDataFIFO.IsEmpty())
    {
        FRoleSelectStateData    DefaultData;
        Data = DefaultData;
    }
    else
    {
        Data = RoleSelectStateDataFIFO.Last();
    }
    Data.IsStayApply = false;
    return Data;
}



ABattleController* ARoleSelectPlayerState::GetPlayerBattleController() const
{
#if 0
    if (ABattleController* PC = Cast<ABattleController>(GetPlayerController())) {
        return PC;
    }
#endif

    if (auto Pawn = GetPawn()) {
        if (auto PC = Cast<ABattleController>(Pawn->GetController())) {
            return PC;
        }
    }
    return nullptr;
}


void ARoleSelectPlayerState::AddCommand(const FRoleSelectStateData& DataState)
{
    //  コールIDを設定する
    if (ClientSlotRun)
    {
        //  クライアント処理実行中
        RoleSelectStateDataFIFOBuffer.Add(DataState);
    }
    else
    {
        //  通常
        RoleSelectStateDataFIFO += RoleSelectStateDataFIFOBuffer;
        RoleSelectStateDataFIFO.Add(DataState);
        RoleSelectStateDataFIFOBuffer.Empty();
    }
}

//  同期とり用
void ARoleSelectPlayerState::OnRep_SyncServerString(const FString& Message)
{
    ARoleSelectGameState* rsgs = Cast<ARoleSelectGameState>(GetWorld()->GetGameState());

    bool Server = true;

    switch (rsgs->GameMode)
    {
    case EBattleGameMode::EBGM_Player_VS_Player:
    case EBattleGameMode::EBGM_Player_VS_NPC:
        //  通信対戦以外では処理をしない
        return;
    case EBattleGameMode::EBGM_Player_VS_NET:
        Server = HasAuthority();
        if (Server == true)
        {
            //  サーバー側は発信するだけなので
            UE_LOG(LogTemp, Log, TEXT("ARoleSelectPlayerState::OnRep_SyncServerString() Client SyncServerString:%s"), *SyncServerString);
            return;
        }
    }

    UE_LOG(LogTemp, Log, TEXT("OnRep_SyncServerString():%s"), *SyncServerString);

    FRoleSelectStateData    StateData = GetLastCommand();
    StateData.DataType = ERoleSelectDataType::ERSDT_Nagosiation;
    StateData.SyncServerString = SyncServerString;
    StateData.IsStayApply = true;;
    AddCommand(StateData);
}



//--------------------------------------------------------------------
void ARoleSelectPlayerState::OnRep_SlotState(const ERpoleSelectSlotState RSSState)
{

    UE_LOG(LogTemp, Log, TEXT("OnRep_SlotState():%s: %d -> %d"), HasAuthority() ? TEXT("サーバー"):TEXT("クライアント"), RSSState, SlotState);

    FRoleSelectStateData    StateData = GetLastCommand();
    StateData.DataType = ERoleSelectDataType::ERSDT_SlotState;
    StateData.SlotState = SlotState;

    switch (StateData.SlotState)
    {
    case ERpoleSelectSlotState::ERSSS_None:
    case ERpoleSelectSlotState::ERSSS_SlotCansel:
    case ERpoleSelectSlotState::ERSSS_SelectingNext:
    case ERpoleSelectSlotState::ERSSS_SelectingCansel:
//    case ERpoleSelectSlotState::ERSSS_Arrangement_Begin:
//    case ERpoleSelectSlotState::ERRSS_ArrangementCansel:
    case ERpoleSelectSlotState::ERRSS_ReadyCansel:
        StateData.IsStayApply = false;
        break;
    case ERpoleSelectSlotState::ERSSS_Selecting:
    case ERpoleSelectSlotState::ERSSS_SelectingAnim:
    case ERpoleSelectSlotState::ERRSS_CheckReady:
    case ERpoleSelectSlotState::ERRSS_Ready:
        StateData.IsStayApply = true;
        break;

    }

    AddCommand(StateData);

}

void ARoleSelectPlayerState::SetReplicated_SlotState(const ERpoleSelectSlotState RSSState)
{
    // Authorityならそのまま設定、AutonomousProxyの場合はServerRPCを呼ぶ
//    DO_CONE_CHEKER(DoOnceSlotState);
    if (HasAuthority()) {
        //  サーバー側から書き込む
        const auto Old = SlotState;
        if (Old != RSSState)
        {
            SlotState = RSSState;
            OnRep_SlotState(Old);
        }
        //        FPlatformProcess::Sleep(SEND_SLEEP_TIME);
        return;
    }
#if 1
    //  クライアント側から書き込む
    if (ABattleController* PC = GetPlayerBattleController())
    {
        auto role = PC->GetLocalRole();
        ensure(role == ROLE_AutonomousProxy);
        PC->ServerRPC_SlotState(RSSState);	// ServerRPC
    }
#endif
}

void ARoleSelectPlayerState::ServerRPC_SlotState(const ERpoleSelectSlotState RSSState)
{
#if 1
    ABattleController* BC = GetPlayerBattleController();
    if (BC)
    {

        BC->ServerRPC_SlotState(RSSState);
        return;
    }
    ensure(0);
#else
    SetReplicated_SlotState(RSSState);
#endif
}



//--------------------------------------------------------------------
void ARoleSelectPlayerState::OnRep_SlotSelectIndex(const int32 SlotIndex)
{
    UE_LOG(LogTemp, Log, TEXT("OnRep_SlotSelectIndex()%s:%d -> %d"), HasAuthority() ? TEXT("サーバー") : TEXT("クライアント"), SlotIndex , RoleSelectIndex);
    FRoleSelectStateData    StateData = GetLastCommand();
    StateData.IsStayApply = false;
    StateData.DataType = ERoleSelectDataType::ERSDT_RoleSelectIndex;
    StateData.SlotSelectIndex = RoleSelectIndex;
    AddCommand(StateData);
}

void ARoleSelectPlayerState::SetReplicated_SlotSelectIndex(const int32 SlotIndex)
{
    // Authorityならそのまま設定、AutonomousProxyの場合はServerRPCを呼ぶ
    if (HasAuthority()) {
        //  サーバー側から書き込む
        const auto Old = SlotSelectIndex;

        if (SlotSelectIndex != SlotIndex)
        {
            SlotSelectIndex = SlotIndex;
            OnRep_SlotSelectIndex(Old);
        }
        return;
    }
#if 1
    //  クライアント側から書き込む
    if (ABattleController* PC = GetPlayerBattleController())
    {
        auto role = PC->GetLocalRole();
        ensure(role == ROLE_AutonomousProxy);
        PC->ServerRPC_SlotSelectIndex(SlotIndex);	// ServerRPC
    }
#endif
}

void ARoleSelectPlayerState::ServerRPC_SlotSelectIndex(const int32 SlotIndex)
{
    ABattleController* BC = GetPlayerBattleController();
    if (BC)
    {
        DO_CONE_CHEKER(DoOnceSlotSelectIndex);
        BC->ServerRPC_SlotSelectIndex(SlotIndex);
        return;
    }
    ensure(0);
}

//--------------------------------------------------------------------
void ARoleSelectPlayerState::OnRep_GetReady(const bool Ready)
{
    UE_LOG(LogTemp, Log, TEXT("OnRep_GetReady():%s:%s"), HasAuthority() ? TEXT("サーバー") : TEXT("クライアント"), (GetReady) ? TEXT("TRUE"):TEXT("FALSE"));
    FRoleSelectStateData    StateData = GetLastCommand();
    StateData.IsStayApply = false;
    StateData.DataType = ERoleSelectDataType::ERSDT_GetReady;
    StateData.GetReady = GetReady;
    AddCommand(StateData);
}


void ARoleSelectPlayerState::SetReplicated_GetReady(const bool Ready)
{
    // Authorityならそのまま設定、AutonomousProxyの場合はServerRPCを呼ぶ
    if (HasAuthority()) {
        //  サーバー側から書き込む
        const auto Old = GetReady;
        if (Old != Ready)
        {
            GetReady = Ready;
            OnRep_GetReady(Old);
        }
        return;
    }
#if 1
    //  クライアント側から書き込む
    if (ABattleController* PC = GetPlayerBattleController())
    {
        auto role = PC->GetLocalRole();
        ensure(role == ROLE_AutonomousProxy);
        PC->ServerRPC_GetReady(Ready);	// ServerRPC
    }
#endif
}

void ARoleSelectPlayerState::ServerRPC_GetReady(const bool Ready)
{
    ABattleController* BC = GetPlayerBattleController();
    if (BC)
    {
        DO_CONE_CHEKER(DoOnceSlotGetReady);
        BC->ServerRPC_GetReady(Ready);
        return;
    }
    ensure(0);
}

//--------------------------------------------------------------------
void ARoleSelectPlayerState::OnRep_RoleSelectState(const ERoleSelectState ERSState)
{
    UE_LOG(LogTemp, Log, TEXT("OnRep_RoleSelectState():%s:%d -> %d"), HasAuthority() ? TEXT("サーバー") : TEXT("クライアント"), ERSState , RoleSelectState);
    FRoleSelectStateData    StateData = GetLastCommand();
    StateData.DataType = ERoleSelectDataType::ERSDT_RoleSelectState;
    StateData.RoleSelectState = RoleSelectState;


    switch (StateData.RoleSelectState)
    {
    case ERoleSelectState::ERS_None:
        StateData.IsStayApply = false;
        break;
    case ERoleSelectState::ERS_RoleSelect:
    case ERoleSelectState::ERS_Arrangement:
        StateData.IsStayApply = true;
        break;
    }


    AddCommand(StateData);
}

void ARoleSelectPlayerState::SetReplicated_RoleSelectState(const ERoleSelectState ERSState)
{
    // Authorityならそのまま設定、AutonomousProxyの場合はServerRPCを呼ぶ
    if (HasAuthority()) {
        //  サーバー側から書き込む
        const auto Old = RoleSelectState;
        if (Old != ERSState)
        {
            RoleSelectState = ERSState;
            OnRep_RoleSelectState(Old);
        }
        return;
    }
#if 1
    //  クライアント側から書き込む
    if (ABattleController* PC = GetPlayerBattleController())
    {
        auto role = PC->GetLocalRole();
        ensure(role == ROLE_AutonomousProxy);
        PC->ServerRPC_RoleSelectState(ERSState);	// ServerRPC
    }
#endif
}

void ARoleSelectPlayerState::ServerRPC_RoleSelectState(const ERoleSelectState ERSState)
{
    ABattleController* BC = GetPlayerBattleController();
    if (BC)
    {
        DO_CONE_CHEKER(DoOnceRoleSelectState);
        BC->ServerRPC_RoleSelectState(ERSState);
        return;
    }
    ensure(0);
}

//--------------------------------------------------------------------
void ARoleSelectPlayerState::OnRep_RoleSelectIndex(const int32 RSIndex)
{
    UE_LOG(LogTemp, Log, TEXT("OnRep_RoleSelectIndex():%s:%d -> %d"), HasAuthority() ? TEXT("サーバー") : TEXT("クライアント"), RSIndex , RoleSelectIndex);
    FRoleSelectStateData    StateData = GetLastCommand();
    StateData.DataType = ERoleSelectDataType::ERSDT_RoleSelectIndex;
    StateData.RoleSelectIndex = RoleSelectIndex;
    AddCommand(StateData);
}

void ARoleSelectPlayerState::SetReplicated_RoleSelectIndex(const int32 RSIndex)
{
    // Authorityならそのまま設定、AutonomousProxyの場合はServerRPCを呼ぶ
    if (HasAuthority()) {
        //  サーバー側から書き込む
        const auto Old = RoleSelectIndex;
        if (Old != RSIndex)
        {
            RoleSelectIndex = RSIndex;
            OnRep_RoleSelectIndex(Old);
        }
        return;
    }
#if 1
    //  クライアント側から書き込む
    if (ABattleController* PC = GetPlayerBattleController())
    {
        auto role = PC->GetLocalRole();
        ensure(role == ROLE_AutonomousProxy);
        PC->ServerRPC_RoleSelectIndex(RSIndex);	// ServerRPC
    }
#endif
}

void ARoleSelectPlayerState::ServerRPC_RoleSelectIndex(const int32 RSIndex)
{
    ABattleController* BC = GetPlayerBattleController();
    if (BC)
    {
        DO_CONE_CHEKER(RoleSelectIndex);
        BC->ServerRPC_RoleSelectIndex(RSIndex);
        return;
    }
    ensure(0);
}




//--------------------------------------------------------------------
void ARoleSelectPlayerState::OnRep_RoleSelectJob(const EUnitJob job)
{
    UE_LOG(LogTemp, Log, TEXT("OnRep_RoleSelectJob():%s:%d -> %d"), HasAuthority() ? TEXT("サーバー") : TEXT("クライアント"), job , RoleSelectJob);
    FRoleSelectStateData    StateData = GetLastCommand();
    StateData.DataType = ERoleSelectDataType::ERSDT_RoleSelectJob;
    StateData.RoleSelectJob = RoleSelectJob;
    AddCommand(StateData);
}

void ARoleSelectPlayerState::SetReplicated_RoleSelectJob(const EUnitJob job)
{
    // Authorityならそのまま設定、AutonomousProxyの場合はServerRPCを呼ぶ
    if (HasAuthority()) {
        //  サーバー側から書き込む
        const auto Old = RoleSelectJob;
        if (Old != job)
        {
            RoleSelectJob = job;
            OnRep_RoleSelectJob(Old);
        }
        return;
    }
#if 1
    //  クライアント側から書き込む
    if (ABattleController* PC = GetPlayerBattleController())
    {
        auto role = PC->GetLocalRole();
        ensure(role == ROLE_AutonomousProxy);
        PC->ServerRPC_RoleSelectJob(job);	// ServerRPC
    }
#endif
}

void ARoleSelectPlayerState::ServerRPC_RoleSelectJob(const EUnitJob job)
{
    ABattleController* BC = GetPlayerBattleController();
    if (BC)
    {
        DO_CONE_CHEKER(DoOnceRoleSelectJob);
        BC->ServerRPC_RoleSelectJob(job);
        return;
    }
    ensure(0);
}


//--------------------------------------------------------------------
void ARoleSelectPlayerState::OnRep_RoleSelectJobBefore(const EUnitJob job)
{
    UE_LOG(LogTemp, Log, TEXT("OnRep_RoleSelectJobBefore():%s:%d -> %d"), HasAuthority() ? TEXT("サーバー") : TEXT("クライアント"), job , RoleSelectJobBefore);
    FRoleSelectStateData    StateData = GetLastCommand();
    StateData.DataType = ERoleSelectDataType::ERSDT_RoleSelectJobBefore;
    StateData.RoleSelectJobBefore = RoleSelectJobBefore;
    AddCommand(StateData);
}

void ARoleSelectPlayerState::SetReplicated_RoleSelectJobBefore(const EUnitJob job)
{
    // Authorityならそのまま設定、AutonomousProxyの場合はServerRPCを呼ぶ
    if (HasAuthority()) {
        //  サーバー側から書き込む
        const auto Old = RoleSelectJobBefore;

        if (Old != job)
        {
            RoleSelectJobBefore = job;
            OnRep_RoleSelectJobBefore(Old);
        }
        return;
    }
#if 1
    //  クライアント側から書き込む
    if (ABattleController* PC = GetPlayerBattleController())
    {
        auto role = PC->GetLocalRole();
        ensure(role == ROLE_AutonomousProxy);
        PC->ServerRPC_RoleSelectJobBefore(job);	// ServerRPC
    }
#endif
}

void ARoleSelectPlayerState::ServerRPC_RoleSelectJobBefore(const EUnitJob job)
{
    ABattleController* BC = GetPlayerBattleController();
    if (BC)
    {
        DO_CONE_CHEKER(DoOnceRoleSelectJobBefore);
        BC->ServerRPC_RoleSelectJobBefore(job);
        return;
    }
    ensure(0);
}

//--------------------------------------------------------------------
void ARoleSelectPlayerState::OnRep_RoleSelectTime(const float RSTime)
{
    UE_LOG(LogTemp, Log, TEXT("OnRep_RoleSelectTime():%s:%f -> %f"), HasAuthority() ? TEXT("サーバー") : TEXT("クライアント"), RSTime , RoleSelectTime);
    FRoleSelectStateData    StateData = GetLastCommand();
    StateData.DataType = ERoleSelectDataType::ERSDT_RoleSelectTime;
    StateData.RoleSelectTime = RoleSelectTime;
    AddCommand(StateData);
}

void ARoleSelectPlayerState::SetReplicated_RoleSelectTime(const float RSTime)
{
    // Authorityならそのまま設定、AutonomousProxyの場合はServerRPCを呼ぶ
    if (HasAuthority()) {
        //  サーバー側から書き込む
        const auto Old = RoleSelectTime;
        if (Old != RSTime)
        {
            RoleSelectTime = RSTime;
            OnRep_RoleSelectTime(Old);
        }
        return;
    }
#if 1
    //  クライアント側から書き込む
    if (ABattleController* PC = GetPlayerBattleController())
    {
        auto role = PC->GetLocalRole();
        ensure(role == ROLE_AutonomousProxy);
        PC->ServerRPC_RoleSelectTime(RSTime);	// ServerRPC
    }

#endif
}

void ARoleSelectPlayerState::ServerRPC_RoleSelectTime(const float RSTime)
{
    ABattleController* BC = GetPlayerBattleController();
    if (BC)
    {
        DO_CONE_CHEKER(DoOnceRoleSelectTime);
        BC->ServerRPC_RoleSelectTime(RSTime);
        return;
    }
    ensure(0);
}




//--------------------------------------------------------------------
void ARoleSelectPlayerState::OnRep_RoleSelectTimeMax(const float RSTimeMax)
{
    UE_LOG(LogTemp, Log, TEXT("OnRep_RoleSelectTimeMax():%s:%f -> %f"), HasAuthority() ? TEXT("サーバー") : TEXT("クライアント"), RSTimeMax , RoleSelectTimeMax);
    FRoleSelectStateData    StateData = GetLastCommand();
    StateData.DataType = ERoleSelectDataType::ERSDT_RoleSelectTimeMax;
    StateData.RoleSelectTimeMax = RoleSelectTimeMax;
    AddCommand(StateData);
}

void ARoleSelectPlayerState::SetReplicated_RoleSelectTimeMax(const float RSTimeMax)
{
    // Authorityならそのまま設定、AutonomousProxyの場合はServerRPCを呼ぶ
    if (HasAuthority()) {
        //  サーバー側から書き込む
        const auto Old = RoleSelectTimeMax;
        if (Old != RSTimeMax)
        {
            RoleSelectTimeMax = RSTimeMax;
            OnRep_RoleSelectTimeMax(Old);
        }
        return;
    }
#if 1
    //  クライアント側から書き込む
    if (ABattleController* PC = GetPlayerBattleController())
    {
        auto role = PC->GetLocalRole();
        ensure(role == ROLE_AutonomousProxy);
        PC->ServerRPC_RoleSelectTimeMax(RSTimeMax);	// ServerRPC
    }
#endif
}

void ARoleSelectPlayerState::ServerRPC_RoleSelectTimeMax(const float RSTime)
{
    ABattleController* BC = GetPlayerBattleController();
    if (BC)
    {
        DO_CONE_CHEKER(DoOnceRoleSelectTimeMax);
        BC->ServerRPC_RoleSelectTimeMax(RSTime);
        return;
    }
    ensure(0);
}

//--------------------------------------------------------------------
void ARoleSelectPlayerState::OnRep_ArrangementUnitState(const EAUState State)
{
    UE_LOG(LogTemp, Log, TEXT("OnRep_ArrangementUnitState():%s:%d -> %d"), HasAuthority() ? TEXT("サーバー") : TEXT("クライアント"), State , ArrangementUnitState);
    FRoleSelectStateData    StateData = GetLastCommand();
    StateData.DataType = ERoleSelectDataType::ERSDT_RoleSelectState;
    StateData.RoleSelectState = ERoleSelectState::ERS_Arrangement;
    StateData.ArrangementUnitState = ArrangementUnitState;

    //  ステート挿せるデータにフラグをたてる
    switch (StateData.ArrangementUnitState)
    {
    case EAUState::EAUState_None:
    case EAUState::EAUState_Begin:
    case EAUState::EAUState_Selected:
    case EAUState::EAUState_SelectPositionCansel:
    case EAUState::EAUState_ReadyWait:
    case EAUState::EAUState_Ready:
    case EAUState::EAUState_StartPosX:
    case EAUState::EAUState_StartPosY:
        StateData.IsStayApply = false;
        break;
    case EAUState::EAUState_SelectPosition:
        StateData.IsStayApply = true;
        break;
    }

    AddCommand(StateData);
}

void ARoleSelectPlayerState::SetReplicated_ArrangementUnitState(const EAUState State)
{
    // Authorityならそのまま設定、AutonomousProxyの場合はServerRPCを呼ぶ
    if (HasAuthority()) {
        //  サーバー側から書き込む
        const auto Old = ArrangementUnitState;
        if (Old != State)
        {
            ArrangementUnitState = State;
            OnRep_ArrangementUnitState(Old);
        }
        return;
    }
#if 1
    //  クライアント側から書き込む
    if (ABattleController* PC = GetPlayerBattleController())
    {
        auto role = PC->GetLocalRole();
        ensure(role == ROLE_AutonomousProxy);
        PC->ServerRPC_ArrangementUnitState(State);	// ServerRPC
    }
#endif
}

void ARoleSelectPlayerState::ServerRPC_ArrangementUnitState(const EAUState State)
{
    ABattleController* BC = GetPlayerBattleController();
    if (BC)
    {
        DO_CONE_CHEKER(DoOnceArrangementUnitState);
        BC->ServerRPC_ArrangementUnitState(State);
        return;
    }
    ensure(0);
}

//--------------------------------------------------------------------
void ARoleSelectPlayerState::OnRep_ArrangementStartPosX(const int32 X)
{
    UE_LOG(LogTemp, Log, TEXT("OnRep_ArrangementStartPosX():%s:%d -> %d"), HasAuthority() ? TEXT("サーバー") : TEXT("クライアント"), X , ArrangementStartPosX);
    FRoleSelectStateData    StateData = GetLastCommand();
    StateData.DataType = ERoleSelectDataType::ERSDT_RoleSelectState;
    StateData.RoleSelectState = ERoleSelectState::ERS_Arrangement;
    StateData.ArrangementUnitState = EAUState::EAUState_StartPosX;
    StateData.ArrangementStartPosX = ArrangementStartPosX;
    AddCommand(StateData);
}

void ARoleSelectPlayerState::SetReplicated_ArrangementStartPosX(const int32 X)
{
    // Authorityならそのまま設定、AutonomousProxyの場合はServerRPCを呼ぶ
    if (HasAuthority()) {
        //  サーバー側から書き込む
        const auto Old = ArrangementStartPosX;
        if (Old != X)
        {
            ArrangementStartPosX = X;
            OnRep_ArrangementStartPosX(Old);
        }
        return;
    }
#if 1
    //  クライアント側から書き込む
    if (ABattleController* PC = GetPlayerBattleController())
    {
        auto role = PC->GetLocalRole();
        ensure(role == ROLE_AutonomousProxy);
        PC->ServerRPC_ArrangementStartPosX(X);	// ServerRPC
    }
#endif
}

void ARoleSelectPlayerState::ServerRPC_ArrangementStartPosX(const int32 X)
{
    ABattleController* BC = GetPlayerBattleController();
    if (BC)
    {
        DO_CONE_CHEKER(DoOnceArrangementStartPosX);
        BC->ServerRPC_ArrangementStartPosX(X);
        return;
    }
    ensure(0);
}



//--------------------------------------------------------------------
void ARoleSelectPlayerState::OnRep_ArrangementStartPosY(const int32 Y)
{
    UE_LOG(LogTemp, Log, TEXT("OnRep_ArrangementStartPosY():%s:%d -> %d"),(HasAuthority() ? TEXT("サーバー") : TEXT("クライアント")), Y , ArrangementStartPosY);
    FRoleSelectStateData    StateData = GetLastCommand();
    StateData.DataType = ERoleSelectDataType::ERSDT_RoleSelectState;
    StateData.RoleSelectState = ERoleSelectState::ERS_Arrangement;
    StateData.ArrangementUnitState = EAUState::EAUState_StartPosY;
    StateData.ArrangementStartPosY = ArrangementStartPosY;
    AddCommand(StateData);
}

void ARoleSelectPlayerState::SetReplicated_ArrangementStartPosY(const int32 Y)
{
    // Authorityならそのまま設定、AutonomousProxyの場合はServerRPCを呼ぶ
    if (HasAuthority()) {
        //  サーバー側から書き込む
        const auto Old = ArrangementStartPosY;
        if (Old != Y)
        {
            ArrangementStartPosY = Y;
            OnRep_ArrangementStartPosY(Old);
        }
        return;
    }
#if 1
    //  クライアント側から書き込む
    if (ABattleController* PC = GetPlayerBattleController())
    {
        auto role = PC->GetLocalRole();
        ensure(role == ROLE_AutonomousProxy);
        PC->ServerRPC_ArrangementStartPosY(Y);	// ServerRPC
    }
#endif
}

void ARoleSelectPlayerState::ServerRPC_ArrangementStartPosY(const int32 Y)
{
    ABattleController* BC = GetPlayerBattleController();
    if (BC)
    {
        DO_CONE_CHEKER(DoOnceArrangementStartPosY);
        BC->ServerRPC_ArrangementStartPosY(Y);
        return;
    }
    ensure(0);
}

void ARoleSelectPlayerState::OnRep_CallID(const ERoleSelectCallID ID)
{
    UE_LOG(LogTemp, Log, TEXT("OnRep_CallID():%s:%d -> %d"), (HasAuthority() ? TEXT("サーバー") : TEXT("クライアント")), ID, CallID);
    FRoleSelectStateData    StateData = GetLastCommand();
    StateData.DataType = ERoleSelectDataType::ERSDT_CallID;
    StateData.CallID = CallID;
    AddCommand(StateData);
}

void ARoleSelectPlayerState::SetReplicated_CallID(const ERoleSelectCallID ID)
{
    if (HasAuthority()) {
        //  サーバー側から書き込む
        const auto Old = CallID;
        if (Old != ID)
        {
            CallID = ID;
            OnRep_CallID(Old);
        }
        return;
    }
    //  クライアント側から書き込む
    if (ABattleController* PC = GetPlayerBattleController())
    {
        auto role = PC->GetLocalRole();
        ensure(role == ROLE_AutonomousProxy);
        PC->ServerRPC_CallID(ID);	// ServerRPC
    }
}

void ARoleSelectPlayerState::ServerRPC_CallID(const ERoleSelectCallID ID)
{
    ABattleController* BC = GetPlayerBattleController();
    if (BC)
    {
        BC->ServerRPC_CallID(ID);
        return;
    }
    ensure(0);
}







void ARoleSelectPlayerState::BeginPlay()
{
    Super::BeginPlay();

    DO_ONCE_COUNTER_CLEAR(DoOnceSlotState);
    DO_ONCE_COUNTER_CLEAR(DoOnceSlotSelectIndex);
    DO_ONCE_COUNTER_CLEAR(DoOnceSlotGetReady);

    DO_ONCE_COUNTER_CLEAR(DoOnceRoleSelectState);
    DO_ONCE_COUNTER_CLEAR(DoOnceRoleSelectIndex);
    DO_ONCE_COUNTER_CLEAR(DoOnceRoleSelectJob);
    DO_ONCE_COUNTER_CLEAR(DoOnceRoleSelectJobBefore);

    DO_ONCE_COUNTER_CLEAR(DoOnceRoleSelectTime);
    DO_ONCE_COUNTER_CLEAR(DoOnceRoleSelectTimeMax);

    DO_ONCE_COUNTER_CLEAR(DoOnceArrangementUnitState);
    DO_ONCE_COUNTER_CLEAR(DoOnceArrangementStartPosX);
    DO_ONCE_COUNTER_CLEAR(DoOnceArrangementStartPosY);

}


void ARoleSelectPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ThisClass, SyncServerString);

    DOREPLIFETIME(ThisClass, SlotState);
    DOREPLIFETIME(ThisClass, SlotSelectIndex);
    DOREPLIFETIME(ThisClass, GetReady);

    DOREPLIFETIME(ThisClass, RoleSelectState);
    DOREPLIFETIME(ThisClass, RoleSelectIndex);
    DOREPLIFETIME(ThisClass, RoleSelectJob);
    DOREPLIFETIME(ThisClass, RoleSelectJobBefore);
    DOREPLIFETIME(ThisClass, RoleSelectTime);
    DOREPLIFETIME(ThisClass, RoleSelectTimeMax);

    DOREPLIFETIME(ThisClass, ArrangementUnitState);
    DOREPLIFETIME(ThisClass, ArrangementStartPosX);
    DOREPLIFETIME(ThisClass, ArrangementStartPosY);
    DOREPLIFETIME(ThisClass, CallID);
}
