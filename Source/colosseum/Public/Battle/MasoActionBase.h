// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Battle/MasoPanel.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "Battle/UnitBattleParameter.h"
#include "Battle/ActionResultData.h"
#include "Battle/BuffDebuffBase.h"
#include "Battle/BuffAttack.h"
#include "Battle/BuffDefense.h"
#include "Battle/BuffMove.h"
#include "Battle/DebuffAttack.h"
#include "Battle/DebuffDefense.h"
#include "Battle/DebuffMove.h"
#include "MasoActionBase.generated.h"

UENUM()
enum class EActionType : uint8
{
	EAT_Normal     UMETA(DisplayName = "í èÌå^"), // 1É^Å[Éìå„Ç…î≠ìÆ
	EAT_Immediate  UMETA(DisplayName = "ë¨çUå^") // ë¶éûî≠ìÆ
};
/**
 * 
 */
UCLASS()
class COLOSSEUM_API UMasoActionBase : public UObject
{
	GENERATED_BODY()

public:

	virtual void CalcAction(FActionResultData* ActionResult, const uint8 PanelX, const uint8 PanelY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode);

	virtual void ReflectAction(FActionResultData& ActionResult, ABattleGameMode* GameMode);

	virtual void ActionEffect(TObjectPtr<AMasoPanel> MasoPanel);
	
	virtual EActionType GetActionType();

	virtual float GetActionTime();

	UFUNCTION()
	void OnIncidenceFinished();

	void UpdateDuration();

	int32 GetDuration() const { return Duration; }
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsEffected = false; // ñÇëfå¯â Ç™î≠ìÆÇµÇƒÇ¢ÇÈÇ©Ç«Ç§Ç©ÇÃÉtÉâÉO
protected:

	UPROPERTY(Transient)
	TObjectPtr<UNiagaraSystem> ActionNiagaraSystem;

	UPROPERTY(Transient)
	TObjectPtr<UNiagaraSystem> IncidenceNiagaraSystem;

	UPROPERTY(Transient)
	TObjectPtr<UNiagaraComponent> MasoActionEffect;

	UPROPERTY(Transient)
	TObjectPtr<class AMasoPanel> TargetPanel;

	FTimerHandle EffectTimerHandle;

	float EffectDuration = 0.0f;

	int32 Duration = 0;
};
