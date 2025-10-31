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
bool ABattleController::IsCansel()
{
    return InputCansel.Coutinue;
}

// キャンセルフラグが立っているかどうか
bool ABattleController::IsCanselTrigger()
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
bool ABattleController::IsOk()
{
    return InputOk.Coutinue;
}

//  決定入力のトリガ
bool ABattleController::IsOkTrigger()
{
    return InputOk.Trigger;
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
    InputRun(&InputLeftAxis, DeltaSeconds);
}




