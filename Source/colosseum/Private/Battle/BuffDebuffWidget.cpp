// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle/BuffDebuffWidget.h"

void UBuffDebuffWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// ここでウィジェットの初期化を行う
	HorizontalBox_73->ClearChildren();
}

void UBuffDebuffWidget::AddBuffDebuffIcon(UBuffDebuffBase* BuffDebuff)
{
    UImage* NewIconImage = NewObject<UImage>(this);

    UTexture2D* BuffIconTexture = BuffDebuff->GetIcon();
    NewIconImage->SetBrushFromTexture(BuffIconTexture);

    HorizontalBox_73->AddChild(NewIconImage);
    
    BuffIconMap.Add(BuffDebuff, NewIconImage); // アイコンをマップに追加
}

void UBuffDebuffWidget::RemoveBuffDebuffIcon(UBuffDebuffBase* BuffDebuff)
{
    if (!BuffDebuff || !HorizontalBox_73) return;

    if (UImage** FoundIconPtr = BuffIconMap.Find(BuffDebuff))
    {
        UImage* IconToRemove = *FoundIconPtr;

        if (IconToRemove)
        {
            HorizontalBox_73->RemoveChild(IconToRemove);
        }

        BuffIconMap.Remove(BuffDebuff);

        UE_LOG(LogTemp, Log, TEXT("バフアイコンを削除しました"));
    }
    else
    {
        // UE_LOG(LogTemp, Warning, TEXT("削除対象のバフに対応するアイコンが見つかりません"));
    }
}
