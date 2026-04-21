// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Unit/UnitData.h"
#include "Unit/UnitAnimInstance.h"
#include "Unit/UnitModel.h"
#include "Unit/Interface/UnitAnimationInterface.h"
#include "Unit/Interface/UnitFaceInterface.h"
#include "Unit.generated.h"




UCLASS(Blueprintable)

class COLOSSEUM_API AUnit : public AActor, public IUnitAnimationInterface, public IUnitFaceInterface
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

    // スケール設定
    void Set3DScale(const FVector& scale);

    // 回転設定
    void Set3DRotation(const FRotator& rotation);

    // 回転取得
    FRotator Get3DRotation() const;

    // クォータニオン取得
    FQuat GetQuaternion() const;

    //  クォータニオン設定
    void SetQuaternion(const FQuat& quat);

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

public:


    //  任意の表情に変更
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Unit)
    virtual void ChangeUnitFace(EUnitFace FaceID) override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Unit)
    FVector2D UnitFaceUV = FVector2D::ZeroVector; //  ユニット表情UV

public:
	TObjectPtr<AUnitModel> GetUnitModel() const { return UnitModel; }

private:
    FUnitData UnitBaseData; // ユニットデータ
    UPROPERTY(Transient)
    TObjectPtr<USkeletalMeshComponent> UnitMesh; //  スケルタルメッシュ

    UPROPERTY(Transient)
    TObjectPtr<AUnitModel> UnitModel; // ユニットモデル

    UPROPERTY(Transient)
    TObjectPtr<UUnitAnimInstance> UnitAnimInstanceObject = nullptr; // ユニットアニメーションインスタンスオブジェクト

    UPROPERTY(Transient)
    TObjectPtr<UMaterialInstanceDynamic> FaceMaterialInstance;   // 顔のマテリアルインスタンス(nullptrの場合もある)



};
