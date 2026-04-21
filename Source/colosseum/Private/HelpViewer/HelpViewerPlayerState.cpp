// Fill out your copyright notice in the Description page of Project Settings.


#include "HelpViewer/HelpViewerPlayerState.h"
#include "Battle/BattleController.h"
#include "HelpViewer/HelpViewerGameState.h"

/**
 * ヘルプのプレーヤーステート
 */

void AHelpViewerPlayerState::CtrlCursorPosition(float DT)
{
    TObjectPtr<ABattleController> Ctrl = Cast<ABattleController>(GetPlayerController());
    TObjectPtr<AHelpViewerGameState> GameState = Cast<AHelpViewerGameState>(GetWorld()->GetGameState());



    CursorWait = FMath::Min(CursorWait + DT, HELPVIEWER_CURSOR_WAIT);




    if (CursorWait >= HELPVIEWER_CURSOR_WAIT && Ctrl && GameState)
    {
        FVector2D Vec = Ctrl->GetLeftAxis();

        if (Vec.Length() > 0.0f && FMath::Abs(Vec.Y) > FMath::Abs(Vec.X))
        {

            if (Vec.Y < 0)
            {
                Cursor++;
                if (Cursor >= HELPVIEWER_COLUMN_MAX)
                {
                    Cursor -= HELPVIEWER_COLUMN_MAX;
                }
            }
            else
            {
                Cursor--;

                if (Cursor < 0)
                {
                    Cursor += HELPVIEWER_COLUMN_MAX;
                }
            }
            GameState->SetCursorPosition(Cursor);
            CursorWait = 0.0f;
        }
    }
}
