// Fill out your copyright notice in the Description page of Project Settings.


#include "Title/TitleController.h"
#define AXIS_DEAD_ZONE  0.2f

void ATitleController::Ok()
{
	InputBegin(&InputOk);
}

void ATitleController::ReleaseOk()
{
	InputRelease(&InputOk);
}

bool ATitleController::IsOk()
{
	return InputOk.Coutinue;
}

bool ATitleController::IsOkTrigger()
{
	return InputOk.Trigger;
}

void ATitleController::Cansel()
{
	InputBegin(&InputCansel);
}

void ATitleController::ReleaseCansel()
{
	InputRelease(&InputCansel);
}

bool ATitleController::IsCansel()
{
	return InputCansel.Coutinue;
}

FVector2D& ATitleController::GetLeftAxis()
{
	return InputLeftAxis.CoutinueAxis;
}

void ATitleController::SetLeftAxis(const FVector2D& LeftAxis)
{
	InputLeftAxis.CoutinueAxis = LeftAxis;
	// 通知を飛ばす.
	if (OnInputChanged.IsBound())
	{
		// UE_LOG(LogTemp, Warning, TEXT("通知を飛ばします"));
		OnInputChanged.Broadcast();
	}
}

FVector2D& ATitleController::GetLeftAxisTrigger()
{
	return InputLeftAxis.TriggerAxis;
}

void ATitleController::SetLeftAxisTrigger(const FVector2D& LeftAxis)
{
	InputLeftAxis.TriggerAxis = LeftAxis;
	InputLeftAxis.BeforeContinue = false;
}

void ATitleController::InputRun(float DeltaSeconds)
{
	InputRun(&InputOk, DeltaSeconds);
	InputRun(&InputCansel, DeltaSeconds);
	InputRun(&InputLeftAxis, DeltaSeconds);
}

void ATitleController::InputBegin(ATitleController::FButtonInputInfo* InputData) const
{
	InputData->BeforeContinue = false;
	InputData->Coutinue = true;
	InputData->Trigger = true;
	InputData->Repeat = true;
}

void ATitleController::InputRun(ATitleController::FButtonInputInfo* InputData, float DeltaSecond) const
{
	if (InputData->BeforeContinue)
	{
		InputData->Trigger = false;
	}
	InputData->BeforeContinue = InputData->Coutinue;
}

void ATitleController::InputRelease(ATitleController::FButtonInputInfo* InputData) const
{
	InputData->BeforeContinue = false;
	InputData->Coutinue = false;
	InputData->Trigger = false;
	InputData->Repeat = false;
}
//  アナログスティック実行中
void ATitleController::InputRun(ATitleController::FAxisInputInfo* InputData, float DeltaSecond) const
{
	if (InputData->BeforeContinue)
	{
		InputData->TriggerAxis = FVector2D::ZeroVector;
	}
	bool IsInput = (FMath::Abs(InputData->CoutinueAxis.X) > FLT_EPSILON) || (FMath::Abs(InputData->CoutinueAxis.Y) > FLT_EPSILON);
	InputData->BeforeContinue = IsInput;
}

//  アナログスティック入力開始
void ATitleController::InputBegin(ATitleController::FAxisInputInfo* InputData, const FVector2D& Axis) const
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

//  アナログスティック解除
void ATitleController::InputRelease(ATitleController::FAxisInputInfo* InputData) const
{
	InputData->BeforeContinue = false;
	InputData->CoutinueAxis = FVector2D::ZeroVector;
	InputData->TriggerAxis = FVector2D::ZeroVector;
}

