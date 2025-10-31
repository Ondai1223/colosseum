// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnitModel.generated.h"

/**
 *  ユニットモデル基底クラスユニットモデル
 */
class AUnit;
UCLASS()
class COLOSSEUM_API AUnitModel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnitModel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

    //  攻撃イベント
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_UnitAnime)
    void OnAttackRunEvent();
    virtual void OnAttackRunEvent_Implementation();

    //  ダメージイベント
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_UnitAnime)
    void OnDamageRunEvent();
    virtual void OnDamageRunEvent_Implementation();

    //  ダウンイベント
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_UnitAnime)
    void OnDownRunEvent();
    virtual void OnDownRunEvent_Implementation();

    //  スキルアタック
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_UnitAnime)
    void OnSkillAttackRunEvent();
    virtual void OnSkillAttackRunEvent_Implementation();

    //  バフ
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_UnitAnime)
    void OnBufRunEvent();
    virtual void OnBufRunEvent_Implementation();


public:

    UFUNCTION(BlueprintCallable, Category = CATEGORY_UnitAnime)
    void ClearEndOfAnime();

    UFUNCTION(BlueprintCallable, Category = CATEGORY_UnitAnime)
    void SetEndOfAnime();

    UFUNCTION(BlueprintCallable, Category = CATEGORY_UnitAnime)
    bool IsEndOfAnime() const;

    UFUNCTION(BlueprintCallable, Category = CATEGORY_UnitAnime)
    void SetVisible(bool visible = true);

public:
    void SetMasterUnit(TObjectPtr<AUnit> Unit);

private:
    bool EndOfAnime = false;

    UPROPERTY(Transient)
    TObjectPtr<AUnit> MasterUnit; // スケルタルメッシュのコンポーネント


};
