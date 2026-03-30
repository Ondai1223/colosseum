// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerState.h"
#include "Battle/BattleController.h"
#include "RoleSelect/RoleSelectDefines.h"
#include "RoleSelect/RoleSelectPage.h"
#include "RoleSelect/RoleSelectENums.h"
#include "RoleSelect/RoleSelectStateData.h"
#include "RoleSelect/RoleArrangementUnitStage.h"
#include "RoleSelectPlayerState.generated.h"


#define ARRANGEMENT_SYNC_READY TEXT("SyncReadyMessage")
#define ARRANGEMENT_SYNC_SELECTED TEXT("SyncSelectedMessage")
#define ARRANGEMENT_SYNC_READY_CANCEL TEXT("SyncReadyCancelMessage")
#define ARRANGEMENT_SYNC_READY_WAIT  TEXT("SyncReadyWaitMessage")
#define ARRANGEMENT_SYNC_CANSEL TEXT("SyncCanselMessage")


//#define FRAME_DO_CONCE_CHECKER  //  １フレで一回しか呼び出してはいけない処理のチェック

/**
 *  プレーヤーロール選択ステート
 */
UCLASS()
class COLOSSEUM_API ARoleSelectPlayerState : public APlayerState
{
    GENERATED_BODY()




public:


    ARoleSelectPlayerState();


    //  ネゴシエーションメッセージの同期
//    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
//    void SyncNegotiationMessage(const FString& Message);
//    virtual void SyncNegotiationMessage_Implementation(const FString& Message);

public:
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void SetOnlyRelevantToOwner(bool flag);

    /**
     *  プレイヤー番号の取得
     */
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    int GetPlayerNo() const;


    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    bool CompereString(const FString& StrLeft , const FString& StrRight) const;


    //  サーバーにメッセージを送る
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void SendServerMessage(const FString& Message);
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    bool IsSyncServerMessage(const FString& Message) const;

    //  受け取ったメッセージを取得
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    const FString& GetServerMessage() const { return SyncServerString; }


    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void TickProc(URoleSelectPage* page, float DT);


public:

    void TickNewWorkProc(URoleSelectPage* page, float DT);


    bool IsRunCommand() const;

    UFUNCTION()
    FRoleSelectStateData GetLastCommand() const;

    //  BattleControllerの取得
    ABattleController* GetPlayerBattleController() const;

    UFUNCTION()
    void AddCommand(const FRoleSelectStateData& DataState);


    UFUNCTION()
    void OnRep_SyncServerString(const FString& Message);


    //  -------------------------------------------------------------
    //  スロットステートの取得と設定    
    UFUNCTION()
    void OnRep_SlotState( const ERpoleSelectSlotState RSSState );

    ERpoleSelectSlotState GetReplicated_SlotState() const { return(SlotState); }
    void SetReplicated_SlotState(const ERpoleSelectSlotState RSSState);

    void ServerRPC_SlotState(const ERpoleSelectSlotState RSSState);


    //  -------------------------------------------------------------
    //  スロットインデックスの取得と設定
    UFUNCTION()
    void OnRep_SlotSelectIndex(const int32 SlotIndex);

    int32 GetReplicated_SlotSelectIndex() const { return(SlotSelectIndex); }
    void SetReplicated_SlotSelectIndex(const int32 SlotIndex);

    void ServerRPC_SlotSelectIndex(const int32 SlotIndex);
    //  -------------------------------------------------------------
    // 準備完了の取得と設定

    UFUNCTION()
    void OnRep_GetReady(const bool Ready);

    bool GetReplicated_GetReady() const { return(GetReady); }
    void SetReplicated_GetReady(const bool SlotIndex);

    void ServerRPC_GetReady(const bool SlotIndex);
    //  -------------------------------------------------------------
    //  ロール選択ステートの取得と設定
    UFUNCTION()
    void OnRep_RoleSelectState(const ERoleSelectState ERSState);

    ERoleSelectState GetReplicated_RoleSelectState() const { return(RoleSelectState); }
    void SetReplicated_RoleSelectState(const ERoleSelectState ERSState);

    void ServerRPC_RoleSelectState(const ERoleSelectState ERSState);


    //  -------------------------------------------------------------
    //  ロール選択インデックスの取得と設定
    UFUNCTION()
    void OnRep_RoleSelectIndex(const int32 RSIndex);

    int32 GetReplicated_RoleSelectIndex() const { return(RoleSelectIndex); }
    void SetReplicated_RoleSelectIndex(const int32 RSIndex);

    void ServerRPC_RoleSelectIndex(const int32 RSIndex);



    //  -------------------------------------------------------------
    //  ロール選択の取得と設定
    UFUNCTION()
    void OnRep_RoleSelectJob( const EUnitJob job);

    EUnitJob GetReplicated_RoleSelectJob() const { return(RoleSelectJob); }
    void SetReplicated_RoleSelectJob(const EUnitJob job);

    void ServerRPC_RoleSelectJob(const EUnitJob job);

    //  -------------------------------------------------------------
    //  前のロール選択の取得と設定
    UFUNCTION()
    void OnRep_RoleSelectJobBefore(const EUnitJob job);

    EUnitJob GetReplicated_RoleSelectJobBefore() const { return(RoleSelectJobBefore); }
    void SetReplicated_RoleSelectJobBefore(const EUnitJob job);

    void ServerRPC_RoleSelectJobBefore(const EUnitJob job);

    //  -------------------------------------------------------------
    //  ロール選択の時間の取得と設定
    UFUNCTION()
    void OnRep_RoleSelectTime(const float RSTime);

    float GetReplicated_RoleSelectTime() const { return(RoleSelectTime); }
    void SetReplicated_RoleSelectTime(const float RSTime);

    void ServerRPC_RoleSelectTime(const float RSTime);


    //  -------------------------------------------------------------
    //  ロール選択の最大時間の取得と設定
    UFUNCTION()
    void OnRep_RoleSelectTimeMax(const float RSTimeMax);

    float GetReplicated_RoleSelectTimeMax() const { return(RoleSelectTimeMax); }
    void SetReplicated_RoleSelectTimeMax(const float RSTime);

    void ServerRPC_RoleSelectTimeMax(const float RSTime);


    //  -------------------------------------------------------------
    //  ユニット配置の状態の取得と設定
    UFUNCTION()
    void OnRep_ArrangementUnitState(const EAUState State);

    EAUState GetReplicated_ArrangementUnitState() const { return(ArrangementUnitState); }
    void SetReplicated_ArrangementUnitState(const EAUState State);

    void ServerRPC_ArrangementUnitState(const EAUState State);



    //  -------------------------------------------------------------
    //  ユニット配置の開始位置Xの取得と設定
    UFUNCTION()
    void OnRep_ArrangementStartPosX(const int32 X);

    int32 GetReplicated_ArrangementStartPosX() const { return(ArrangementStartPosX); }
    void SetReplicated_ArrangementStartPosX(const int32 X);

    void ServerRPC_ArrangementStartPosX(const int32 X);


    //  -------------------------------------------------------------
    //  ユニット配置の開始位置Yの取得と設定
    UFUNCTION()
    void OnRep_ArrangementStartPosY(const int32 Y);

    int32 GetReplicated_ArrangementStartPosY() const { return(ArrangementStartPosY); }
    void SetReplicated_ArrangementStartPosY(const int32 Y);

    void ServerRPC_ArrangementStartPosY(const int32 Y);


    //  -------------------------------------------------------------
    //  コールIDの設定
    UFUNCTION()
    void OnRep_CallID(const ERoleSelectCallID ID);

    ERoleSelectCallID GetReplicated_CallID() const { return(CallID); }
    void SetReplicated_CallID(const ERoleSelectCallID ID);

    void ServerRPC_CallID(const ERoleSelectCallID ID);



protected:
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;



public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    int PlayerIndex;

    //  プレーヤーの情報
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    TObjectPtr<ABattleController> PlayerBattleController;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    TObjectPtr<URoleSelectPage> PlayerRoleSelectPage;

    //  チームID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    EUnitTeamID TeamID = EUnitTeamID::EUTID_None;



    UPROPERTY(Transient)
    bool ClientSlotRun = false;     //クライアントで使う

    UPROPERTY()
    TArray<FRoleSelectStateData>    RoleSelectStateDataFIFO;
    UPROPERTY()
    TArray<FRoleSelectStateData>    RoleSelectStateDataFIFOBuffer;

    //  最後に実行したコマンドの状態(コマンドがカラになると適用されるステート
    UPROPERTY()
    FRoleSelectStateData   NowDataState;



    /**
     *  サーバーからクライアントに送るデータ（ここから）
     * 注意：（ReplicatedUsing = OnRep_～のコールバックは変更のあった変数のみで反応します。）
     */
    //-------------------------------------------------------------
    //-------------------------------------------------------------
    //  サーバー同期用文字列
    UPROPERTY(Replicated , ReplicatedUsing = OnRep_SyncServerString)
    FString SyncServerString = "";

    UPROPERTY(Replicated)
    bool IsSyncServerString = false;    // 同期がとれたら trueになる(サーバーから読み取る)

protected:
    //-------------------------------------------------------------
    //-------------------------------------------------------------
    //  スロットステータス(サーバーからのみ書き込みが出来る)
    UPROPERTY(Replicated , ReplicatedUsing = OnRep_SlotState)
    ERpoleSelectSlotState   SlotState = ERpoleSelectSlotState::ERSSS_None; //  スロットの状態
#ifdef FRAME_DO_CONCE_CHECKER
    int32 DoOnceSlotState = 0;
#endif // FRAME_DO_CONCE_CHECKER

    UPROPERTY(Replicated , ReplicatedUsing = OnRep_SlotSelectIndex)
    int32 SlotSelectIndex = 0;
#ifdef FRAME_DO_CONCE_CHECKER
    int32 DoOnceSlotSelectIndex = 0;
#endif // FRAME_DO_CONCE_CHECKER

    UPROPERTY(Replicated , ReplicatedUsing = OnRep_GetReady)
    bool GetReady = false;
#ifdef FRAME_DO_CONCE_CHECKER
    int32 DoOnceSlotGetReady = 0;
#endif // FRAME_DO_CONCE_CHECKER



    //-------------------------------------------------------------
    //-------------------------------------------------------------
    UPROPERTY(Replicated , ReplicatedUsing = OnRep_RoleSelectState)
    ERoleSelectState    RoleSelectState = ERoleSelectState::ERS_None;
#ifdef FRAME_DO_CONCE_CHECKER
    int32 DoOnceRoleSelectState = 0;
#endif // FRAME_DO_CONCE_CHECKER



    UPROPERTY(Replicated , ReplicatedUsing = OnRep_RoleSelectIndex)
    int32    RoleSelectIndex = 0;
#ifdef FRAME_DO_CONCE_CHECKER
    int32 DoOnceRoleSelectIndex = 0;
#endif // FRAME_DO_CONCE_CHECKER


    UPROPERTY(Replicated , ReplicatedUsing = OnRep_RoleSelectJob)
    EUnitJob    RoleSelectJob = EUnitJob::EUJ_None;
#ifdef FRAME_DO_CONCE_CHECKER
    int32 DoOnceRoleSelectJob = 0;
#endif // FRAME_DO_CONCE_CHECKER

    UPROPERTY(Replicated , ReplicatedUsing = OnRep_RoleSelectJobBefore)
    EUnitJob    RoleSelectJobBefore = EUnitJob::EUJ_None;
#ifdef FRAME_DO_CONCE_CHECKER
    int32 DoOnceRoleSelectJobBefore = 0;
#endif // FRAME_DO_CONCE_CHECKER

    UPROPERTY(Replicated , ReplicatedUsing = OnRep_RoleSelectTime)
    float    RoleSelectTime = 1.0f;
#ifdef FRAME_DO_CONCE_CHECKER
    int32 DoOnceRoleSelectTime = 0;
#endif // FRAME_DO_CONCE_CHECKER

    UPROPERTY(Replicated , ReplicatedUsing = OnRep_RoleSelectTimeMax)
    float    RoleSelectTimeMax = 1.0f;

#ifdef FRAME_DO_CONCE_CHECKER
    int32 DoOnceRoleSelectTimeMax = 0;
#endif // FRAME_DO_CONCE_CHECKER

    //-------------------------------------------------------------
    //-------------------------------------------------------------
    UPROPERTY(Replicated , ReplicatedUsing = OnRep_ArrangementUnitState)
    EAUState    ArrangementUnitState = EAUState::EAUState_None;
#ifdef FRAME_DO_CONCE_CHECKER
    int32 DoOnceArrangementUnitState = 0;
#endif // FRAME_DO_CONCE_CHECKER

    UPROPERTY(Replicated , ReplicatedUsing = OnRep_ArrangementStartPosX)
    int32 ArrangementStartPosX = 1;
#ifdef FRAME_DO_CONCE_CHECKER
    int32 DoOnceArrangementStartPosX = 0;
#endif // FRAME_DO_CONCE_CHECKER

    UPROPERTY(Replicated , ReplicatedUsing = OnRep_ArrangementStartPosY)
    int32 ArrangementStartPosY = 0;
#ifdef FRAME_DO_CONCE_CHECKER
    int32 DoOnceArrangementStartPosY = 0;
#endif // FRAME_DO_CONCE_CHECKER


    UPROPERTY(Replicated, ReplicatedUsing = OnRep_CallID)
    ERoleSelectCallID   CallID = ERoleSelectCallID::ERSCID_None;

    //-------------------------------------------------------------
    //-------------------------------------------------------------
    /**
     *  サーバーからクライアントに送るデータ（ここまで）
     */


};
