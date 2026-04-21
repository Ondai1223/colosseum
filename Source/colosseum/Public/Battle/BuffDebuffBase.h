// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/Image.h"
#include "NiagaraSystem.h"
#include "BuffDebuffBase.generated.h"

UENUM(BlueprintType)
enum class EBuffDebuffType : uint8
{
	EBT_ATTACK		UMETA(Display = "Attack"),
	EBT_DEFENSE		UMETA(Display = "Defense"),
	EBT_MOVE		UMETA(Display = "Move"),
	EBT_NONE			UMETA(Display = "None"),
};

UENUM(BlueprintType)
enum class EBuffCategory : uint8
{
	Buff    UMETA(DisplayName = "Buff"),
	Debuff  UMETA(DisplayName = "Debuff")
};
/**
 * バフとデバフの基底クラス
 */
UCLASS()
class COLOSSEUM_API UBuffDebuffBase : public UObject
{
	GENERATED_BODY()

public:

	int32 GetDuration() const { return Duration; }

	UTexture2D* GetIcon() const { return BuffDebuffIcon; }

	EBuffDebuffType GetBuffDebuffType() const { return BuffDebuffType; }

	EBuffCategory GetBuffCategory() const { return BuffCategory; }

	/*
		Times: 効果の持続ターン数
		Magnification: 効果の倍率
	*/
	void Init(int32 Times, float Magnification, const FVector& Location);

	virtual float CalcPower(float BasePower);

	void UpdateDuration() { Duration--; }

protected:

	int32 Duration;
	
	UPROPERTY(Transient)
	UTexture2D* BuffDebuffIcon;

	EBuffDebuffType BuffDebuffType;

	float Multiplier;

	UPROPERTY(Transient)
	TObjectPtr<UNiagaraSystem> BuffDebuffSystem;

	EBuffCategory BuffCategory;
};
