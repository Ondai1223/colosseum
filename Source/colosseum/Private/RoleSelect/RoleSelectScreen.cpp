// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleSelect/RoleSelectScreen.h"
#include "Camera/CameraComponent.h"
/**
 * ロールセレクト画面
 */

// Sets default values
ARoleSelectScreen::ARoleSelectScreen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoleSelectScreen::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoleSelectScreen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

