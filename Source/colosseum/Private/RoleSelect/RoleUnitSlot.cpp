// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleSelect/RoleUnitSlot.h"

/**
 * ロールユニットスロット
 */
 




 // Sets default values
ARoleUnitSlot::ARoleUnitSlot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoleUnitSlot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoleUnitSlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARoleUnitSlot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

//  
void ARoleUnitSlot::BeginSlotSelected_Implementation(URoleSelectPage* RolePage, ABattleController* BattleController)
{
    Controller = BattleController;
    SelectedPage = RolePage;
}


bool ARoleUnitSlot::TickSlotSelected_Implementation(float DeltaSecounds)
{
    return false;
}



//  キャラクタの顔変更
void ARoleUnitSlot::ChangeFace()
{
    if (CharaFace)
    {
        CharaFace->ChangeFace();
    }
}

//  ジョブID
void ARoleUnitSlot::SetJobID(EUnitJob InJobID)
{
    if (CharaFace)
    {
        CharaFace->JobFaceID = InJobID;
    }
}

//  ジョブID取得
EUnitJob ARoleUnitSlot::GetJobID() const
{
    if (CharaFace)
    {
        return CharaFace->JobFaceID;
    }
    return EUnitJob::EUJ_None;
}

//  チームID取得 
void ARoleUnitSlot::SetTeamID(EUnitTeamID InTeamID)
{
    if (CharaFace)
    {
        CharaFace->TeamID = InTeamID;
    }
}

//  チームID取得
EUnitTeamID ARoleUnitSlot::GetTeamID() const
{
    if (CharaFace)
    {
        return CharaFace->TeamID;
    }
    return EUnitTeamID::EUTID_None;
}

//  
void ARoleUnitSlot::SetSelected(bool flag)
{
    if (CharaFace)
    {
        CharaFace->SetArrow(flag);
    }

}



