// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Battle/MasoPanel.h"
#include "Battle/MasoActionBase.h"
#include "NiagaraSystem.h"
#include "MasoManager.generated.h"

class ABattleGameMode; // 前方宣言
UCLASS()
class COLOSSEUM_API AMasoManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasoManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//  魔素パネルを見つけて配置する
	UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
	void SearchMasoPanelFromWorld();

	// 魔素登録
	void JoinMaso(int X, int Y, FName Type, TObjectPtr<AUnitBattleParameter> ActionUnit, ABattleGameMode* GameMode);

	// パネルの色変更
	void ChangeMasoPanelMaterial(TObjectPtr<AMasoPanel> MasoPanel, int MasoPanelNum, bool join);
	
	// Player1の魔素パネルのターン更新
	void UpdatePlayer1Maso();
	
	// Player2の魔素パネルのターン更新
	void UpdatePlayer2Maso();

	// Player1の魔素パネルの通常型の魔素チェック
	void ResolvePlayer1PendingMasoActions(ABattleGameMode* GameMode);

	// Player2の魔素パネルの通常型の魔素チェック
	void ResolvePlayer2PendingMasoActions(ABattleGameMode* GameMode);

	// ターン更新の際に行う処理をまとめたもの
	void UpdateTurnMasoActions();

	// MasoPanelが発動中かチェックする関数.
	bool AbleJoin(TObjectPtr<AMasoPanel> MasoPanel);

	// 魔素の組み合わせで魔素効果発動クラスを作成.
	bool GetCombinedMasoElements(FMasoPanelData* maso1, FMasoPanelData* maso2);

	// 魔素効果発動.
	void ActivateMasoAction(TObjectPtr<AMasoPanel> MasoPanel, ABattleGameMode* GameMode);

	// 魔素効果エフェクトの消滅
	void DeactivateMasoAction(TObjectPtr<AMasoPanel> MasoPanel);

	// 魔素効果のエフェクト発生
	UFUNCTION(BlueprintCallable, Category = CATEGORY_Maso)
	void MasoActionEffect(UMasoActionBase* MasoAction);

	// 魔素効果の計算
	UFUNCTION(BlueprintCallable, Category = CATEGORY_Maso)
	void MasoActionCalculate(UMasoActionBase* MasoAction);

	// 魔素効果エフェクトの時間取得
	UFUNCTION(BlueprintCallable, Category = CATEGORY_Maso)
	float GetMasoActionTime(UMasoActionBase* MasoAction);

	// 魔素データの初期化.
	UFUNCTION(BlueprintCallable, Category = CATEGORY_Maso)
	void ResetMasoPanel();

	void CreateNiagaraComponent(TObjectPtr<UNiagaraSystem> MasoPanelNiagaraSystem, UStaticMeshComponent* component, int PanelSideIndex);

	//  アクションリザルトの初期化
	void ClearActionResult();

	bool IsMasoActionActive();

	// 魔素効果エフェクトと計算処理を始めるイベントノード
	UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Maso)
	void OnMasoAction(UMasoActionBase* LaunchedAction);
	virtual void OnMasoAction_Implementation(UMasoActionBase* LaunchedAction);


protected:
	UPROPERTY(Transient)
	ABattleGameMode* MasoGameMode;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMasoActionBase> CurrentMasoAction; // 発動効果格納先

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UMasoActionBase>> MasoActionList; // バトルにある魔素アクションの管理リスト
private:
	UPROPERTY(Transient)
	TArray<TObjectPtr<AMasoPanel>> MasoPanelArray; //魔素パネルの配列

	UPROPERTY(Transient)
	TArray<TObjectPtr<AMasoPanel>> Player1MasoPanel; //プレイヤー１のパネル配列

	UPROPERTY(Transient)
	TArray<TObjectPtr<AMasoPanel>> Player2MasoPanel; //プレイヤー２のパネル配列

	UPROPERTY(Transient)
	TObjectPtr<UNiagaraComponent> MasoPanelEffectComponent;
	
	UPROPERTY(Transient)
	TObjectPtr<AMasoPanel> ActionPanel;

	UPROPERTY(Transient)
	TObjectPtr<AUnitBattleParameter> JointedUnit;

	FActionResultData ActionResult;
	
	bool bIsMasoActionActive; // 魔素効果が発動中かどうかのフラグ
};
