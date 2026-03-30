// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Unit/UnitTeamID.h"
#include "NiagaraSystem.h"
#include "Unit/Unit.h"
#include "RoleSelect/RoleSelectENums.h"
#include "Battle/BattleController.h"
#include "RoleArrangementUnitStage.generated.h"



class ARoleSelectPlayerState;

UCLASS(BlueprintType)
class COLOSSEUM_API ARoleArrangementUnitStage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoleArrangementUnitStage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;






public:
    //  カーソルモデルの作成
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void CreateCursorModel();

    //  予めユニットを全部ロードしておく
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void CreateUnitModel();

    void CreateUnitModel(EUnitJob job, TArray<TObjectPtr<AUnit>>& UnitArray,int Num);

    //  ユニット配置済み数を調べる
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    int CalcNumArrangementUnit();
    int CalcNumArrangementUnit(const TArray<TObjectPtr<AUnit>>& Units) const;

    //  ユニット配置セットアップ
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void ArrangementUnitSetup(EUnitJob Job,int Slot = 0);

    //ユニットがいない場所を検索して返す。(または、推奨される位置)
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    bool SearchEmptyPosition(int& X, int& Y) const;
    bool SearchEmptyPosition(int X, int Y , const TArray<TObjectPtr<AUnit>>& Units , const TObjectPtr<AUnit>& SkipUnit) const;


//    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    TObjectPtr<AUnit> SearchUnitFromPosition(int X, int Y);
    TObjectPtr<AUnit> SearchUnitFromPosition(int X, int Y,TArray<TObjectPtr<AUnit>>& Units , bool visible = true);


    //  ユニット3D座標取得
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    FVector CalcUnitLocation(int X, int Y) const;


    //  最後に配置したユニットのジョブを取得
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    EUnitJob GetLastArrangementUnitJob() const;



    void VisibleArrangementUnit();

    void ClearArrangementUnit(TArray<TObjectPtr<AUnit>>& Units);
    //  ロード済みユニットをすべて非表示にする
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void ClearArrangementUnit();


    //  ユニット配置
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void TickArrangementUnit(float DeltaTime, ABattleController* Controller,ARoleSelectPlayerState* PlayerState);



    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void CalcUnitPosition();



    TObjectPtr<AUnit> GetSelectUnit(EUnitJob Job) const;


    void BeginArrangementUnitStage();

public:
    //　ステータス
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    EAUState    StartPositionState = EAUState::EAUState_None;


    //  ネゴシエーション完了待ちしたあとに飛ぶステータス
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    EAUState    EventNextState = EAUState::EAUState_None;

    //  ユニットジョブの設定
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    EUnitJob    JobID = EUnitJob::EUJ_None;


    //  選択ユニット
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    TObjectPtr<AUnit>   SelectUnit;

    //  ユニットデータ
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    TArray<FUnitData>   ResultUnitDatas;

    //  スロット番号
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    int SlotNo = 0;



public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    EUnitTeamID TeamID = EUnitTeamID::EUTID_None;

    UPROPERTY(Transient)
    TObjectPtr<UStaticMeshComponent> CursorModel; // ユニットのメッシュコンポーネント

    UPROPERTY(Transient)
    TObjectPtr<UNiagaraComponent> CursorEffectComponent;

    UPROPERTY(Transient)
    TObjectPtr<UNiagaraSystem> CursorNiagaraSystem;

    //  タンクユニット
    UPROPERTY(Transient)
    TArray<TObjectPtr<AUnit>>   TankUnits;

    //  ラウンダー
    UPROPERTY(Transient)
    TArray<TObjectPtr<AUnit>>   RaunderUnits;

    // マジシャン
    UPROPERTY(Transient)
    TArray<TObjectPtr<AUnit>>   MagicianUnits;

    // ヒーラー
    UPROPERTY(Transient)
    TArray<TObjectPtr<AUnit>>   HealerUnits;


    //  ユニットカーソル位置
    struct {
        int X = 1;
        int Y = 0;
    }UnitPosition;

    //  カーソル動かすウエイト
    float NowTime = 0.0f;
    float MaxTime = 0.5f;

};
