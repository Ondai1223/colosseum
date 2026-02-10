// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleSelect/RoleSelecter.h"

// Sets default values
ARoleSelecter::ARoleSelecter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoleSelecter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoleSelecter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ARoleSelecter::Startup()
{
    NowTime = 0.0f;
}


float ARoleSelecter::CalcLerp()
{
    return NowTime / MaxTime;
}

bool ARoleSelecter::IsEnd() const
{
    return NowTime >= MaxTime;
}

void ARoleSelecter::SetMaxTime(float Time)
{
    MaxTime = Time;
}

void ARoleSelecter::AddDT(float DT)
{
    NowTime = FMath::Min(NowTime + DT, MaxTime);
}
