// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Unit/UnitData.h"
#include "Unit/UnitAnimInstance.h"
#include "Unit/UnitModel.h"
#include "Unit/Interface/UnitAnimationInterface.h"
#include "Unit.generated.h"




UCLASS(Blueprintable)

class COLOSSEUM_API AUnit : public AActor, public IUnitAnimationInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    //  ユニットデータの設定
    void SetUnitData(const FUnitData& UnitData);

    //  ユニットデータから作成
    void CreateUnitData();

    //  ユニットデータの取得
    FUnitData& GetUnitData();

    // 回転設定
    void Set3DRotation(const FRotator& rotation);

    // 回転取得
    FRotator Get3DRotation() const;

    // 位置設定
    void Set3DLocation(const FVector& location);

    // 位置取得
    FVector Get3DLocation() const;

    // 表示非表示設定
    void SetVisible(bool flag);

    //  表示されているか
    bool IsVisible() const;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent; // スケルタルメッシュのコンポーネント

public:
    // アニメーション
    virtual  void PlayAnimationWait(float ShiftTime = SHIFT_ANIME_TIME) override;
    virtual  void PlayAnimationMove(float ShiftTime = SHIFT_ANIME_TIME) override;
    virtual  void PlayAnimationAttack(float ShiftTime = SHIFT_ANIME_TIME) override;
    virtual  void PlayAnimationDamage(float ShiftTime = SHIFT_ANIME_TIME) override;
    virtual  void PlayAnimationDeath(float ShiftTime = SHIFT_ANIME_TIME) override;
    virtual  void PlayAnimationGuard(float ShiftTime = SHIFT_ANIME_TIME) override;
    virtual  void PlayAnimationSkillAttack(float ShiftTime = SHIFT_ANIME_TIME) override;
    virtual  void PlayAnimationBuf(float ShiftTime = SHIFT_ANIME_TIME) override;


    bool IsEndOfAnime() const;


private:
    FUnitData UnitBaseData; // ユニットデータ
    UPROPERTY(Transient)
    TObjectPtr<USkeletalMeshComponent> UnitMesh; //  スケルタルメッシュ

    UPROPERTY(Transient)
    TObjectPtr<AUnitModel> UnitModel; // ユニットモデル

    UPROPERTY(Transient)
    TObjectPtr<UUnitAnimInstance> UnitAnimInstanceObject = nullptr; // ユニットアニメーションインスタンスオブジェクト
};
