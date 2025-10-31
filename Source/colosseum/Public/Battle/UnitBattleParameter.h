// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Unit/UnitData.h"
#include "Unit/Interface/UnitAnimationInterface.h"
#include "UnitBattleParameter.generated.h"

#define CATEGORY_Battle "Battle"
#define DEFENSE_PARAMETER  1.3f //防御倍率


UENUM(BlueprintType)
enum class EBattleCommmand : uint8
{
    EBC_RUN UMETA(Display = "Run"),
    EBC_CANSEL UMETA(Display = "Cansel"),

    EBC_BATTLE  UMETA(DisplayName = "Command_Battle"),
    EBC_DIFFENCE  UMETA(DisplayName = "Command_Diffence"),
    EBC_MOVE  UMETA(DisplayName = "Command_Move"),
    EBC_SKILL  UMETA(DisplayName = "Command_Skill"),
};


class ABattleGameMode;
class AUnit;
class UBattleCharaStatusWidget;
class UBattleGauge;
/**
 * ユニットを戦闘に出すときのパラメーター
 */
UCLASS(Blueprintable)
class COLOSSEUM_API AUnitBattleParameter : public AActor , public IUnitAnimationInterface
{
	GENERATED_BODY()

public:
    AUnitBattleParameter();

public:
    //  バトルコマンドの開始イベント
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void BeginBattleCommand();
    virtual void BeginBattleCommand_Implementation();

    //  バトルコマンドの終了イベント
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void EndBattleCommand();
    virtual void EndBattleCommand_Implementation();


    //  バトルコマンドの表示非表示
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void BattleCommandVisible( bool visible);




public:
    //  ユニットからバトル用ユニットの設定
    void SetUnitData(TObjectPtr<AUnit>& Unit);

    //  チームIDを返す
    EUnitTeamID GetTeamID() const;

    //  ジョブIDを返す
    EUnitJob GetJobID() const;


    //  移動力を返す
    uint8 GetMobility() const;

    //  攻撃力を返す
    float GetAttackPower() const;

    //  防御力を返す
    float GetDefencePower() const;



    //  ゲーム座標を返す
    int GetGameX() const { return GameX; }
    int GetGameY() const { return GameY; }

    //  ゲーム座標を設定
    void SetGameX(int X) { GameX = X; }
    void SetGameY(int Y) { GameY = Y; }

    //  移動値固定
    void FixMove()
    {
        MoveStartX = GameX;
        MoveStartY = GameY;
    }

    //  移動開始の座標設定
    int GetMoveStartX() const { return MoveStartX; }
    int GetMoveStartY() const { return MoveStartY; }




    //  HPの取得と設定
    float GetHp() const;
    void SetHp(float NextHp);
    float GetMaxHp() const;

    //  MPの取得と設定
    float GetMp() const;
    void SetMp(float NextMp);
    float GetMaxMp() const;

    //  ユニットアクターの取得





    //  死亡フラグ
    bool IsDead() const { return Hp <= FLT_EPSILON; }


    //  アクション終了フラグ
    bool IsActionEnd() const;

    //  アクション終了設定
    void SetActionEnd(){ ActionEnd = true;}
    //  アクションフラグのクリア
    void ClearAction();

    //  攻撃フラグの設定
    void SetAttackEnd() { AttackEnd = true; }
    //  攻撃済み
    bool IsAttackEnd() const { return AttackEnd; }

    //  移動フラグの設定
    void SetMoveEnd() { MoveEnd = true; }

    //  移動したときのフラグ
    bool IsMoveEnd() const { return MoveEnd; }
    //  移動フラグのキャンセル
    void ClearMoveEnd()
    {
        MoveEnd = false;
        GameX = MoveStartX;
        GameY = MoveStartY;
    }

    //  スキルフラグの設定
    void SetSkillEnd() { SkillEnd = true; }

    //  スキル使用済みか
    bool IsSkillEnd() const { return SkillEnd; }


    //  防御状態か
    bool IsDiffence() const { return ActionDiffence; }

    //  防御選択終了判定
    bool IsDiffenceEnd() const { return IsDiffence() || IsAttackEnd() || IsSkillEnd(); }




    //  防御状態にする
    void SetActionDiffence() {
        ActionDiffence = true;
        PlayAnimationGuard();
    }
    //  防御状態クリア
    void ClearActionDiffence()
    {
        ActionDiffence = false;
        PlayAnimationWait();
    }

    // 回転設定
    void Set3DRotation(const FRotator& rotation);

    // 回転取得
    FRotator Get3DRotation() const;

    //  3D座標の設定
    void Set3DLocation(const FVector& Location);

    //  3D座標の取得
    FVector Get3DLocation() const;

    //  表示非表示の設定
    void SetVisible(bool visible);
    //  表示されているか
    bool IsVisible() const;

    void SetGameMode(ABattleGameMode* InGameMode);

    //  ゲームモードの設定
    TObjectPtr<ABattleGameMode> GetGameMode() const;

    //  ステータスウエジットの設定
    void SetBattleCharaStatusWidget(TObjectPtr<UBattleCharaStatusWidget> CharaStatusWidget);

    //  ステータスウエジットの取得
    TObjectPtr<UBattleCharaStatusWidget> GetBattleCharaStatusWidget();

    //  HPゲージの設定
    void SetHpGaugeWidget(TObjectPtr<UBattleGauge> HpGauge);

    //  HPゲージの取得
    TObjectPtr<UBattleGauge> GetHpGaugeWidget();


    //  MPゲージの設定
    void SetMpGaugeWidget(TObjectPtr<UBattleGauge> MpGauge);

    //  MPゲージの取得
    TObjectPtr<UBattleGauge> GetMpGaugeWidget();

public:
    //  アニメーション再生関数のオーバーライド

    // 待機アニメーションの再生
    virtual  void PlayAnimationWait(float ShiftTime = SHIFT_ANIME_TIME) override;

    // 移動アニメーションの再生
    virtual  void PlayAnimationMove(float ShiftTime = SHIFT_ANIME_TIME) override;

    // 攻撃のアニメーションの再生
    virtual  void PlayAnimationAttack(float ShiftTime = SHIFT_ANIME_TIME) override;

    // ダメージのアニメーションの再生
    virtual  void PlayAnimationDamage(float ShiftTime = SHIFT_ANIME_TIME) override;

    // 死亡のアニメーションの再生
    virtual  void PlayAnimationDeath(float ShiftTime = SHIFT_ANIME_TIME) override;

    //  ガード
    virtual  void PlayAnimationGuard(float ShiftTime = SHIFT_ANIME_TIME) override;

    //  スキルアタックの再生
    virtual  void PlayAnimationSkillAttack(float ShiftTime = SHIFT_ANIME_TIME) override;

    //  バフの再生
    virtual  void PlayAnimationBuf(float ShiftTime = SHIFT_ANIME_TIME) override;



    //  アニメーション終了判定
    bool IsEndOfAnime() const;


private:
    //  ゲームモード
    UPROPERTY(Transient)
    TObjectPtr<ABattleGameMode> GameMode;
    //  ユニット
    UPROPERTY(Transient)
    TObjectPtr<AUnit> UnitActor;

    UPROPERTY(Transient)
    TObjectPtr<UBattleCharaStatusWidget> BattleCharaStatusWidget;

    UPROPERTY(Transient)
    TObjectPtr<UBattleGauge> BattleHPGauge;

    UPROPERTY(Transient)
    TObjectPtr<UBattleGauge> BattleMpGauge;




    //  戦闘中で使うパラメータ
    int GameX = 0;  //  ゲーム座標X
    int GameY = 0;  //  ゲーム座標Y

    int MoveStartX = 0;
    int MoveStartY = 0;

    //  パラメータ
    float Hp = 0.0f;
    float Mp = 0.0f;

    bool ActionDiffence = false;    //  防御状態

    bool ActionEnd = false;   //  行動が終了すると建つフラグ

    bool AttackEnd = false;     //  攻撃が終了したことを示すフラグ
    bool MoveEnd = false;       //  移動が終了したことを示すフラグ
    bool SkillEnd = false;         //  スキルが終了したことを示すフラグ

};



