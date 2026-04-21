// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle/BattleSkillItem.h"
#include "Blueprint/WidgetTree.h"
#include "Components/PanelWidget.h"

#define ARROW_WIDGET_NAME TEXT("WBP_Common_Arrow")
#define TEXTBLOCK_WIDGET_NAME TEXT("TextBlock_SkillName")

void UBattleSkillItem::NativeConstruct()
{
    Super::NativeConstruct();
    if (!CommonArrow)
    {
        CommonArrow = Cast<UUserWidget>(FindWidgetRecursive(this, ARROW_WIDGET_NAME));
    }
    
    if (CommonArrow)
    {
        UE_LOG(LogTemp, Log, TEXT("Skill Item %s: Found Arrow %s"), *GetName(), *CommonArrow->GetName());
        CommonArrow->SetVisibility(ESlateVisibility::Hidden);
    }
    
    if (!TextBlock_SkillName)
    {
        TextBlock_SkillName = Cast<UTextBlock>(FindWidgetRecursive(this, TEXTBLOCK_WIDGET_NAME));
        if (TextBlock_SkillName)
        {
             UE_LOG(LogTemp, Log, TEXT("Skill Item %s: Found TextBlock %s"), *GetName(), *TextBlock_SkillName->GetName());
        }
    }

    // デフォルトの表示反映
    if (!SkillName.IsEmpty())
    {
        SetSkillName(SkillName);
    }
}

UWidget* UBattleSkillItem::FindWidgetRecursive(UWidget* Root, FName Name)
{
    if (!Root) return nullptr;
    if (Root->GetFName() == Name) return Root;

    if (UUserWidget* UserWidget = Cast<UUserWidget>(Root))
    {
        if (UserWidget->WidgetTree)
        {
            return FindWidgetRecursive(UserWidget->WidgetTree->RootWidget, Name);
        }
    }
    else if (UPanelWidget* PanelWidget = Cast<UPanelWidget>(Root))
    {
        for (int32 i = 0; i < PanelWidget->GetChildrenCount(); ++i)
        {
            if (UWidget* Found = FindWidgetRecursive(PanelWidget->GetChildAt(i), Name))
            {
                return Found;
            }
        }
    }
    return nullptr;
}

void UBattleSkillItem::OnSelected_Implementation()
{
    UE_LOG(LogTemp, Log, TEXT("Skill Item %s: Selected"), *GetName());
    if (CommonArrow)
    {
        CommonArrow->SetVisibility(ESlateVisibility::Visible);
    }
}

void UBattleSkillItem::OnDeselected_Implementation()
{
    if (CommonArrow)
    {
        CommonArrow->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UBattleSkillItem::OnConfirmed_Implementation()
{
}

void UBattleSkillItem::SetSkillIcon_Implementation(EBattleSkillIcon IconID)
{
    ;
}


void UBattleSkillItem::SetSkillName(const FText& InName)
{
    SkillName = InName;
    
    // もしTextBlockがまだ見つかっていなければ、ここで再度検索を試みる
    if (!TextBlock_SkillName)
    {
        TextBlock_SkillName = Cast<UTextBlock>(FindWidgetRecursive(this, TEXTBLOCK_WIDGET_NAME));
    }


    if (TextBlock_SkillName)
    {
        TextBlock_SkillName->SetText(InName);
        UE_LOG(LogTemp, Log, TEXT("Skill Item %s: Text set to '%s'"), *GetName(), *InName.ToString());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Skill Item %s: TextBlock_SkillName not found during SetSkillName"), *GetName());
    }
}

void UBattleSkillItem::SetSkillData(const FSkillDataType& InData)
{
    SkillData = InData;
    SetSkillName(SkillData.skill_name);
    SetSkillIcon(SkillData.icon_id);
}
