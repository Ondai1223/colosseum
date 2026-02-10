// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoleSelecter.generated.h"

UCLASS()
class COLOSSEUM_API ARoleSelecter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoleSelecter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void Startup();


    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    float CalcLerp();

    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    bool IsEnd() const;

    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void SetMaxTime(float Time);

    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void AddDT(float DT);
public:
    float NowTime = 0.0f;
    float MaxTime = 1.0f;
};
