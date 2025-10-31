// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Battle/BattleUnits.h"
#include "Battle/BattleSelector.h"
#include "Battle/Interface/BattleInterface.h"
#include "Battle/Interface/TurnDecisionInterface.h"
#include "Battle/Interface/BattleResultInterface.h"
#include "Battle/Interface/NextTurnInterface.h"
#include "GameFramework/GameModeBase.h"
#include "Battle/BattleController.h"
#include "Battle/BattleHelper.h"
#include "Unit/UnitData.h"
#include "Unit/Unit.h"
#include "Battle/BattleActionAttack.h"
#include "Battle/BattleActionMove.h"
#include "Battle/BattleActionDiffence.h"
#include "Battle/UnitBattleParameter.h"
#include "Battle/BattleActionSkill.h"
#include "Battle/BattleInGameWidget.h"
#include "Battle/BattleCharaStatusWidget.h"
#include "Battle/BattleResultCheck.h"
#include "Battle/MasoManager.h"
#include "Battle/BattleInGameWidgetProxy.h"
#include "Battle/BattleGameStateBase.h"
#include "Battle/BattleCommunication.h"
#include "BattleGameMode.generated.h"

#define UNITDATA_DUMMY  // ダミーユニットデータの定義

UENUM(BlueprintType)
enum class EBattleTurn : uint8
{
    EBT_None        UMETA(DisplayName = "決まってない状態"),    // ターンなし
    EBT_Player1     UMETA(DisplayName = "ターンプレーヤー１"),  // プレイヤー1のターン
    EBT_Player2     UMETA(DisplayName = "ターンプレーヤー２"),   // プレイヤー2のターン
};

UENUM(BlueprintType)
enum class EBattleState : uint8
{
    EBS_Waiting            UMETA(DisplayName = "待機"),   // 待機中
    EBS_StartTurnDecision   UMETA(DisplayName = "先制後攻の決定"),// 先制後攻の決定
    EBS_Battle              UMETA(DisplayName = "戦闘中"), // 戦闘中
    EBS_NextTurn            UMETA(DisplayName = "次のターンに以降"),
    EBS_Result              UMETA(DisplayName = "結果表示"),       // 結果表示
    EBS_End                 UMETA(DisplayName = "バトル終了"),        //  バトル終了
};

UENUM(BlueprintType)
enum class EBattleResult : uint8
{
    EBR_None        UMETA(DisplayName = "結果なし"),    // 結果なし
    EBR_Player1Win  UMETA(DisplayName = "プレイヤー1の勝利"),  // プレイヤー1の勝利
    EBR_Player2Win  UMETA(DisplayName = "プレイヤー2の勝利"),   // プレイヤー2の勝利
    EBR_Draw        UMETA(DisplayName = "引き分け"),   // 引き分け
};




/**
 * ゲームモード
 */
UCLASS(Blueprintable)
class COLOSSEUM_API ABattleGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:


public:
    // コンストラクタ
    ABattleGameMode();

public:



    // 最初に呼ばれるメソッド
    virtual void BeginPlay() override;

    // 毎フレーム呼ばれるメソッド
    virtual void Tick(float DeltaSeconds) override;



public:

    // 先制後攻の決定イベント
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void BeginTurnDecision();
    virtual void BeginTurnDecision_Implementation();

    // 先制後攻の表示イベント
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void TickTurnDecsision(float DeltaSeconds);
    virtual void TickTurnDecsision_Implementation(float DeltaSeconds);

    // 戦闘開始イベント
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void BeginBattle();
    virtual void BeginBattle_Implementation();

    // 戦闘
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void TickBattle(float DeltaSeconds);
    virtual void TickBattle_Implementation(float DeltaSeconds);


    // 次のターン開始イベント
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void BeginNextTurn();
    virtual void BeginNextTurn_Implementation();

    // 次のターンの処理
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void TickNextTurn(float DeltaSeconds);
    virtual void TickNextTurn_Implementation(float DeltaSeconds);

    // 結果表示用イベント開始
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void BeginResult();
    virtual void BeginResult_Implementation();

    // 結果表示用イベントのTick
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void TickResult(float DeltaSeconds);
    virtual void TickResult_Implementation(float DeltaSeconds);

    
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void BeginPlayLevelBuleprint();
    virtual void BeginPlayLevelBuleprint_Implementation();

public:

    // ゲームモードの開始イベント
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void BeginBattleGameMode();




    // ゲームモードの開始イベント
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void SetupBattle();


    // ゲームモードの開始イベント
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void BeginGameMode();

    // ゲームモードのTickイベント
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void TickGameMode(float DeltaSeconds);

    //  先制後攻の決定処理
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void BeginStartTurnDecision();

    //  先制後攻の表示処理
    //  trueで次の状態へ
    //  falseで継続
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    bool TickStartTurnDecision(float DeltaSeconds);


    //  バトルステートの最初に呼ばれる
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void BeginRunBattleState();

    //  バトルステートの実行
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    ETickBattleState TickRunBattleState(float DeltaSeconds);

    //  結果表示状態の開始
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void BeginRunResultState();

    //  結果表示状態の処理
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    bool TickRunResultState(float DeltaSeconds);

    //  次のターン実行処理の開始
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void BeginNextTurnState();

    //  次のターンステートの実行
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    bool TickNextTurnState(float DeltaSeconds);



    // 状態を次の状態に遷移
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void NextBattleState();

    // 次のターン
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void NextTurn();

    // 戦闘結果の設定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void SetBattleResult(EBattleResult Result);

    // 戦闘結果の取得
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    EBattleResult GetBattleResult() const;

    //  現在のターン終了か判定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    bool IsNowTurnEnd() const;

    //  すべてのアクション終了フラグをクリア
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void ClearActionEndFlag();

    //  現在のチームの防御フラグをクリア
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void ClearDiffenceNowTeam();






public:
    //  ユニットの検索(nullptrで何もない)
    TObjectPtr<AUnitBattleParameter> GetUnit(uint8 GameX, uint8 GameY);

    //  ユニットの検索(nullptrで何もない)
    TObjectPtr<AUnitBattleParameter> GetUnit(TArray<TObjectPtr<AUnitBattleParameter>>& UnitActorArray , uint8 GameX, uint8 GameY) const;
    //  ユニットのインデックスを取得(-1で見つからない)
    int GetUnitIndex(TArray<TObjectPtr<AUnitBattleParameter>>& UnitActorArray, const TObjectPtr<AUnitBattleParameter>& SelectUnit) const;
    // 任意のユニットのステータス選択
    void SelectUnitStatus(TObjectPtr<AUnitBattleParameter>& SelectUnit);
    // 任意のユニットのステータス選択をキャンセル
    void CanselUnitStatus(const TObjectPtr<AUnitBattleParameter>& SelectUnit);

    // 任意のユニット以外のステータス選択をキャンセル
    void CanselWithOutUnitSatus(TArray<TObjectPtr<AUnitBattleParameter>>& Units, const TObjectPtr<AUnitBattleParameter>& SelectUnit) const;
    void CanselWithOutUnitStatus(const TObjectPtr<AUnitBattleParameter>& SelectUnit);

    //  ステータスの反映
    void ReflectionStatus(const TObjectPtr<AUnitBattleParameter>& Unit) const;
    void ReflectionStatus(const TArray<TObjectPtr<AUnitBattleParameter>>& Units) const;
    void ReflectionStatus() const;


    //  戦闘結果のチェック
    void CheckBattleResult();


private:
#ifdef UNITDATA_DUMMY
    //  ダミーデータの作成
    void CreateDummyUnits();
#endif

public:
    // 戦闘状態の取得
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    EBattleState GetCurrentBattleState() { return CurrentBattleState; }

    // 現在のバトルターンの取得
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    EBattleTurn GetCurrentBattleTurn() const { return CurrentBattleTurn; }

    // 自分自身のポインタを取得
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    ABattleGameMode* GetSelf() { return this; }


    // ターン数を返す
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    int GetTurnCount() const { return TurnCount; }

public:

    // 指定座標にカメラを向ける
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void SetLookAtBattleCamera(const FVector& LookAtLocation);

    // 視点の移動
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void SetEyeBattleCamera(const FVector& EyeLocation);

    // カメラのズーム(0.0f～1.0f)
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void SetZoomBattleCamera(float zoom);

    // カメラの計算
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void CalcBattleCamera();

    // ターン開始決定状態の処理
    void SetStartTurnDecisionState(EBattleTurn Turn);


    //  カーソル位置算出
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    FVector GetBattleCursorLocation(int X, int Y) const;


    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void SetInGameWidgetProxy(UBattleInGameWidgetProxy* WidgetProxy);



    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void SetBattleCameraFromBP(ACameraActor* Camera);


    //  プレーヤー１全滅か？
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    bool IsPlayer1AllDead() const;

    //  プレーヤー２全滅か？
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    bool IsPlayer2AllDead() const;


//    UFUNCTION(Server, Reliable)
//    virtual void RequestUpdate(struct FBattleCommunication const& InfoCom);
private:


    // 全滅か？
    bool IsAllDead(const TArray<TObjectPtr<AUnitBattleParameter>>& Units) const;

    // バトル開始時の先制後攻の決定
    void StartTurnDecision(float DeltaSeconds);

    // 戦闘状態の処理
    void RunBattleState(float DeltaSeconds);

    //  次のターン実行処理
    void RunNextTurnState(float DeltaSeconds);

    // 結果表示状態の処理
    void RunResultState(float DeltaSeconds);


public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TArray<FUnitData> Player1Units;  // 戦闘に参加するユニットのベースクラス

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TArray<FUnitData> Player2Units;  // 戦闘に参加するユニットのベースクラス

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    FString Player1TeamName = TEXT("プレーヤー１");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    FString Player2TeamName = TEXT("プレーヤー２");



    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TArray<TObjectPtr<AUnitBattleParameter>> Player1UnitsActors;  // 戦闘に参加する生成したユニットデータ

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TArray<TObjectPtr<AUnitBattleParameter>> Player2UnitsActors;  // 戦闘に参加する生成したユニットデータ

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TObjectPtr<ABattleUnits> BattleUnitsFiled;  // 戦闘に参加する生成したユニットデータ

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TObjectPtr<ABattleSelector> BattleSelector;  // 戦闘に参加する生成したユニットデータ

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TObjectPtr<AMasoManager> MasoManager;       // ワールド内にあるMasoManager格納

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TScriptInterface<ITurnDecisionInterface> TurnDecisionInterface;  // 先制後攻決定のインターフェース

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TScriptInterface<IBattleInterface> BattleInterface;  // 戦闘状態のインターフェース

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TScriptInterface<IBattleResultInterface> BattleResultInterface;  // 戦闘結果のインターフェース

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TScriptInterface<INextTurnInterface> NextTurnInterface;  // 戦闘結果のインターフェース

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TObjectPtr<ACameraActor> BattleCamera;  // 戦闘用カメラ


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    FVector BattleCameraLookAtLocation = FVector(0.0f,0.0f,0.0f);  // カメラの注視位置

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    FVector BattleCameraEyeLocation;  // カメラの視点位置

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    float BattleCameraZoom = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TObjectPtr<ABattleController> BattleController;  // 戦闘用コントローラー


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TObjectPtr<UBattleInGameWidgetProxy>    InGameWidget = nullptr;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    EBattleGameMode BattleGameModeType = EBattleGameMode::EBGM_Player_VS_Player;     //  ゲームモードのタイプ(

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TObjectPtr<ABattleGameStateBase> BattleGameStateBase = nullptr;     //  ゲームモードのタイプ(





private:
    // ユニットの生成
    int CreateUnits(TArray<TObjectPtr<AUnit>>& output, const TArray<FUnitData>& UnitDataArray ) const;

    //  ユニットバトルパラメーターの作成
    int CreateUnitBattleParameter(TArray<TObjectPtr<AUnitBattleParameter>>& output, const TArray<TObjectPtr<AUnit>>& Units,ABattleGameMode* GameMode) const;


private:
    EBattleState CurrentBattleState;  // 現在の戦闘状態
    bool bIsBeginState = true;  // 初期状態フラグ

    EBattleTurn CurrentBattleTurn;  // 現在のバトルターン


    // 結果
    int TurnCount = 1;  // ターンカウント
    EBattleResult   BattleResult = EBattleResult::EBR_None;  // 戦闘結果

    //  保存用インタフェース

    UPROPERTY(Transient)
    TObjectPtr<UBattleActionAttack> BattleActionAttack;
    UPROPERTY(Transient)
    TObjectPtr<UBattleActionMove> BattleActionMove;
    UPROPERTY(Transient)
    TObjectPtr<UBattleActionDiffence> BattleActionDiffence;
    UPROPERTY(Transient)
    TObjectPtr<UBattleActionSkill> BattleActionSkill;

    UPROPERTY(Transient)
    TObjectPtr<UBattleResultCheck> BattleResultCheck;


};
