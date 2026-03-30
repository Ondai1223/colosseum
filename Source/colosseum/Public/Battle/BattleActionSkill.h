// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Battle/Interface/BattleActionInterface.h"
#include "Battle/BattleAttackCamera.h"
#include "NiagaraSystem.h"
#include "BattleActionSkill.generated.h"

UENUM(BlueprintType)
enum class ESkillState : uint8
{
    None            UMETA(DisplayName = "何もしない"),
    MoveStartCamera UMETA(DisplayName = "カメラ移動開始"),
    MoveToTarget    UMETA(DisplayName = "ターゲットの前まで移動"),
    Skill          UMETA(DisplayName = "攻撃"),
    MoveBack        UMETA(DisplayName = "元の位置に戻る"),
    End             UMETA(DisplayName = "終了"),
    Wait            UMETA(DisplayName = "任意の秒数待つ"),
    PlayAnimWait    UMETA(DisplayName = "待機アニメーション開始"),
    PlayAnimSkill  UMETA(DisplayName = "攻撃アニメーション開始"),
    PlayAnimMove    UMETA(DisplayName = "移動アニメーション開始"),
    AnimeWaitEnd    UMETA(DisplayName = "アニメーション終了待ち"),
    CameraFinishWait UMETA(DisplayName = "カメラ終了待ち"),

};


struct FSkillStateWaitData
{
    ESkillState    NextState;      //  次の状態
    float           WaitTime;       //  待機時間
};

/**
 * 
 */
UCLASS()
class COLOSSEUM_API UBattleActionSkill : public UObject , public IBattleActionInterface
{
	GENERATED_BODY()


public:
    //  選択パネルの設定
    //  CenterGameX     :   中心となるX座標
    //  CenterGameY     :   中心となるX座標
    //  GameMode        :   ゲームモード
    virtual void SetSelectPanel(int CenterGameX, int CenterGameY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode, const FSkillDataType& SkillData) override;


    //  スキル選択開始
    //  ActionUnit      :   スキルを行使するユニット
    //  GameMode        :   ゲームモード
    virtual void SelectSkillBegin(TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode) override;

    //  スキル選択のTick
    //  -1でまだ選択が終わっていない
    //  -2でキャンセル
    //  0以上で選択したスキル
    virtual int SelectSkillTick(TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode, FSkillDataType& OutSkillData) override;
    //  アクション計算
    //  ActionResult    :   アクション結果格納先
    //  TargetLocations :   ターゲットするゲーム座標
    //  ActionUnit      :   アクションを起こすユニット
    //  GameMode        :   ゲームモード
    //  SkillID         :   スキルID(特技を選択した時のみ有効）
    virtual void CalcAction(FActionResultData* ActionResult, const TArray<FGameLocation>& TargetLocations, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode, const FSkillDataType& SkillData) override;

    //  アクション結果を反映
    //  ActionResult    :   結果格納先
    //  GameMode        :   ゲームモード
    virtual void ReflectAction(FActionResultData& ActionResult, ABattleGameMode* GameMode) override;

    //  アクション開始
    virtual void BeginAction(FActionResultData& ActionResult, ABattleGameMode* GameMode) override;

    //  アクションTick
    //  ActionResult    :   アクション結果
    //  DeltaSecounds   :   細分時間
    //  GameMode        :   ゲームモード
    //  @Return         :   true 終了 : false 続行
    virtual bool TickAction(FActionResultData& ActionResult, float DeltaSecounds, ABattleGameMode* GameMode) override;

    // 現在のステートをスタックに保存
    void PushState(ESkillState NextState, float WaitTime = 0.0f);

    //  スタックより次のステートへ移行
    void PopNextState();

    // 攻撃のNiagaraエフェクト発生
    void SpawnAttackNiagaraEffect(const FVector& Location, const FRotator& Rotator, const FName Type);

	// 回復、バフ、デバフのNiagaraエフェクト発生
    void SpawnOthersNiagaraEffect(const FVector& Location, const FRotator& Rotator, const ESkillAbility Ability);

private:
    UPROPERTY(Transient)
    TObjectPtr<ABattleAttackCamera>     SkillCamera;

    ESkillState    SkillState = ESkillState::None;
    TArray<FSkillStateWaitData>   SkillStateStack;

    FVector BackupCameraEye;
    FRotator BackupCameraRotator;


    FVector BackupSkillUnitLocation;
    FRotator BackupSkillUnitRotator;

    UPROPERTY(Transient)
    TObjectPtr<UNiagaraSystem> SkillNiagaraSystem;

	TArray<FGameLocation> SelectLocations;
};
