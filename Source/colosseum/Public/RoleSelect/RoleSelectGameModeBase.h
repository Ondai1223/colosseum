// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RoleSelect/RoleSelectDefines.h"
#include "RoleSelect/RoleSelectCursor.h"
#include "Unit/Unit.h"
#include "Unit/UnitData.h"
#include "Battle/BattleController.h"
#include "RoleSelect/Interface/RoleArrangementInterface.h"
#include "RoleSelectGameModeBase.generated.h"


class ARoleArrangement;


UENUM(BlueprintType)
enum class ERoleSelectState : uint8
{
    ERS_None            UMETA(DisplayName = "状態なし"),    // 状態なし
    ERS_RoleSelect      UMETA(DisplayName = "ロールセレクト中"),  // ロールセレクト中
    ERS_Arrangement     UMETA(DisplayName = "ユニット配置中"),   // ユニット配置中
};

/**
 * ロールセレクトゲームモードベース
 */
UCLASS()
class COLOSSEUM_API ARoleSelectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

    // ロールセレクトゲームモード開始処理
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void BeginRoleSelectGameMode();

    // ロールセレクトゲームモード処理
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void TickRoleSelectGameMode( ABattleController* Controller , float DeltaSeconds);


    // ワークスペースのユニット選択
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void SelectUnitWorkSpace();


    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    ARoleSelectGameModeBase* GetGameModeBaseInstance();


private:
    // 作業用ユニット作成
    void CreateWorkUnit(TArray<TObjectPtr<AUnit>>& Units,EUnitTeamID TeamID);

public:

//    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
//    TObjectPtr<ABattleController> Controller;  // 戦闘用コントローラー


public:
    //  カーソル
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    TObjectPtr<ARoleSelectCursor> RoleSelectCursorActor;

    //  配置したユニットたち
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    TArray<TObjectPtr<AUnit>>   Player1Units;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    TArray<TObjectPtr<AUnit>>   Player2Units;

    // バトルに渡すユニットデータ
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    TArray<FUnitData>   Player1UnitDatas;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    TArray<FUnitData>   Player2UnitDatas;


    // 作業用ユニットデータ
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    FUnitData           WorkUnitData;

    // 予めロードしておくユニット
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    TArray<TObjectPtr<AUnit>>   WorkPlayer1Units;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    TArray<TObjectPtr<AUnit>>   WorkPlayer2Units;

    // 作業用ユニットインデックス
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    int WorkUnitIndex = 0;



    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    ERoleSelectState    NowProccessState = ERoleSelectState::ERS_RoleSelect;



    //  ゲームの対戦モード
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    EBattleGameMode GameMode = EBattleGameMode::EBGM_Player_VS_Player;


private:

    // ロール配置インターフェース
    UPROPERTY(Transient)
    TObjectPtr<ARoleArrangement> RoleArrangementInterface;


};
