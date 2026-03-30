// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RoleSelect/RoleSelectPlayerState.h"
#include "RoleSelectNPCState.generated.h"

/**
 * ロールセレクトNPCステート
 */

UCLASS()
class COLOSSEUM_API ARoleSelectNPCState : public ARoleSelectPlayerState
{
	GENERATED_BODY()
	


public:

    virtual void TickProc(URoleSelectPage* page, float DT);

};
