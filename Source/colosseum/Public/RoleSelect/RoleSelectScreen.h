// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraActor.h"
#include "RoleSelectScreen.generated.h"

/**
 * ロールセレクト画面
 */

class UCameraComponent;

UCLASS()
class COLOSSEUM_API ARoleSelectScreen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoleSelectScreen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
    TObjectPtr<UCameraComponent>   RoleSelectCamera;
};
