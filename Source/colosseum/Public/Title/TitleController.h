// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TitleController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInputChangedSignature);
/**
 * タイトルController
 */
UCLASS()
class COLOSSEUM_API ATitleController : public APlayerController
{
	GENERATED_BODY()

public:
    // 外部から購読（Bind）するためのデリゲートインスタンス
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnInputChangedSignature OnInputChanged;
    //  決定フラグをたてる
    UFUNCTION(BlueprintCallable, Category = CATEGORY_TitleInput)
    void Ok();

    //　決定フラグをオフ
    UFUNCTION(BlueprintCallable, Category = CATEGORY_TitleInput)
    void ReleaseOk();

    // 決定フラグが立っているかどうか
    UFUNCTION(BlueprintCallable, Category = CATEGORY_TitleInput)
    bool IsOk();

    //  決定入力のトリガ
    UFUNCTION(BlueprintCallable, Category = CATEGORY_TitleInput)
    bool IsOkTrigger();

    // キャンセルフラグをたてる
    UFUNCTION(BlueprintCallable, Category = CATEGORY_TitleInput)
    void Cansel();

    //　キャンセルフラグをオフ
    UFUNCTION(BlueprintCallable, Category = CATEGORY_TitleInput)
    void ReleaseCansel();

    // キャンセルフラグが立っているかどうか
    UFUNCTION(BlueprintCallable, Category = CATEGORY_TitleInput)
    bool IsCansel();

    /////////スティック入力///////////
    
    // 左スティックの値を取得
    UFUNCTION(BlueprintCallable, Category = CATEGORY_TitleInput)
    FVector2D& GetLeftAxis();

    // 左スティックの値をセット
    UFUNCTION(BlueprintCallable, Category = CATEGORY_TitleInput)
    void SetLeftAxis(const FVector2D& LeftAxis);

    // 左スティックのトリガ入力を取得
    UFUNCTION(BlueprintCallable, Category = CATEGORY_TitleInput)
    FVector2D& GetLeftAxisTrigger();

    UFUNCTION(BlueprintCallable, Category = CATEGORY_TitleInput)
    void SetLeftAxisTrigger(const FVector2D& LeftAxis);

   
    UFUNCTION(BlueprintCallable, Category = CATEGORY_TitleInput)
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
    void InputBegin(ATitleController::FButtonInputInfo* InputData) const;
    //  入力中
    void InputRun(ATitleController::FButtonInputInfo* InputData, float DeltaSecond) const;
    //  入力リリース
    void InputRelease(ATitleController::FButtonInputInfo* InputData) const;


    //  アナログスティック入力開始
    void InputBegin(ATitleController::FAxisInputInfo* InputData, const FVector2D& Axis) const;

    //  アナログスティック実行中
    void InputRun(ATitleController::FAxisInputInfo* InputData, float DeltaSecond) const;

    //  アナログスティック解除
    void InputRelease(ATitleController::FAxisInputInfo* InputData) const;


    FButtonInputInfo InputOk;        //  OK入力情報
    FButtonInputInfo InputCansel;    //  キャンセル入力情報
    FAxisInputInfo  InputLeftAxis;  //  左スティック入力情報
};
