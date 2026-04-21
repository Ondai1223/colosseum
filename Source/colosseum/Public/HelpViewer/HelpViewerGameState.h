// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HelpViewer/HelpViewerDefine.h"
#include "GameFramework/GameStateBase.h"
#include "HelpViewerGameState.generated.h"

/**
 * ヘルプのゲームステート
 */

UCLASS(Blueprintable)
class COLOSSEUM_API AHelpViewerGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:


    //----------------------------------------------------------------------
    //  ヘルプビューアーを閉じる
    //  これを呼んでから Opened == false でクローズアニメーション終了
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_HelpViewer)
    void CloseHelpViewer();
    virtual void CloseHelpViewer_Implementation();

    //----------------------------------------------------------------------
    //  ヘルプビューアーを閉じる
    //  これを呼んでから Opened == false でクローズアニメーション終了
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_HelpViewer)
    void SetHelpTitle(const FString& Title, int TitleNo = 0);
    virtual void SetHelpTitle_Implementation(const FString& Title, int TitleNo = 0);

    //----------------------------------------------------------------------
    //  ヘルプビューアーを閉じる
    //  これを呼んでから Opened == false でクローズアニメーション終了
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_HelpViewer)
    void SetCursorPosition(int Position);
    virtual void SetCursorPosition_Implementation(int Position);

public:


public:
    //  ヘルプビューアーが開いているか
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_HelpViewer)
    bool Opened = false;


};
