// Fill out your copyright notice in the Description page of Project Settings.
#include "Battle/BattleCommandWidget.h"
#include "Battle/BattleGameMode.h"
#include "Components/TextBlock.h"
#define COMMAND_NUM 4

#define ATTACK_COLUMN   0
#define DIFFENCE_COLUMN 1
#define SKILL_COLUMN    2
#define MOVE_COLUMN     3

#define COMMAND_SWITCHER_ON 0
#define COMMAND_SWITCHER_OFF    1


#define COMMAND_ATTACK_NAME     TEXT("WBP_Command_1")
#define COMMAND_DIFFENCE_NAME   TEXT("WBP_Command_2")
#define COMMAND_SKILL_NAME      TEXT("WBP_Command_3")
#define COMMAND_MOVE_NAME       TEXT("WBP_Command_4")

#define ARROW_NAME              TEXT("WidgetSwitcher_Base")
#define TEXT_BLOCK_NAME         TEXT("TextBlockCommand")

#define TEXT_NAME_ATTACK        TEXT("攻撃")
#define TEXT_NAME_DIFFENCE      TEXT("防御")
#define TEXT_NAME_SKILL         TEXT("特技")
#define TEXT_NAME_MOVE          TEXT("移動")

//  ウイジェット構築
void UBattleCommandWidget::NativeConstruct()
{
    Super::NativeConstruct();

    //  コマンドウイジェット取得
    TObjectPtr<UBattleCommandColumn> CommandAttack = Cast<UBattleCommandColumn>(GetWidgetFromName(COMMAND_ATTACK_NAME));
    TObjectPtr<UBattleCommandColumn> CommandDiffence = Cast<UBattleCommandColumn>(GetWidgetFromName(COMMAND_DIFFENCE_NAME));
    TObjectPtr<UBattleCommandColumn> CommandSkill = Cast<UBattleCommandColumn>(GetWidgetFromName(COMMAND_SKILL_NAME));
    TObjectPtr<UBattleCommandColumn> CommandMove = Cast<UBattleCommandColumn>(GetWidgetFromName(COMMAND_MOVE_NAME));

    //  矢印ウイジェット配列にセット
    BattleArrows.Add(CommandAttack);
    BattleArrows.Add(CommandDiffence);
    BattleArrows.Add(CommandSkill);
    BattleArrows.Add(CommandMove);




    //  アイコン選択
    CommandAttack->SelectIconNo = ATTACK_COLUMN;
    CommandDiffence->SelectIconNo = DIFFENCE_COLUMN;
    CommandSkill->SelectIconNo = SKILL_COLUMN;
    CommandMove->SelectIconNo = MOVE_COLUMN;

    CommandAttack->OnChangeIcon();
    CommandDiffence->OnChangeIcon();
    CommandSkill->OnChangeIcon();
    CommandMove->OnChangeIcon();


    //  テキスト変更
    TObjectPtr<UTextBlock> TextAttack = Cast<UTextBlock>(CommandAttack->GetWidgetFromName(TEXT_BLOCK_NAME));
    TObjectPtr<UTextBlock> TextDiffence = Cast<UTextBlock>(CommandDiffence->GetWidgetFromName(TEXT_BLOCK_NAME));
    TObjectPtr<UTextBlock> TextSklil = Cast<UTextBlock>(CommandSkill->GetWidgetFromName(TEXT_BLOCK_NAME));
    TObjectPtr<UTextBlock> TextMove = Cast<UTextBlock>(CommandMove->GetWidgetFromName(TEXT_BLOCK_NAME));


    //  注意：とりあえず、文字列直接指定してあります。
    TextAttack->SetText(FText::FromString(TEXT_NAME_ATTACK));
    TextDiffence->SetText(FText::FromString(TEXT_NAME_DIFFENCE));
    TextSklil->SetText(FText::FromString(TEXT_NAME_SKILL));
    TextMove->SetText(FText::FromString(TEXT_NAME_MOVE));

    //  全ての矢印を非表示
    ArrowAllHiddn();

}

//  バトルコマンド開始
void UBattleCommandWidget::BeginBattleCommand_Implementation(ABattleGameMode* BattleGameMode, AUnitBattleParameter* BattleUnit)
{
    
}

//  Tickバトルコマンド
void UBattleCommandWidget::TickBattleCommand_Implementation(float DeltaSecondst)
{
}

//  バトルコマンド終了
void UBattleCommandWidget::ReleaseBattleCommand_Implementation(float DeltaSeconds)
{
}


//  全ての矢印を非表示
void UBattleCommandWidget::ArrowAllHiddn()
{
    for (TArray<TObjectPtr<UBattleCommandColumn>>::TIterator Ite(BattleArrows); Ite; ++Ite)
    {
        (*Ite)->SelectedColumn = COMMAND_SWITCHER_OFF;
        (*Ite)->OnSelectedColumn();
    }
}

//  カーソル設定(AddCursorに0を指定するとスタックオーバーフローを起こします。必ず。1か-1を設定してください)
void UBattleCommandWidget::SetArrow(int AddCursor)
{
    ArrowAllHiddn();

    bool LoopCursor = false;
    if (SelectCursor == ATTACK_COLUMN && SelectUnit->IsAttackEnd())
    {
        SelectCursor += AddCursor;
        LoopCursor = true;
    }

    if (SelectCursor == DIFFENCE_COLUMN && SelectUnit->IsDiffenceEnd())
    {
        SelectCursor += AddCursor;
        LoopCursor = true;
    }

    if (SelectCursor == SKILL_COLUMN && SelectUnit->IsSkillEnd())
    {
        SelectCursor += AddCursor;
        LoopCursor = true;
    }

    if (SelectCursor == MOVE_COLUMN && SelectUnit->IsMoveEnd())
    {
        SelectCursor += AddCursor;
        LoopCursor = true;
    }

    if (SelectCursor < 0)
    {
        SelectCursor += COMMAND_NUM;
        LoopCursor = true;
    }
    if (SelectCursor >= COMMAND_NUM)
    {
        SelectCursor -= COMMAND_NUM;
        LoopCursor = true;
    }
    if (LoopCursor)
    {
        SetArrow(AddCursor);
        return;
    }


    BattleArrows[SelectCursor]->SelectedColumn = COMMAND_SWITCHER_ON;
    BattleArrows[SelectCursor]->OnSelectedColumn();
}

//  コマンド選択処理(戻り値：コマンド確定したらそのコマンドを返す。まだならEBattleCommand::NONEを返す)
EBattleCommand UBattleCommandWidget::RunSelectCommand(float DeltaSeconds)
{
    FVector2D   axis = GameMode->BattleController->GetLeftAxisTrigger();

    if (axis.Size() > 0.0f) {
        if (FMath::Abs(axis.X) < FMath::Abs(axis.Y)) {
            int AddCursor = 0;
            if (axis.Y > 0) {
                --SelectCursor;
                if (SelectCursor == ATTACK_COLUMN && SelectUnit->IsAttackEnd())
                {
                    SelectCursor += COMMAND_NUM-1;
                }
                if (SelectCursor == DIFFENCE_COLUMN && SelectUnit->IsDiffenceEnd())
                {
                    --SelectCursor;
                }
                if (SelectCursor == SKILL_COLUMN && SelectUnit->IsSkillEnd())
                {
                    --SelectCursor;
                }
                if (SelectCursor == MOVE_COLUMN && SelectUnit->IsMoveEnd())
                {
                    --SelectCursor;
                }
                AddCursor = -1;
            }
            else
            {
                ++SelectCursor;
                if (SelectCursor == ATTACK_COLUMN && SelectUnit->IsAttackEnd())
                {
                    ++SelectCursor;
                }

                if (SelectCursor == DIFFENCE_COLUMN && SelectUnit->IsDiffenceEnd())
                {
                    ++SelectCursor;
                }


                if (SelectCursor == SKILL_COLUMN && SelectUnit->IsSkillEnd())
                {
                    ++SelectCursor;
                }
                if (SelectCursor == MOVE_COLUMN && SelectUnit->IsMoveEnd())
                {
                    SelectCursor -= COMMAND_NUM - 1;
                }
                AddCursor = 1;
            }

            SetArrow(AddCursor);
        }
    }
    else if (GameMode->BattleController->IsOkTrigger())
    {
        //  コマンド選択可能か？

        EBattleCommand Cmd = static_cast<EBattleCommand>(SelectCursor);
        if (Cmd == EBattleCommand::EBC_ATTACK && SelectUnit->IsAttackEnd()
         || Cmd == EBattleCommand::EBC_SKILL && SelectUnit->IsSkillEnd())
        {
            //  選択不可
            return EBattleCommand::EBC_CONTINUE;
        }
        //  コマンド選択
        return static_cast<EBattleCommand>(SelectCursor);
    }
    else if (GameMode->BattleController->IsCanselTrigger() && !SelectUnit->IsAttackEnd())
    {
        return EBattleCommand::EBC_CANSEL;
    }




    return EBattleCommand::EBC_CONTINUE;
}

//  選択コマンドをセット
void UBattleCommandWidget::SetSelectedCommand()
{
#if 0
    TObjectPtr<UBattleCommandColumn> CommandAttack = Cast<UBattleCommandColumn>(GetWidgetFromName(COMMAND_ATTACK_NAME));
    TObjectPtr<UBattleCommandColumn> CommandDiffence = Cast<UBattleCommandColumn>(GetWidgetFromName(COMMAND_DIFFENCE_NAME));
    TObjectPtr<UBattleCommandColumn> CommandSkill = Cast<UBattleCommandColumn>(GetWidgetFromName(COMMAND_SKILL_NAME));
    TObjectPtr<UBattleCommandColumn> CommandMove = Cast<UBattleCommandColumn>(GetWidgetFromName(COMMAND_MOVE_NAME));

    CommandAttack->SelectedColumn = (SelectUnit->IsAttackEnd()) ? 1 : 0;
    CommandDiffence->SelectedColumn = (SelectUnit->IsDiffenceEnd()) ? 1 : 0;
    CommandSkill->SelectedColumn = (SelectUnit->IsSkillEnd()) ? 1 : 0;
    CommandMove->SelectedColumn = (SelectUnit->IsMoveEnd()) ? 1 : 0;

    CommandAttack->OnSelectedColumn();
    CommandDiffence->OnSelectedColumn();
    CommandSkill->OnSelectedColumn();
    CommandMove->OnSelectedColumn();
#endif
}