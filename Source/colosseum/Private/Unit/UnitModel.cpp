// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/UnitModel.h"
#include "Unit/Unit.h"
/**
 *  ユニットモデル基底クラスユニットモデル
 */


// Sets default values
AUnitModel::AUnitModel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnitModel::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AUnitModel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUnitModel::OnAttackRunEvent_Implementation()
{
    //  処理なし
}


void AUnitModel::OnDamageRunEvent_Implementation()
{
    //  処理無し
}

void AUnitModel::OnDownRunEvent_Implementation()
{
    //  処理無し
}

void AUnitModel::OnSkillAttackRunEvent_Implementation()
{
    //  処理無し
}

//  バフ
void AUnitModel::OnBufRunEvent_Implementation()
{
}


void AUnitModel::ClearEndOfAnime()
{
    EndOfAnime = false;
}

void AUnitModel::SetEndOfAnime()
{
    EndOfAnime = true;
}


bool AUnitModel::IsEndOfAnime() const
{
    return EndOfAnime;
}

void AUnitModel::SetVisible(bool visible )
{
    if (MasterUnit)
    {
        MasterUnit->SetVisible(visible);
    }
}

void AUnitModel::SetMasterUnit(TObjectPtr<AUnit> Unit)
{
    MasterUnit = Unit;
}

