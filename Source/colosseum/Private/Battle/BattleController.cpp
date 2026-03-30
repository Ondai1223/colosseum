// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/BattleController.h"
#include "RoleSelect/RoleSelectPlayerState.h"
#include "Net/UnrealNetwork.h" // レプリケーションに必要

#define AXIS_DEAD_ZONE  0.2f

ABattleController::ABattleController()
{
    bReplicates = true; // レプリケーションを有効にする
}


void ABattleController::CallRunOnServerInputOk_Implementation()
{
    ;
}


void ABattleController::CallRunOnServerReleaseTriggerOk_Implementation()
{
    ;
}

void ABattleController::CallRunOnServerReleaseOk_Implementation()
{
    ;
}


void ABattleController::CallRunOnServerInputCansel_Implementation()
{
    ;
}

void ABattleController::CallRunOnServerReleaseTriggerCansel_Implementation()
{
    ;
}


void ABattleController::CallRunOnServerReleaseCansel_Implementation()
{
    ;
}


void ABattleController::CallRunOnServerInputLeftAxis_Implementation(const FVector2D axis)
{
    ;
}

void ABattleController::CallRunOnServerReleaseLeftAxis_Implementation()
{
    ;
}




// キャンセル
void ABattleController::Cansel()
{
    // Example: Notify the player or game mode about the cancellation
    // This could be a call to a method in the game mode or another relevant class
    InputBegin(&InputCansel);

    if (HasAuthority() == false)
    {
        CallRunOnServerInputCansel();
    }

}


void ABattleController::TriggerCansel()
{
    InputCansel.Trigger = true;
}

void ABattleController::TriggerReleaseCansel()
{
    InputCansel.Trigger = false;

    if (HasAuthority() == false)
    {
        CallRunOnServerReleaseTriggerCansel();
    }

}

// キャンセルフラグをオフにする
void ABattleController::ReleaseCansel()
{
    InputRelease(&InputCansel);

    if (HasAuthority() == false)
    {
        CallRunOnServerReleaseCansel();
    }

}

// キャンセルフラグが立っているかどうか
bool ABattleController::IsCansel() const
{
    return InputCansel.Coutinue;
}

// キャンセルフラグが立っているかどうか
bool ABattleController::IsCanselTrigger() const
{
    return InputCansel.Trigger;
}

//  決定フラグをたてる
void ABattleController::Ok()
{
    InputOk.Coutinue = true;

    if (HasAuthority() == false)
    {
        CallRunOnServerInputOk();
    }


}

void ABattleController::TriggerOk()
{
    InputOk.Trigger = true;

    if (HasAuthority() == false)
    {
        CallRunOnServerInputOk();
    }

}

void ABattleController::ReleaseTriggerOk()
{
    InputOk.Trigger = false;

    if (HasAuthority() == false)
    {
        CallRunOnServerReleaseTriggerOk();
    }

}


//　決定フラグをオフ
void ABattleController::ReleaseOk()
{
    InputOk.Coutinue = false;
    InputOk.Trigger = false;

    if (HasAuthority() == false)
    {
        CallRunOnServerReleaseOk();
    }
}


// 決定フラグが立っているかどうか
bool ABattleController::IsOk() const
{
    return InputOk.Coutinue;
}

//  決定入力のトリガ
bool ABattleController::IsOkTrigger() const
{
    return InputOk.Trigger;
}

//  ページアップ入力
void ABattleController::PageUp()
{
    InputBegin(&InputPageUp);
}

//  ページアップ入力リリース
void ABattleController::ReleasePageUp()
{
    InputRelease(&InputPageUp);
}

//  ページアップ入力判定
bool ABattleController::IsPageUp() const
{
    return InputPageUp.Coutinue;
}

//  ページアップ入力トリガ判定
bool ABattleController::IsPageUpTrigger() const
{
    return InputPageUp.Trigger;
}

// ページダウン入力
void ABattleController::PageDown()
{
    InputBegin(&InputPageDown);
}
// ページダウン入力リリース
void ABattleController::ReleasePageDown()
{
    InputRelease(&InputPageDown);
}
// ページダウン入力判定
bool ABattleController::IsPageDown() const
{
    return InputPageDown.Coutinue;
}
// ページダウン入力トリガ判定
bool ABattleController::IsPageDownTrigger() const
{
    return InputPageDown.Trigger;
}


// ページ切り替え入力（左）
void ABattleController::PageSwitchingLeft()
{
    InputBegin(&InputPageSwitchingLeft);
}

// ページ切り替え入力リリース（左）
void ABattleController::ReleasePageSwitchingLeft()
{
    InputRelease(&InputPageSwitchingLeft);
}

// ページ切り替え入力判定（左）
bool ABattleController::IsPageSwitchingLeft() const
{
    return InputPageSwitchingLeft.Coutinue;
}

// ページ切り替え入力トリガ判定（左）
bool ABattleController::IsPageSwitchingLeftTrigger() const
{
    return InputPageSwitchingLeft.Trigger;
}

//  ページ切り替え入力（右）
void ABattleController::PageSwitchingRight()
{
    InputBegin(&InputPageSwitchingRight);
}

//  ページ切り替え入力リリース（右）
void ABattleController::ReleasePageSwitchingRight()
{
    InputRelease(&InputPageSwitchingRight);
}

//  ページ切り替え入力判定（右）
bool ABattleController::IsPageSwitchingRight() const
{
    return InputPageSwitchingRight.Coutinue;
}

//  ページ切り替え入力トリガ判定（右）
bool ABattleController::IsPageSwitchingRightTrigger() const
{
    return InputPageSwitchingRight.Trigger;
}


// ポーズ入力
void ABattleController::InPause()
{
    InputBegin(&InputPause);
}

// ポーズ入力リリース
void ABattleController::ReleasePause()
{
    InputRelease(&InputPause);
}

// ポーズ入力判定
bool ABattleController::IsPause() const
{
    return InputPause.Coutinue;
}

// ポーズ入力トリガ判定
bool ABattleController::IsPauseTrigger() const
{
    return InputPause.Trigger;
}

// タイトルに戻る入力
bool ABattleController::IsReturnToTitle() const
{
    return IsPause();
}

//  タイトルに戻る入力トリガ
bool ABattleController::IsReturnToTitleTrigger() const
{
    return IsPauseTrigger();
}

// 魔素相関図表示入力
void ABattleController::MasoCD()
{
    InputBegin(&InputMasoCD);
}

// 魔素相関図表示入力リリース
void ABattleController::ReleaseMasoCD()
{
    InputRelease(&InputMasoCD);
}

// 魔素相関図表示入力判定
bool ABattleController::IsMasoCD() const
{
    return InputMasoCD.Coutinue;
}

// 魔素相関図表示入力トリガ判定
bool ABattleController::IsMasoCDTrigger() const
{
    return InputMasoCD.Trigger;
}

void ABattleController::Motion0()
{
    InputBegin(&InputMotion0);
}

void ABattleController::ReleaseMotion0()
{
    InputRelease(&InputMotion0);
}

bool ABattleController::IsMotion0() const
{
    return InputMotion0.Coutinue;
}

bool ABattleController::IsMotion0Trigger() const
{
    return InputMotion0.Trigger;
}

void ABattleController::Motion1()
{
    InputBegin(&InputMotion1);
}

void ABattleController::ReleaseMotion1()
{
    InputRelease(&InputMotion1);
}

bool ABattleController::IsMotion1() const
{
    return InputMotion1.Coutinue;
}

bool ABattleController::IsMotion1Trigger() const
{
    return InputMotion1.Trigger;
}

void ABattleController::Motion2()
{
    InputBegin(&InputMotion2);
}

void ABattleController::ReleaseMotion2()
{
    InputRelease(&InputMotion2);
}

bool ABattleController::IsMotion2() const
{
    return InputMotion2.Coutinue;
}

bool ABattleController::IsMotion2Trigger() const
{
    return InputMotion2.Trigger;
}

void ABattleController::Motion3()
{
    InputBegin(&InputMotion3);
}

void ABattleController::ReleaseMotion3()
{
    InputRelease(&InputMotion3);
}

bool ABattleController::IsMotion3() const
{
    return InputMotion3.Coutinue;
}

bool ABattleController::IsMotion3Trigger() const
{
    return InputMotion3.Trigger;
}

void ABattleController::Motion4()
{
    InputBegin(&InputMotion4);
}

void ABattleController::ReleaseMotion4()
{
    InputRelease(&InputMotion4);
}

bool ABattleController::IsMotion4() const
{
    return InputMotion4.Coutinue;
}

bool ABattleController::IsMotion4Trigger() const
{
    return InputMotion4.Trigger;
}

void ABattleController::Motion5()
{
    InputBegin(&InputMotion5);
}

void ABattleController::ReleaseMotion5()
{
    InputRelease(&InputMotion5);
}

bool ABattleController::IsMotion5() const
{
    return InputMotion5.Coutinue;
}

bool ABattleController::IsMotion5Trigger() const
{
    return InputMotion5.Trigger;
}

void ABattleController::Motion6()
{
    InputBegin(&InputMotion6);
}

void ABattleController::ReleaseMotion6()
{
    InputRelease(&InputMotion6);
}

bool ABattleController::IsMotion6() const
{
    return InputMotion6.Coutinue;
}

bool ABattleController::IsMotion6Trigger() const
{
    return InputMotion6.Trigger;
}

void ABattleController::Motion7()
{
    InputBegin(&InputMotion7);
}

void ABattleController::ReleaseMotion7()
{
    InputRelease(&InputMotion7);
}

bool ABattleController::IsMotion7() const
{
    return InputMotion7.Coutinue;
}

bool ABattleController::IsMotion7Trigger() const
{
    return InputMotion7.Trigger;
}


void ABattleController::InputBegin(FButtonInputInfo* InputData) const
{
    InputData->BeforeContinue = false;
    InputData->Coutinue = true;
    InputData->Trigger = true;
    InputData->Repeat = true;
}

//  入力中
void ABattleController::InputRun(FButtonInputInfo* InputData,float DeltaSecounds) const
{
#if 1
    if (InputData->BeforeContinue)
    {
        InputData->Trigger = false;
    }
    InputData->BeforeContinue = InputData->Coutinue;
#endif
}

//  入力リリース
void ABattleController::InputRelease(FButtonInputInfo* InputData) const
{
    InputData->BeforeContinue = false;
    InputData->Coutinue = false;
    InputData->Trigger = false;
    InputData->Repeat = false;
}


//  アナログスティック入力開始
void ABattleController::InputBegin(ABattleController::FAxisInputInfo* InputData, const FVector2D& Axis) const
{
    bool IsBeforeInput = !((FMath::Abs(InputData->CoutinueAxis.X) < AXIS_DEAD_ZONE) || (FMath::Abs(InputData->CoutinueAxis.Y) < AXIS_DEAD_ZONE));
    InputData->CoutinueAxis = Axis;
    if (IsBeforeInput)
    {
        InputData->TriggerAxis = FVector2D::ZeroVector;
    }
    else
    {
        InputData->TriggerAxis = Axis;
    }
    InputData->BeforeContinue = IsBeforeInput;
    InputData->CoutinueAxis = Axis;
}

//  アナログスティック実行中
void ABattleController::InputRun(ABattleController::FAxisInputInfo* InputData, float DeltaSecond) const
{
    if (InputData->BeforeContinue)
    {
        InputData->TriggerAxis = FVector2D::ZeroVector;
    }
    bool IsInput = (FMath::Abs(InputData->CoutinueAxis.X) > FLT_EPSILON) || (FMath::Abs(InputData->CoutinueAxis.Y) > FLT_EPSILON);
    InputData->BeforeContinue = IsInput;
}

//  アナログスティック解除
void ABattleController::InputRelease(ABattleController::FAxisInputInfo* InputData) const
{
    InputData->BeforeContinue = false;
    InputData->CoutinueAxis = FVector2D::ZeroVector;
    InputData->TriggerAxis = FVector2D::ZeroVector;
}


// 左スティックの値をセット
void ABattleController::SetLeftAxis(const FVector2D& LeftAxis)
{
    InputLeftAxis.CoutinueAxis = LeftAxis;

    if (HasAuthority() == false)
    {
        float len = LeftAxis.Size();
        if (len <= AXIS_DEAD_ZONE)
        {
            CallRunOnServerReleaseLeftAxis();
        }
        else
        {
            CallRunOnServerInputLeftAxis(LeftAxis);
        }
    }

    
    
    //    UE_LOG(LogTemp, Warning, TEXT("Left Axis Set: X=%f, Y=%f"), InputLeftAxis.CoutinueAxis.X, InputLeftAxis.CoutinueAxis.Y);
}

// 左スティックの値を取得
FVector2D& ABattleController::GetLeftAxis()
{
    return InputLeftAxis.CoutinueAxis; // 左スティックの値を取得
}

FVector2D& ABattleController::GetLeftAxisTrigger()
{
    return InputLeftAxis.TriggerAxis;
}

void ABattleController::SetLeftAxisTrigger(const FVector2D& LeftAxis)
{
    InputLeftAxis.TriggerAxis = LeftAxis;
    InputLeftAxis.BeforeContinue = false;

    if (HasAuthority() == false)
    {
        CallRunOnServerReleaseTriggerOk();
    }



//    UE_LOG(LogTemp, Warning, TEXT("Left Axis Set: X=%f, Y=%f"), InputLeftAxis.TriggerAxis.X, InputLeftAxis.TriggerAxis.Y);

}


void ABattleController::InputRun(float DeltaSeconds)
{
    if (HasAuthority())
    {
//        InputRun(&InputOk, DeltaSeconds);
//        InputRun(&InputCansel, DeltaSeconds);
        InputRun(&InputPageUp, DeltaSeconds);
        InputRun(&InputPageDown, DeltaSeconds);
        InputRun(&InputPageSwitchingLeft, DeltaSeconds);
        InputRun(&InputPageSwitchingRight, DeltaSeconds);
        InputRun(&InputPause, DeltaSeconds);
        InputRun(&InputMasoCD, DeltaSeconds);
        InputRun(&InputLeftAxis, DeltaSeconds);
        InputRun(&InputMotion0, DeltaSeconds);
        InputRun(&InputMotion1, DeltaSeconds);
        InputRun(&InputMotion2, DeltaSeconds);
        InputRun(&InputMotion3, DeltaSeconds);
        InputRun(&InputMotion4, DeltaSeconds);
        InputRun(&InputMotion5, DeltaSeconds);
        InputRun(&InputMotion6, DeltaSeconds);
        InputRun(&InputMotion7, DeltaSeconds);

#if 0
        if (OkCont)
        {
            UE_LOG(LogTemp, Warning, TEXT("TRUE"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("FALSE"));
        }
#endif
    }

}





void ABattleController::BeginPlay()
{
    Super::BeginPlay();
    // 初期化コードなどをここに追加


    // サーバー側のみでステータスを初期化
}

void ABattleController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    // ここにレプリケーションするプロパティを追加
//    DOREPLIFETIME(ABattleController, OkContinuation);
//    DOREPLIFETIME(ABattleController, OkTrigger);
}



void ABattleController::SetupInputComponent()
{
    Super::SetupInputComponent();
    // ここで入力バインディングを設定
    // 例: InputComponent->BindAction("Cansel", IE_Pressed, this, &ABattleController::Cansel);

//    InputComponent->BindAction("Ok", IE_Pressed, this, &ABattleController::Ok);
//    InputComponent->BindAction("TriggerOk", IE_Repeat, this, &ABattleController::TriggerOk);
//    InputComponent->BindAction("ReleaseOk", IE_Released, this, &ABattleController::ReleaseOk);
}


//------------------- ロール選択で使う入力 -------------------
void ABattleController::ServerRPC_SlotState_Implementation(const ERpoleSelectSlotState RSSState)
{
    if (ARoleSelectPlayerState* PS = GetPlayerState<ARoleSelectPlayerState>()) {
        PS->SetReplicated_SlotState(RSSState);
    }
}


void ABattleController::ServerRPC_SlotSelectIndex_Implementation(const int32 SlotIndex)
{
    if (ARoleSelectPlayerState* PS = GetPlayerState<ARoleSelectPlayerState>()) {
        PS->SetReplicated_SlotSelectIndex(SlotIndex);
    }
}

void ABattleController::ServerRPC_GetReady_Implementation(const bool Ready)
{
    if (ARoleSelectPlayerState* PS = GetPlayerState<ARoleSelectPlayerState>()) {
        PS->SetReplicated_GetReady(Ready);
    }
}
void ABattleController::ServerRPC_RoleSelectState_Implementation(const ERoleSelectState ERSState)
{
    if (ARoleSelectPlayerState* PS = GetPlayerState<ARoleSelectPlayerState>()) {
        PS->SetReplicated_RoleSelectState(ERSState);
    }
}

void ABattleController::ServerRPC_RoleSelectIndex_Implementation(const int32 RSIndex)
{
    if (ARoleSelectPlayerState* PS = GetPlayerState<ARoleSelectPlayerState>()) {
        PS->SetReplicated_RoleSelectIndex(RSIndex);
    }
}

void ABattleController::ServerRPC_RoleSelectJob_Implementation(const EUnitJob job)
{
    if (ARoleSelectPlayerState* PS = GetPlayerState<ARoleSelectPlayerState>()) {
        PS->SetReplicated_RoleSelectJob(job);
    }
}

void ABattleController::ServerRPC_RoleSelectJobBefore_Implementation(const EUnitJob job)
{
    if (ARoleSelectPlayerState* PS = GetPlayerState<ARoleSelectPlayerState>()) {
        PS->SetReplicated_RoleSelectJobBefore(job);
    }
}

void ABattleController::ServerRPC_RoleSelectTime_Implementation(const float RSTime)
{
    if (ARoleSelectPlayerState* PS = GetPlayerState<ARoleSelectPlayerState>()) {
        PS->SetReplicated_RoleSelectTime(RSTime);
    }
}

void ABattleController::ServerRPC_RoleSelectTimeMax_Implementation(const float RSTimeMax)
{
    if (ARoleSelectPlayerState* PS = GetPlayerState<ARoleSelectPlayerState>()) {
        PS->SetReplicated_RoleSelectTimeMax(RSTimeMax);
    }
}

void ABattleController::ServerRPC_ArrangementUnitState_Implementation(const EAUState State)
{
    if (ARoleSelectPlayerState* PS = GetPlayerState<ARoleSelectPlayerState>()) {
        PS->SetReplicated_ArrangementUnitState(State);
    }
}

void ABattleController::ServerRPC_ArrangementStartPosX_Implementation(const int32 X)
{
    if (ARoleSelectPlayerState* PS = GetPlayerState<ARoleSelectPlayerState>()) {
        PS->SetReplicated_ArrangementStartPosX(X);
    }
}

void ABattleController::ServerRPC_ArrangementStartPosY_Implementation(const int32 Y)
{
    if (ARoleSelectPlayerState* PS = GetPlayerState<ARoleSelectPlayerState>()) {
        PS->SetReplicated_ArrangementStartPosY(Y);
    }
}

void ABattleController::ServerRPC_CallID_Implementation(const ERoleSelectCallID ID)
{
    if (ARoleSelectPlayerState* PS = GetPlayerState<ARoleSelectPlayerState>()) {
        PS->SetReplicated_CallID(ID);
    }
}



