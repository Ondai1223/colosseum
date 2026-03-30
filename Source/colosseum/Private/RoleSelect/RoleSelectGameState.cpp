// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleSelect/RoleSelectGameState.h"
#include "RoleSelect/RoleSelectPlayerState.h"




void ARoleSelectGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ARoleSelectGameState, NegotiationMessageServer);
    DOREPLIFETIME(ARoleSelectGameState, NegotiationMessageClient);
}

void ARoleSelectGameState::SyncNegotiationMessage_Implementation( const FString& Message)
{
    ;
}
/**
 * ロールセレクトのゲームステート
 */
bool ARoleSelectGameState::IsCheckPlayerController(int CheckIndex) const
{
    int Index = 0;
    {
        for (TArray<TObjectPtr<APlayerState>>::TConstIterator It(PlayerArray); It; ++It)
        {
            TObjectPtr<APlayerState> pps = *It;
            ARoleSelectPlayerState* rps = Cast<ARoleSelectPlayerState>(pps.Get());
            if (rps != nullptr)
            {

                APlayerController* Ctrl = rps->GetPlayerController();

                if (Ctrl != nullptr)
                {
                    ++Index;
                }
            }
        }
    }
    return Index >= CheckIndex;
}

bool ARoleSelectGameState::IsCheckPlayerState(int CheckIndex ) const
{
    int Index = 0;

    {
        for (TArray<TObjectPtr<APlayerState>>::TConstIterator It(PlayerArray); It; ++It)
        {
            TObjectPtr<APlayerState> pps = *It;
            ARoleSelectPlayerState* rps = Cast<ARoleSelectPlayerState>(pps.Get());
            if (rps != nullptr)
            {
                ++Index;
            }
        }
    }
    return Index >= CheckIndex;
}


int ARoleSelectGameState::GetPlayerNum(ABattleController* controller) const
{
    if (!controller)
    {
        return -1;
    }
    UWorld* World = GetWorld();
    if (!World)
    {
        return -1;
    }
    for (TArray<TObjectPtr<APlayerState>>::TConstIterator It(PlayerArray); It; ++It)
    {
        TObjectPtr<APlayerState> pps = *It;
        ARoleSelectPlayerState* rps = Cast<ARoleSelectPlayerState>(pps.Get());
        if (rps != nullptr)
        {
            APlayerController* Ctrl = rps->GetPlayerController();
            if (Ctrl == controller)
            {

                int idx = It.GetIndex();
                if (Ctrl->HasAuthority())
                {
                    UE_LOG(LogTemp, Warning, TEXT("【Server】 : %d"),idx);
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("【Client】 : %d"),idx);
                }

                return idx;
            }
        }
    }
    return -1;

}

//  文字列比較
bool ARoleSelectGameState::CompereString(const FString& StrLeft, const FString& StrRight) const
{
    return StrLeft == StrRight;
}




