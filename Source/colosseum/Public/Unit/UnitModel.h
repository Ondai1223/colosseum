// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnitModel.generated.h"

/**
 *  ���j�b�g���f�����N���X���j�b�g���f��
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

    //  �U���C�x���g
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_UnitAnime)
    void OnAttackRunEvent();
    virtual void OnAttackRunEvent_Implementation();

    //  �_���[�W�C�x���g
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_UnitAnime)
    void OnDamageRunEvent();
    virtual void OnDamageRunEvent_Implementation();

    //  �_�E���C�x���g
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_UnitAnime)
    void OnDownRunEvent();
    virtual void OnDownRunEvent_Implementation();

    //  �X�L���A�^�b�N
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_UnitAnime)
    void OnSkillAttackRunEvent();
    virtual void OnSkillAttackRunEvent_Implementation();

    //  �o�t
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
    TObjectPtr<AUnit> MasterUnit; // �X�P���^�����b�V���̃R���|�[�l���g


};
