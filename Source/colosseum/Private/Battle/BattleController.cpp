// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/BattleController.h"
#define AXIS_DEAD_ZONE  0.2f
// キャンセル
void ABattleController::Cansel()
{
    // Example: Notify the player or game mode about the cancellation
    // This could be a call to a method in the game mode or another relevant class
    InputBegin(&InputCansel);
}

// キャンセルフラグをオフにする
void ABattleController::ReleaseCansel()
{
    InputRelease(&InputCansel);
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

    InputBegin(&InputOk);
}

//　決定フラグをオフ
void ABattleController::ReleaseOk()
{
    InputRelease(&InputOk);
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


void ABattleController::InputBegin(ABattleController::FButtonInputInfo* InputData) const
{
    InputData->BeforeContinue = false;
    InputData->Coutinue = true;
    InputData->Trigger = true;
    InputData->Repeat = true;
}

//  入力中
void ABattleController::InputRun(FButtonInputInfo* InputData,float DeltaSecounds) const
{
    if (InputData->BeforeContinue)
    {
        InputData->Trigger = false;
    }
    InputData->BeforeContinue = InputData->Coutinue;
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
//    UE_LOG(LogTemp, Warning, TEXT("Left Axis Set: X=%f, Y=%f"), InputLeftAxis.TriggerAxis.X, InputLeftAxis.TriggerAxis.Y);

}


void ABattleController::InputRun(float DeltaSeconds)
{
    InputRun(&InputOk,DeltaSeconds);
    InputRun(&InputCansel,DeltaSeconds);
    InputRun(&InputPageUp, DeltaSeconds);
    InputRun(&InputPageDown, DeltaSeconds);
    InputRun(&InputPageSwitchingLeft, DeltaSeconds);
    InputRun(&InputPageSwitchingRight, DeltaSeconds);
    InputRun(&InputPause, DeltaSeconds);
    InputRun(&InputMasoCD, DeltaSeconds);
    InputRun(&InputLeftAxis, DeltaSeconds);
}




