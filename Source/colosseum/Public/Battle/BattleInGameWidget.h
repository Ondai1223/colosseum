// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Battle/UnitBattleParameter.h"
#include "Components/VerticalBox.h"
#include "Common/PlayerNameWidget.h"
#include "Battle/BattleCharaStatusWidget.h"
#include "BattleInGameWidget.generated.h"

class ABattleGameMode;
class AUnitBattleParameter;
class UBattleCommandWidget;


UENUM(BlueprintType)
enum class EBattleCommand : uint8
{
    EBC_ATTACK  UMETA(DisplayName = "ATTACK"),
    EBC_DIFFENCE  UMETA(DisplayName = "DIFFENCE"),
    EBC_SKILL  UMETA(DisplayName = "SKILL"),
    EBC_MOVE  UMETA(DisplayName = "MOVE"),


    EBC_CONTINUE UMETA(DisplayName = "CONTINUE"),
    EBC_CANSEL UMETA(DisplayName = "CANSEL"),

};

/**
 * インゲームウイジェット
 */
UCLASS(Blueprintable)
class COLOSSEUM_API UBattleInGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct();


public:
    //  バトルコマンド開始
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void BeginBattleCommand(ABattleGameMode* GameMode , AUnitBattleParameter* BattleUnit);
    virtual void BeginBattleCommand_Implementation(ABattleGameMode* GameMode, AUnitBattleParameter* BattleUnit);

    //  バトルコマンドの処理
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void TickBattleCommand(float DeltaSeconds);
    virtual void TickBattleCommand_Implementation(float DeltaSeconds);

    //  バトルコマンドのリリース
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void ReleaseBattleCommand(float DeltaSeconds);
    virtual void ReleaseBattleCommand_Implementation(float DeltaSeconds);


public:
    //  ステータス全体の表示非表示
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void EnableVisible();
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void DisenableVisible();

    //  バトルコマンドの表示非表示
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void EnableBattleCommand();
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void DisenableBattleCommand();

    //  バトルコマンドを開く
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void OpenBattleCommand(ABattleGameMode* GameMode, AUnitBattleParameter* BattleUnit);

    //  実行
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void RunBattleCommand(float DeltaSeconds);
    //  リリースバトルコマンド
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void CloseBattleCommand(float DeltaSeconds);

    //  ターンの表示
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void EnableTurnDisplay(ABattleGameMode* GameMode);

    //  ターン非表示
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void DisenableTurnDisplay();

    //  プレーヤーのステータスをすべて反映
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void ReflectPlayersStatus(ABattleGameMode* GameMode);



public:

    //  チームのインデックスのプレイヤーステータスを取得
    TObjectPtr<UBattleCharaStatusWidget> GetPlayersStatus(EUnitTeamID Team, int Index);

    //  チームのプレイヤーネームウイジェットを取得
    TObjectPtr<UPlayerNameWidget> GetPlayerNameWidget(EUnitTeamID Team);

private:
    //  チームのプレイヤーステータスをすべて反映
    void ReflectPlayersStatus(TObjectPtr<UVerticalBox>& VBox,  ABattleGameMode* GameMode,const TArray<TObjectPtr<AUnitBattleParameter>>& Team);
    //  プレイヤーステータスを反映
    void ReflectPlayerStatus(TObjectPtr<UVerticalBox>& VBox, ABattleGameMode* GameMode, const TObjectPtr <AUnitBattleParameter>& Unit, int Index);
    //  ゲージの設定
    void SetGauge(TObjectPtr<UUserWidget>& Gauge, int NowPoint, int MaxPoint,const FText& Name);


public:
    // 選択ユニット
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TObjectPtr<AUnitBattleParameter>    SelectUnit;


    // 選択ロックフラグ
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    bool                    SelectLock = false;

    // ゲームのステート
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    EBattleCommand          Command = EBattleCommand::EBC_CONTINUE; //  バトルコマンドのステート

    // バトルコマンドのウイジェット
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TObjectPtr<UBattleCommandWidget>     BattleCommand;

    //　ターンディスプレイ
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TObjectPtr<UUserWidget>    TurnDisplay;

    //  プレーヤー１のネームウイジェット
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TObjectPtr<UPlayerNameWidget>   Player1NameWidget;

};
