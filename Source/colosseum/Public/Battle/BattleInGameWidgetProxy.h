// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Battle/BattleInGameWidget.h"
#include "BattleInGameWidgetProxy.generated.h"

/**
 * ウイジェット代理クラス
 */
UCLASS()
class COLOSSEUM_API UBattleInGameWidgetProxy : public UObject
{
	GENERATED_BODY()
	
public:

public:
    //  セットアップ
    void Setup();


    //  バトルコマンド開始
    void BeginBattleCommand(class ABattleGameMode* GameMode, class AUnitBattleParameter* BattleUnit);


    //  バトルコマンドの処理
    void TickBattleCommand(float DeltaSeconds);

    //  バトルコマンドのリリース
    void ReleaseBattleCommand(float DeltaSeconds);


public:
    //  ステータス全体の表示非表示
    void EnableVisible();
    void DisenableVisible();

    //  バトルコマンドの表示非表示
    void EnableBattleCommand();
    void DisenableBattleCommand();

    //  バトルコマンドを開く
    void OpenBattleCommand(ABattleGameMode* GameMode, AUnitBattleParameter* BattleUnit);

    //  実行
    void RunBattleCommand(float DeltaSeconds);
    //  リリースバトルコマンド
    void CloseBattleCommand(float DeltaSeconds);

    //  ターンの表示
    void EnableTurnDisplay(ABattleGameMode* GameMode);

    //  ターン非表示
    void DisenableTurnDisplay();

    //  プレーヤーのステータスをすべて反映
    void ReflectPlayersStatus(ABattleGameMode* GameMode);


public:
    //  チームのインデックスのプレイヤーステータスを取得
    TObjectPtr<UBattleCharaStatusWidget> GetPlayersStatus(EUnitTeamID Team, int Index);

    //  チームのプレイヤーネームウイジェットを取得
    TObjectPtr<UPlayerNameWidget> GetPlayerNameWidget(EUnitTeamID Team);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TObjectPtr<UBattleInGameWidget>    InGameWidget;

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
