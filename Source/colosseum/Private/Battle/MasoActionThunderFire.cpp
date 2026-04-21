// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoActionThunderFire.h"
#include "Battle/BattleGameMode.h"

#define NS_Incidence TEXT("/Game/FixEffect/miyaryu/NS/F+T/F+T_incidence.F+T_incidence")
#define NS_Main TEXT("/Game/FixEffect/miyaryu/NS/F+T/F+T.F+T")

#define IncidentEffectTime 2.0f
#define TotalEffectTime 3.0f

#define Thunder_Fire_Base 0.2f
UMasoActionThunderFire::UMasoActionThunderFire()
{   
	IncidenceNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, NS_Incidence);
	ActionNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, NS_Main);
	Duration = 2;
	EffectDuration = IncidentEffectTime;
}

void UMasoActionThunderFire::CalcAction(FActionResultData* ActionResult, const uint8 PanelX, const uint8 PanelY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode)
{
	// 計算
    ActionResult->ActionUnit = ActionUnit;

    TObjectPtr Target = GameMode->GetUnit(PanelX, PanelY);
    UE_LOG(LogTemp, Warning, TEXT("UMasoActionFireFire::CalcAction is called(%d, %d)"), PanelX, PanelY);
    if (Target)
    {
        FActionAttackTargetData TargetData;
        TargetData.TargetUnit = Target;
        // FActionTargetAndLocationへの情報格納
        FActionTargetAndLocation TargetLocation;
        TargetLocation.Location.X = PanelX;
        TargetLocation.Location.Y = PanelY;
        TargetLocation.Target = Target;

        ActionResult->ActionAttackResult.AttackTargets.Add(TargetData);
    }
}

void UMasoActionThunderFire::ReflectAction(FActionResultData& ActionResult, ABattleGameMode* GameMode)
{
    for (TArray<FActionAttackTargetData>::TIterator Ite(ActionResult.ActionAttackResult.AttackTargets); Ite; ++Ite)
    {
        // デバフの付与
        UBuffDebuffBase* Debuff;
		Debuff = NewObject<UDebuffDefense>(Ite->TargetUnit);
        Debuff->Init(2, Thunder_Fire_Base, Ite->TargetUnit->Get3DLocation());
        Ite->TargetUnit->AddBuffDebuff(Debuff);
	}
}

void UMasoActionThunderFire::ActionEffect(TObjectPtr<AMasoPanel> MasoPanel)
{
	UE_LOG(LogTemp, Warning, TEXT("火山灰と雷のエフェクト"));
	Super::ActionEffect(MasoPanel);
}

float UMasoActionThunderFire::GetActionTime()
{
	return TotalEffectTime;
}

EActionType UMasoActionThunderFire::GetActionType()
{
	return EActionType::EAT_Immediate;
}