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
    bool IsCansel() const;

    // キャンセルフラグが立っているかどうか
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    bool IsCanselTrigger() const;

    //  決定フラグをたてる
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void Ok();

    //　決定フラグをオフ
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void ReleaseOk();


    // 決定フラグが立っているかどうか
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    bool IsOk() const;

    //  決定入力のトリガ
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    bool IsOkTrigger() const;


    //  ページアップ入力
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void PageUp();

    //  ページアップ入力リリース
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void ReleasePageUp();

    //  ページアップ入力判定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    bool IsPageUp() const;

    //  ページアップ入力トリガ判定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    bool IsPageUpTrigger() const;


    // ページダウン入力
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void PageDown();
    // ページダウン入力リリース
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void ReleasePageDown();
    // ページダウン入力判定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    bool IsPageDown() const;
    // ページダウン入力トリガ判定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    bool IsPageDownTrigger() const;



    // ページ切り替え入力（左）
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void PageSwitchingLeft();

    // ページ切り替え入力リリース（左）
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void ReleasePageSwitchingLeft();

    // ページ切り替え入力判定（左）
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    bool IsPageSwitchingLeft() const;

    // ページ切り替え入力トリガ判定（左）
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    bool IsPageSwitchingLeftTrigger() const;

    //  ページ切り替え入力（右）
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void PageSwitchingRight();

    //  ページ切り替え入力リリース（右）
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void ReleasePageSwitchingRight();

    //  ページ切り替え入力判定（右）
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    bool IsPageSwitchingRight() const;

    //  ページ切り替え入力トリガ判定（右）
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    bool IsPageSwitchingRightTrigger() const;

    // ポーズ入力
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void InPause();

    // ポーズ入力リリース
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void ReleasePause();

    // ポーズ入力判定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    bool IsPause() const;

    // ポーズ入力トリガ判定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    bool IsPauseTrigger() const;

    /**
     * サブ画面で使う判定処理（ここから)
     */
    // タイトルに戻る入力判定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    bool IsReturnToTitle() const;

    // タイトルに戻る入力トリガ判定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    bool IsReturnToTitleTrigger() const;
    /**
     * サブ画面で使う判定処理（ここまで)
     */


    //　魔素相関図表示入力
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void MasoCD();

    //　魔素相関図表示入力リリース
    UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
    void ReleaseMasoCD();

    // 魔素相関図表示入力判定
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   bool IsMasoCD() const;

   // 魔素相関図表示入力トリガ判定
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   bool IsMasoCDTrigger() const;


   //　モーション再生入力
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   void Motion0();

   //　モーション再生入力リリース
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   void ReleaseMotion0();

   // モーション再生入力判定
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   bool IsMotion0() const;

   // モーション再生入力トリガ判定
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   bool IsMotion0Trigger() const;


   //　モーション再生入力
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   void Motion1();

   //　モーション再生入力リリース
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   void ReleaseMotion1();

   // モーション再生入力判定
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   bool IsMotion1() const;

   // モーション再生入力トリガ判定
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   bool IsMotion1Trigger() const;


   //　モーション再生入力
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   void Motion2();

   //　モーション再生入力リリース
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   void ReleaseMotion2();

   // モーション再生入力判定
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   bool IsMotion2() const;

   // モーション再生入力トリガ判定
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   bool IsMotion2Trigger() const;


   //　モーション再生入力
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   void Motion3();

   //　モーション再生入力リリース
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   void ReleaseMotion3();

   // モーション再生入力判定
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   bool IsMotion3() const;

   // モーション再生入力トリガ判定
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   bool IsMotion3Trigger() const;


   //　モーション再生入力
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   void Motion4();

   //　モーション再生入力リリース
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   void ReleaseMotion4();

   // モーション再生入力判定
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   bool IsMotion4() const;

   // モーション再生入力トリガ判定
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   bool IsMotion4Trigger() const;


   //　モーション再生入力
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   void Motion5();

   //　モーション再生入力リリース
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   void ReleaseMotion5();

   // モーション再生入力判定
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   bool IsMotion5() const;

   // モーション再生入力トリガ判定
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   bool IsMotion5Trigger() const;
     
     
   //　モーション再生入力
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   void Motion6();

   //　モーション再生入力リリース
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   void ReleaseMotion6();

   // モーション再生入力判定
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   bool IsMotion6() const;

   // モーション再生入力トリガ判定
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   bool IsMotion6Trigger() const;


   //　モーション再生入力
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   void Motion7();

   //　モーション再生入力リリース
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   void ReleaseMotion7();

   // モーション再生入力判定
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   bool IsMotion7() const;

   // モーション再生入力トリガ判定
   UFUNCTION(BlueprintCallable, Category = CATEGORY_BattleInput)
   bool IsMotion7Trigger() const;

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

    FButtonInputInfo InputPageUp;     //  ページアップ入力情報
    FButtonInputInfo InputPageDown;   //  ページダウン入力情報
    FButtonInputInfo InputPageSwitchingLeft;   //  ページ切り替え入力情報（左）
    FButtonInputInfo InputPageSwitchingRight;   //  ページ切り替え入力情報（右）
    FButtonInputInfo InputPause;    // ポーズ入力情報

    FButtonInputInfo InputMasoCD;    // 魔素相関図表示

    FButtonInputInfo InputMotion0;    // モーション１つ目
    FButtonInputInfo InputMotion1;    // モーション２つ目
    FButtonInputInfo InputMotion2;    // モーション３つ目
    FButtonInputInfo InputMotion3;    // モーション４つ目
    FButtonInputInfo InputMotion4;    // モーション５つ目
    FButtonInputInfo InputMotion5;    // モーション６つ目
    FButtonInputInfo InputMotion6;    // モーション７つ目
    FButtonInputInfo InputMotion7;    // モーション８つ目



    FAxisInputInfo  InputLeftAxis;  //  左スティック入力情報


//    FVector2D LeftAxis = FVector2D::ZeroVector; // 左スティックの値を保持する変数


};



