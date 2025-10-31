// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define CATEGORY_BattleInput "BattleInput"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BattleController.generated.h"

/**
 * コントローラーの設定
 */
UCLASS(Blueprintable)
class COLOSSEUM_API ABattleController : public APlayerController
{
	GENERATED_BODY()

public:
    // キャンセルフラグをたてる
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void Cansel();

    //　キャンセルフラグをオフ
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void ReleaseCansel();

    // キャンセルフラグが立っているかどうか
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    bool IsCansel();

    // キャンセルフラグが立っているかどうか
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    bool IsCanselTrigger();

    //  決定フラグをたてる
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void Ok();

    //　決定フラグをオフ
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void ReleaseOk();


    // 決定フラグが立っているかどうか
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    bool IsOk();

    //  決定入力のトリガ
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    bool IsOkTrigger();

    // 左スティックの値をセット
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void SetLeftAxis(const FVector2D& InputLeftAxis);

    // 左スティックの値を取得
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    FVector2D& GetLeftAxis();

    // 左スティックのトリガ入力を取得
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    FVector2D& GetLeftAxisTrigger();

    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void SetLeftAxisTrigger(const FVector2D& LeftAxis);



    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void InputRun(float DeltaSeconds);



private:

    //  ボタン入力情報
    struct FButtonInputInfo
    {
        bool Coutinue = false;  //  コンテニュー入力
        bool Trigger = false;   //  トリガ入力
        bool Repeat = false;    //  リピート入力

        bool BeforeContinue = false;    //  前回のコンテニュー入力


    };

    //  アナログスティック情報
    struct FAxisInputInfo
    {
        FVector2D   CoutinueAxis = FVector2D::ZeroVector;   //  コンテニュー入力
        FVector2D   TriggerAxis = FVector2D::ZeroVector;    //  トリガー入力

        bool        BeforeContinue = false;     //  前回の入力
        bool        InputNow = false;           //  現在の入力情報


    };


    //  入力の開始
    void InputBegin(ABattleController::FButtonInputInfo* InputData) const;
    //  入力中
    void InputRun(ABattleController::FButtonInputInfo* InputData,float DeltaSecond) const;
    //  入力リリース
    void InputRelease(ABattleController::FButtonInputInfo* InputData) const;


    //  アナログスティック入力開始
    void InputBegin(ABattleController::FAxisInputInfo* InputData,const FVector2D& Axis) const;

    //  アナログスティック実行中
    void InputRun(ABattleController::FAxisInputInfo* InputData, float DeltaSecond) const;

    //  アナログスティック解除
    void InputRelease(ABattleController::FAxisInputInfo* InputData) const;

    FButtonInputInfo InputOk;        //  OK入力情報
    FButtonInputInfo InputCansel;    //  キャンセル入力情報
    FAxisInputInfo  InputLeftAxis;  //  左スティック入力情報


//    FVector2D LeftAxis = FVector2D::ZeroVector; // 左スティックの値を保持する変数


};



