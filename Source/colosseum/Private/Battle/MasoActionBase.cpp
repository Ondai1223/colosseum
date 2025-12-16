// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/MasoActionBase.h"
#include "NiagaraFunctionLibrary.h"

void UMasoActionBase::ApplyAction()
{
	// 魔素効果の中身を書く
}

void UMasoActionBase::ActionEffect(TObjectPtr<AMasoPanel> MasoPanel)
{
	// 魔素効果発動時のエフェクト再生
    if (ActionNiagaraSystem)
    {
        // NiagaraComponentを取得
        MasoActionEffect = UNiagaraFunctionLibrary::SpawnSystemAttached(
            ActionNiagaraSystem,
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
    }
}

 EActionType UMasoActionBase::GetActionType()
{
	// 通常型か速攻型か.
	 return EActionType::EAT_Normal;
}
