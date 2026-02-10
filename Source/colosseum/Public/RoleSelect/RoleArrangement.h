// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoleSelect/RoleSelectDefines.h"
#include "RoleSelect/Interface/RoleArrangementInterface.h"
#include "RoleArrangement.generated.h"

UENUM(BlueprintType)
enum class ETickRoleArrangementState : uint8
{
    ETRAS_Arranging       UMETA(DisplayName = "ロール配置中"),  // ロール配置中
    ETRAS_Animation       UMETA(DisplayName = "アニメーション再生中"),  // アニメーション再生中
    ETRAS_Completed       UMETA(DisplayName = "配置完了"),   // 配置完了
};



UCLASS()
class COLOSSEUM_API ARoleArrangement : public AActor , public IRoleArrangementInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoleArrangement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:



    virtual void BeginRoleArrangement(ARoleSelectGameModeBase* GameMode) override;

    virtual ERoleArrangementState TickRoleArrangement(ARoleSelectGameModeBase* GameMode , ABattleController* Controller ,float DeltaSeconds) override;


public:


    ETickRoleArrangementState   TickState = ETickRoleArrangementState::ETRAS_Arranging;
};
