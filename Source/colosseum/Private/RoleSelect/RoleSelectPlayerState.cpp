// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleSelect/RoleSelectPlayerState.h"
#include "Engine/World.h"
#include "GameFramework/GameStateBase.h"
/**
 *  プレーヤーロール選択ステート
 */



//  プレイヤー番号の取得
int ARoleSelectPlayerState::GetPlayerNo() const
{
    UWorld* World = GetWorld();
    if (World)
    {
        TArray<TObjectPtr<APlayerState>>& PlayerArray = World->GetGameState()->PlayerArray;

        for (TArray<TObjectPtr<APlayerState>>::TConstIterator It(PlayerArray); It; ++It)
        {
            TObjectPtr<APlayerState> pps = *It;
            ARoleSelectPlayerState* rps = Cast<ARoleSelectPlayerState>(pps.Get());
            if (rps == this)
            {
                return It.GetIndex();
            }
        }
    }
    return -1;
}


void ARoleSelectPlayerState::TickProc(URoleSelectPage* page , ABattleController* BattleController, float DT)
{
    if (!page || !BattleController)
    {
        return;
    }


    page->TickSlotProc(BattleController, DT);

}
