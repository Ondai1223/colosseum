// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoActionBase.h"
#include "NiagaraFunctionLibrary.h"

void UMasoActionBase::CalcAction(FActionResultData* ActionResult, const uint8 PanelX, const uint8 PanelY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleGameMode* GameMode)
{
}

void UMasoActionBase::ReflectAction(FActionResultData& ActionResult, ABattleGameMode* GameMode)
{
}

void UMasoActionBase::ActionEffect(TObjectPtr<AMasoPanel> MasoPanel)
{
    IsEffected = true;
    TargetPanel = MasoPanel;
    // 魔素効果発動時のIncidenceエフェクト再生
    if (IncidenceNiagaraSystem)
    {
        UE_LOG(LogTemp, Warning, TEXT("発生エフェクトを流す"));
        // NiagaraComponentを取得
        UNiagaraComponent* IncidenceComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
            IncidenceNiagaraSystem,
            MasoPanel->GetRootComponent(),
            NAME_None,
            FVector::ZeroVector,
            FRotator::ZeroRotator,
            FVector::OneVector,
            EAttachLocation::KeepRelativeOffset,
            true,
            ENCPoolMethod::None,
            true,
            true
        );

        GetWorld()->GetTimerManager().SetTimer(
            EffectTimerHandle,
            this,
            &UMasoActionBase::OnIncidenceFinished,
            EffectDuration,
            false
        );

    }
    else
    {
        // 発生エフェクトがない場合は直接メインエフェクトを出す
        UE_LOG(LogTemp, Warning, TEXT("発生エフェクトがないのでメインエフェクト"));
        OnIncidenceFinished();
    }
}

void UMasoActionBase::OnIncidenceFinished()
{
    if (TargetPanel)
    {
        // 魔素効果発動時のMainエフェクト再生
        if (ActionNiagaraSystem)
        {
            // NiagaraComponentを取得
            MasoActionEffect = UNiagaraFunctionLibrary::SpawnSystemAttached(
                ActionNiagaraSystem,
                TargetPanel->GetRootComponent(),
                NAME_None,
                FVector::ZeroVector,
                FRotator::ZeroRotator,
                FVector::OneVector,
                EAttachLocation::KeepRelativeOffset,
                true,
                ENCPoolMethod::None,
                true,
                true
            );
        }
    }
}

void UMasoActionBase::UpdateDuration()
{
    Duration--;
    UE_LOG(LogTemp, Warning, TEXT("魔素アクションの残りターン数: %d"), Duration);

     if (Duration <= 0)
     {
         if (GetWorld())
         {
             GetWorld()->GetTimerManager().ClearTimer(this->EffectTimerHandle);
         }

         if (MasoActionEffect)
         {
             MasoActionEffect->DestroyComponent();
			 MasoActionEffect = nullptr;
             UE_LOG(LogTemp, Warning, TEXT("Effect Destroyed!"));
         }
	 }
}

 EActionType UMasoActionBase::GetActionType()
{
	// 通常型か速攻型か.
	 return EActionType::EAT_Normal;
}

 float UMasoActionBase::GetActionTime()
 {
	 return 0.0f;
 }
