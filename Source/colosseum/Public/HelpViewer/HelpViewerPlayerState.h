// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "HelpViewer/HelpViewerDefine.h"
#include "HelpViewerPlayerState.generated.h"

/**
 * ヘルプのプレーヤーステート
 */
UCLASS()
class COLOSSEUM_API AHelpViewerPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
    //--------------------------------------------------------------------
//  機能
    UFUNCTION(BlueprintCallable, Category = CATEGORY_HelpViewer)
    void CtrlCursorPosition(float DT);
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_HelpViewer)
    int Cursor = 0;

    UPROPERTY()
    float CursorWait = HELPVIEWER_CURSOR_WAIT;


};
