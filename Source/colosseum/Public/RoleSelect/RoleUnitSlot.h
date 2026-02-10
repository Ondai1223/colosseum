// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RoleSelect/RoleSelectDefines.h"
#include "Unit/UnitJob.h"
#include "Common/CharaFace.h"
#include "RoleUnitSlot.generated.h"


class URoleSelectPage;
class ABattleController;
/**
 * ロールユニットスロット
 */

UCLASS()
class COLOSSEUM_API ARoleUnitSlot : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARoleUnitSlot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
    //  選択開始
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
    void BeginSlotSelected(URoleSelectPage* Page, ABattleController* BattleController);
    virtual void BeginSlotSelected_Implementation(URoleSelectPage* Page, ABattleController* BattleController);

    //  ただ今選択中(false : 継続 true : 終了)
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_RoleSelect)
    bool TickSlotSelected(float DeltaSecounds);
    virtual bool TickSlotSelected_Implementation(float DeltaSecounds);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    //  キャラクタの顔変更
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void ChangeFace();

    //  ジョブID
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void SetJobID(EUnitJob InJobID);

    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    EUnitJob GetJobID() const;

    //  チームIDの設定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void SetTeamID(EUnitTeamID InTeamID);

    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    EUnitTeamID GetTeamID()const;

    //  選択の設定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void SetSelected(bool flag);

public:
    //  キャラクタの顔
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_RoleSelect)
    TObjectPtr<UCharaFace> CharaFace;


protected:
    TObjectPtr<ABattleController>   Controller;
    TObjectPtr<URoleSelectPage>   SelectedPage;


};
