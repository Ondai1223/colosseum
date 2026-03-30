// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoleSelect/RoleSelectDefines.h"
#include "RoleSelect/RoleUnitSlot.h"
#include "Battle/BattleController.h"
#include "RoleSelect/RoleSelectENums.h"

#include "RoleSelectPage.generated.h"

class ARoleSelecter;
class ARoleSelectScreen;
class ARoleSelecter;
class ARoleArrangementUnitStage;
class ARoleSelectPlayerState;
class AUnit;
/**
 * ロールセレクトページ
 */
UCLASS()
class COLOSSEUM_API URoleSelectPage : public UUserWidget
{
	GENERATED_BODY()



public:
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
    void SetupTeam(EUnitTeamID Team_id);
    virtual void SetupTeam_Implementation(EUnitTeamID Team_id);

    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
    void FaceSetup();
    virtual void FaceSetup_Implementation();


    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
    void PageSetup();
    virtual void PageSetup_Implementation();

    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
    void ArrangementSetup();
    virtual void ArrangementSetup_Implementation();

    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
    void ArrangementClose();
    virtual void ArrangementClose_Implementation();

    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
    void RoleSelecterOpen();
    virtual void RoleSelecterOpen_Implementation();

    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
    void RoleSelecterClose();
    virtual void RoleSelecterClose_Implementation();

    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
    void RoleSelecterDark();
    virtual void RoleSelecterDark_Implementation();

    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
    void RoleSelecterNormal();
    virtual void RoleSelecterNormal_Implementation();

    //  次のスロットへ
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
    void NextSlot();
    virtual void NextSlot_Implementation();

    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
    void SetSlotIndex(int SlotIndex);
    virtual void SetSlotIndex_Implementation(int SlotIndex);



    //  一つ前のスロットへ
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
    void PrevSlot();
    virtual void PrevSlot_Implementation();


    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
    void SetPlayerTeamName(const FString& TeamName);
    virtual void SetPlayerTeamName_Implementation(const FString& TeamName);

    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
    void ActiveSlot();
    virtual void ActiveSlot_Implementation();

    //  出撃可能な通知
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
    void GetReady();
    virtual void GetReady_Implementation();

    //  任意のジョブにカーソルを合わせる
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
    void SetRoleNameInfoFromJobID(EUnitJob jobID);
    virtual void SetRoleNameInfoFromJobID_Implementation(EUnitJob jobID);

public:
    //  チームIDの設定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void SetTeamID(EUnitTeamID Team_ID);

    //  ロールユニットスロット追加
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void SetupRoleUnitSlotsAdd(UCharaFace* CharaFace);

    //  スタートアップ

    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void Startup(int SlotNo = 0);

    //  選択クリア
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void ClearSelectCursor();

    //  スロットカーソル設定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void SetSlotCursor( int SlotNo );

    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void TickSlotProc(ARoleSelectPlayerState* PlayerState, ABattleController* BC, float DT);

    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void TickSlotNetWorkProc(ARoleSelectPlayerState* PlayerState, float DT);

    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void TickSlotNPCProc(ARoleSelectPlayerState* PlayerState, float DT);



    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void ClearRoleSelectArrow();

    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void SetRoleSelectArrow();


    //  ロールセレクタの作成
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void CreateRoleSelecter();


    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void CreateRoleArrangementUnitStage();


    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    int GetRoleSelectCursorIndex(EUnitJob job) const;

    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void SetRoleSelectCursorPosition(EUnitJob job,ARoleSelectPlayerState* PlayerState = nullptr);


    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    EUnitJob GetRoleSelectFromCursorIndex() const;

    //  ジョブ名の取得
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    const FString& GetJobNameFromID(EUnitJob jobID) const;

    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void CreateRoleSelectGph();

    //  任意のジョブのクォータニオン取得
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    FQuat GetRolequat(EUnitJob job) const;

    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void CalcRoleLoop();

    //  以下ステートの変更
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void ChangeState_Selecting(ARoleSelectPlayerState* PlayerState,bool NotSendCommand = false);


    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void ChangeState_SelectingNext(ARoleSelectPlayerState* PlayerState, bool NotSendCommand = false);


    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    bool ChangeState_BeforeSlot(ARoleSelectPlayerState* PlayerState,bool NotSendCommand = false);

    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void ChangeState_RoleSelectingToNone(ARoleSelectPlayerState* PlayerState, bool NotSendCommand = false);


    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void ChangeState_ToArrangement(ARoleSelectPlayerState* PlayerState, bool NotSendCommand = false);

    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void ChangeState_PositionSet(ARoleSelectPlayerState* PlayerState, bool NotSendCommand = false);

    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void ChangeState_ReadyWait(ARoleSelectPlayerState* PlayerState, bool NotSendCommand = false);

    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void ChangeState_SelectPositionCansel(ARoleSelectPlayerState* PlayerState, bool NotSendCommand = false);

#if 0
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void ChangeState_ArrangementCansel(ARoleSelectPlayerState* PlayerState, bool Client = false);
#endif
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void ChangeState_ReadyCansel(ARoleSelectPlayerState* PlayerState, bool Client = false);





public:
    //  ロールユニットスロットの取得
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    TArray<TObjectPtr<ARoleUnitSlot>> RoleUnitSlots;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    EUnitTeamID TeamID = EUnitTeamID::EUTID_None;


    UPROPERTY()
    ERpoleSelectSlotState   SlotState = ERpoleSelectSlotState::ERSSS_None;


    //  ロールカーソル
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    int RoleSelectIndex = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    bool Arrow = true;


    //  顔グラ
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    TArray<TObjectPtr<UCharaFace>>  RoleSelectCharFace;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    TObjectPtr<ARoleSelecter>   RoleSelecter;



    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    TObjectPtr<ARoleArrangementUnitStage>   RoleArrangementUnitStage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    TObjectPtr<ARoleSelectScreen>   RoleSelectScreen;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    EUnitJob SelectedJob = EUnitJob::EUJ_Tank;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    EUnitJob SelecteBeforedJob = EUnitJob::EUJ_Tank;


};
