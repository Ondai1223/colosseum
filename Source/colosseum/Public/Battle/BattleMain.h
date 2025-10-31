// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Battle/ActionBattleCamera.h"
#include "Battle/Interface/BattleInterface.h"
#include "Battle/UnitBattleParameter.h"
#include "Battle/ActionResultData.h"
#include "Battle/Interface/BattleActionInterface.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "BattleMain.generated.h"


UENUM(BlueprintType)
enum class EBattleMainState : uint8
{
    BMS_UnitSelect  UMETA(DisplayName = "Unit選択"),
    BMS_CommandSelect UMETA(DisplayName = "コマンド選択"),
    BMS_CommandCansel UMETA(DisplayName = "コマンドキャンセル"),

    BMS_SelectAttack UMETA(DisplayName = "攻撃選択"),
    BMS_SelectMove UMETA(DisplayName = "移動選択"),
    BMS_SelectDiffence UMETA(DisplayName = "防御選択"),
    BMS_SelectSkill UMETA(DisplayName = "スキル選択"),
    BMS_SelectSkillPanel UMETA(DisplayName = "スキルのパネル選択"),



    BMS_AttackTick  UMETA(DisplayName = "攻撃のTick"),
    BMS_DiffenceTick  UMETA(DisplayName = "防御のTick"),
    BMS_SkillTick  UMETA(DisplayName = "スキルのTick"),
    BMS_MoveTick  UMETA(DisplayName = "移動のTick"),
    BMS_MoveOkOrCansel UMETA(DisplayName = "移動後、キャンセルか固定化選べる"),
    BMS_MoveCansel  UMETA(DisplayName = "MoveCalsen and OpenSelectCommand"),
    MBS_EndAction UMETA(DisplayName = "アクション終了"),

};


class ABattleGameMode; // 前方宣言
class AUnit;

/**
 *  戦闘のメイン処理
 */
UCLASS(Blueprintable)
class COLOSSEUM_API ABattleMain : public AActor, public IBattleInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABattleMain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


    struct FMoveCursorData
    {
        uint8 X = 1; // Xカーソル位置
        uint8 Y = 0;    // Yカーソル位置
        uint8 BeforeX = 1; // 前回のXカーソル位置
        uint8 BeforeY = 0; // 前回のYカーソル位置
        float MoveTime = 0.25f; // カーソル移動時間
        float MoveLerp = 0.0f; // カーソル移動の補間値
    };

public:


    // バトル開始処理
    virtual void BeginBattleState(ABattleGameMode* GameMode) override;

    // バトルループ処理
    virtual ETickBattleState TickBattleState(ABattleGameMode* GameMode, float DeltaSeconds) override;

    // ユニット選択カーソルの作成
    void CreateCursorModel();
    
    bool MoveCursor(ABattleGameMode* GameMode, FMoveCursorData& cursor , const FVector2D& Direction, float DeltaSeconds);
    bool MoveCursor(ABattleGameMode* GameMode, const FVector2D& Direction, float DeltaSeconds);
    // ユニット選択カーソルの移動
    bool MoveUnitSelectCursor(ABattleGameMode* GameMode,float DeltaSeconds);


    //  アクション結果のクリア
    void ClearActionResult();

    // 攻撃
    void AttackAction(ABattleGameMode* GameMode,int X , int Y);

    // 防御
    void DiffenceAction(ABattleGameMode* GameMode , int X ,int Y);

    //  バトルコマンドを開く
    virtual void BeginBattleCommand(ABattleGameMode* GameMode);
    //  バトルコマンドを閉じる
    virtual void EndBattleCommand(ABattleGameMode* GameMode);


    //  カーソル位置を選択ユニットに戻す
    void ReturnSelectUnitCursorLocation(ABattleGameMode* GameMode);


public:
    EBattleMainState    BattleMainState = EBattleMainState::BMS_UnitSelect; // BattleMainの状態
    UPROPERTY(Transient)
    TObjectPtr<UStaticMeshComponent> CursorModel; // ユニットのメッシュコンポーネント

    UPROPERTY(Transient)
    TObjectPtr<UNiagaraComponent> CursorEffectComponent;

    UPROPERTY(Transient)
    TObjectPtr<UNiagaraSystem> CursorNiagaraSystem;

    UPROPERTY(Transient)
    TObjectPtr<AUnitBattleParameter>   SelectUnit;  //  選択しているユニット


    UPROPERTY(Transient)
    TObjectPtr<AUnitBattleParameter>   NowUnit;             //  現在のユニット
    UPROPERTY(Transient)
    TObjectPtr<AUnitBattleParameter>   BeforeUnit;          //  前回のユニット

    FMoveCursorData Player1Cursor;  // プレイヤー1のカーソル位置
    FMoveCursorData Player2Cursor; // プレイヤー2のカーソル位置

    ActionBattleCamera BattleCameraAction; // カメラアクション
    ActionBattleCamera MoveCanselCameraAction; // カメラアクション

    UPROPERTY(Transient)
    TScriptInterface<IBattleActionInterface>   BattleAttackInterface;   //  アタックインタフェース
    UPROPERTY(Transient)
    TScriptInterface<IBattleActionInterface>   BattleMoveInterface;     //  移動インタフェース
    UPROPERTY(Transient)
    TScriptInterface<IBattleActionInterface>   BattleSkillInterface;     //  スキルインタフェース
    UPROPERTY(Transient)
    TScriptInterface<IBattleActionInterface>   BattleDiffenceInterface;     //  防御インタフェース




    FActionResultData                          ActionResult;            //  アクションリザルト
    uint32                                      SkillID;                //  スキルID
};
