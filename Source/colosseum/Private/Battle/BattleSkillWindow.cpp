// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle/BattleSkillWindow.h"
#include "Blueprint/WidgetTree.h"
#include "Battle/SkillData.h"
#include "Unit/SkillParameter.h"

void UBattleSkillWindow::NativeConstruct()
{
    Super::NativeConstruct();
    UpdateSkillItems();
    // データ反映はResetSelection(Job)経由で行うため、ここでは行わない
    ScrollBox = nullptr;
    FindScrollBoxRecursive(WidgetTree->RootWidget);
    RefreshSelection();
}

void UBattleSkillWindow::PrevSkill()
{
    if (SkillItems.Num() == 0) return;

    SelectIndex--;
    if (SelectIndex < 0)
    {
        SelectIndex = SkillItems.Num() - 1;
    }
    RefreshSelection();
}

void UBattleSkillWindow::NextSkill()
{
    if (SkillItems.Num() == 0) return;

    SelectIndex++;
    if (SelectIndex >= SkillItems.Num())
    {
        SelectIndex = 0;
    }
    RefreshSelection();
}

void UBattleSkillWindow::ResetSelection(EUnitJob Job)
{
    SelectIndex = 0;
    UpdateSkillItems();
    ApplySkillData(Job);
    RefreshSelection();
}

FSkillDataType UBattleSkillWindow::GetSelectedSkillData() const
{
    if (SkillItems.IsValidIndex(SelectIndex))
    {
        return SkillItems[SelectIndex]->SkillData;
    }
    return FSkillDataType();
}

void UBattleSkillWindow::UpdateSkillItems()
{
    SkillItems.Empty();
    UE_LOG(LogTemp, Log, TEXT("UBattleSkillWindow::UpdateSkillItems started. RootWidget: %s"), *WidgetTree->RootWidget->GetName());
    FindSkillItemsRecursive(WidgetTree->RootWidget);
    UE_LOG(LogTemp, Log, TEXT("UBattleSkillWindow::UpdateSkillItems finished. Count: %d"), SkillItems.Num());
}

void UBattleSkillWindow::ApplySkillData(EUnitJob Job)
{
    if (!SkillDataTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBattleSkillWindow: SkillDataTable is NOT set."));
        return;
    }

    // ジョブを文字列に変換
    FString JobString;
    switch (Job)
    {
    case EUnitJob::EUJ_Tank:     JobString = TEXT("Tank"); break;
    case EUnitJob::EUJ_Rounder:  JobString = TEXT("Rounder"); break;
    case EUnitJob::EUJ_Magician: JobString = TEXT("Magician"); break;
    case EUnitJob::EUJ_Healer:   JobString = TEXT("Healer"); break;
    default: JobString = TEXT("None"); break;
    }

    // 型チェックを回避し、かつメモリレイアウトの不一致に強いリフレクション方式を採用
    TArray<FSkillDataType> FilteredSkills;
    const TMap<FName, uint8*>& RowMap = SkillDataTable->GetRowMap();
    UScriptStruct* RowStruct = SkillDataTable->RowStruct;

    if (!RowStruct)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBattleSkillWindow: RowStruct is NULL!"));
        return;
    }

    // プロパティを名前（またはプレフィックス）で検索
    FProperty* NameProp = RowStruct->FindPropertyByName(TEXT("skill_name"));
    FProperty* CharProp = RowStruct->FindPropertyByName(TEXT("character"));
    FProperty* EffectProp = RowStruct->FindPropertyByName(TEXT("effect_id"));
    FProperty* MotionProp = RowStruct->FindPropertyByName(TEXT("motion_id"));
    FProperty* TargetProp = RowStruct->FindPropertyByName(TEXT("target_id"));
    FProperty* AbilityProp = RowStruct->FindPropertyByName(TEXT("skill_ability"));
    FProperty* BuffDebuffProp = RowStruct->FindPropertyByName(TEXT("buffdebuff_type"));
    FProperty* SkillIconProp = RowStruct->FindPropertyByName(TEXT("icon_id"));

    if (!NameProp || !CharProp)
    {
        for (TFieldIterator<FProperty> It(RowStruct); It; ++It)
        {
            FString PropName = It->GetName();
            if (!NameProp && PropName.StartsWith(TEXT("skill_name"))) NameProp = *It;
            if (!CharProp && PropName.StartsWith(TEXT("character"))) CharProp = *It;
            if (!EffectProp && PropName.StartsWith(TEXT("effect_id"))) EffectProp = *It;
            if (!MotionProp && PropName.StartsWith(TEXT("motion_id"))) MotionProp = *It;
            if (!TargetProp && PropName.StartsWith(TEXT("target_id"))) TargetProp = *It;
            if (!AbilityProp && PropName.StartsWith(TEXT("skill_ability"))) AbilityProp = *It;
            if (!BuffDebuffProp && PropName.StartsWith(TEXT("buffdebuff_type"))) BuffDebuffProp = *It;
            if (!SkillIconProp && PropName.StartsWith(TEXT("icon_id"))) SkillIconProp = *It;
        }
    }

    if (!NameProp || !CharProp)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBattleSkillWindow: Still missing skill_name or character columns after fuzzy search."));
        return;
    }

    // Load SkillParameterTable once
    UDataTable* SkillParamTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Table/DT_SkillParameter"));
    if (!SkillParamTable)
    {
         UE_LOG(LogTemp, Error, TEXT("DT_SkillParameter NOT FOUND in UBattleSkillWindow::ApplySkillData"));
    }

    for (auto& It : RowMap)
    {
        uint8* RowData = It.Value;

        // character を取得
        FString RowCharStr;
        if (CharProp->IsA<FNameProperty>())
        {
            RowCharStr = CastField<FNameProperty>(CharProp)->GetPropertyValue_InContainer(RowData).ToString();
        }
        else if (CharProp->IsA<FStrProperty>())
        {
            RowCharStr = CastField<FStrProperty>(CharProp)->GetPropertyValue_InContainer(RowData);
        }

        if (RowCharStr.TrimStartAndEnd().Equals(JobString, ESearchCase::IgnoreCase))
        {
            FSkillDataType NewSkillData;

            // skill_name
            if (NameProp->IsA<FTextProperty>())
            {
                NewSkillData.skill_name = CastField<FTextProperty>(NameProp)->GetPropertyValue_InContainer(RowData);
            }
            else if (NameProp->IsA<FNameProperty>())
            {
                NewSkillData.skill_name = FText::FromName(CastField<FNameProperty>(NameProp)->GetPropertyValue_InContainer(RowData));
            }
            else if (NameProp->IsA<FStrProperty>())
            {
                NewSkillData.skill_name = FText::FromString(CastField<FStrProperty>(NameProp)->GetPropertyValue_InContainer(RowData));
            }

            // character
            NewSkillData.character = FName(*RowCharStr);

            // effect_id
            if (EffectProp)
            {
                if (EffectProp->IsA<FNameProperty>())
                    NewSkillData.effect_id = CastField<FNameProperty>(EffectProp)->GetPropertyValue_InContainer(RowData);
                else if (EffectProp->IsA<FStrProperty>())
                    NewSkillData.effect_id = FName(*CastField<FStrProperty>(EffectProp)->GetPropertyValue_InContainer(RowData));
            }

            // motion_id
            if (MotionProp)
            {
                if (MotionProp->IsA<FNameProperty>())
                    NewSkillData.motion_id = CastField<FNameProperty>(MotionProp)->GetPropertyValue_InContainer(RowData);
                else if (MotionProp->IsA<FStrProperty>())
                    NewSkillData.motion_id = FName(*CastField<FStrProperty>(MotionProp)->GetPropertyValue_InContainer(RowData));
            }

            // target_id
            if (TargetProp)
            {
                if (TargetProp->IsA<FNameProperty>())
                    NewSkillData.target_id = CastField<FNameProperty>(TargetProp)->GetPropertyValue_InContainer(RowData);
                else if (TargetProp->IsA<FStrProperty>())
                    NewSkillData.target_id = FName(*CastField<FStrProperty>(TargetProp)->GetPropertyValue_InContainer(RowData));
            }

			// skill_ability
            if (AbilityProp)
            {
                if (FEnumProperty* EnumProp = CastField<FEnumProperty>(AbilityProp))
                {
                    // プロパティから数値（uint8相当）を取得
                    int64 EnumValue = EnumProp->GetUnderlyingProperty()->GetSignedIntPropertyValue(EnumProp->ContainerPtrToValuePtr<void>(RowData));
                    // ESkillAbility型にキャストして代入
                    NewSkillData.skill_ability = static_cast<ESkillAbility>(EnumValue);
                }
            }

            // buffdebuff_type
            if (BuffDebuffProp)
            {
                if (FEnumProperty* EnumProp = CastField<FEnumProperty>(BuffDebuffProp))
                {
                    // プロパティから数値（uint8相当）を取得
                    int64 EnumValue = EnumProp->GetUnderlyingProperty()->GetSignedIntPropertyValue(EnumProp->ContainerPtrToValuePtr<void>(RowData));
                    // EBuffDebuffType型にキャストして代入
                    NewSkillData.buffdebuff_type = static_cast<EBuffDebuffType>(EnumValue);
                }
            }

            // icon_id
            if (SkillIconProp)
            {
                if (FEnumProperty* EnumProp = CastField<FEnumProperty>(SkillIconProp))
                {
                    // プロパティから数値（uint8相当）を取得
                    int64 EnumValue = EnumProp->GetUnderlyingProperty()->GetSignedIntPropertyValue(EnumProp->ContainerPtrToValuePtr<void>(RowData));
                    // EBuffDebuffType型にキャストして代入
                    NewSkillData.icon_id = static_cast<EBattleSkillIcon>(EnumValue);
                }
            }




            // SkillParameter.h reflects values from DT_SkillParameter (matching RowName)
            if (SkillParamTable)
            {
                FName SkillRowName = It.Key;
                const TMap<FName, uint8*>& ParamRowMap = SkillParamTable->GetRowMap();
                uint8* const* ParamRowDataPtr = ParamRowMap.Find(SkillRowName);
                UScriptStruct* ParamRowStruct = SkillParamTable->RowStruct;

                if (ParamRowDataPtr && ParamRowStruct)
                {
                    uint8* ParamRowData = *ParamRowDataPtr;
                    FProperty* ElemProp = ParamRowStruct->FindPropertyByName(TEXT("skl_element"));
                    if(!ElemProp) {
                        UE_LOG(LogTemp, Warning, TEXT("見つからなかった"));
                        for (TFieldIterator<FProperty> ItProp(ParamRowStruct); ItProp; ++ItProp) {
                            if (ItProp->GetName().Contains(TEXT("skl_element"), ESearchCase::IgnoreCase)) {
                                ElemProp = *ItProp;
                                break;
                            }
                        }
					}
                    if (ElemProp)
                    {
                        if (ElemProp->IsA<FNameProperty>())
                        {
                            NewSkillData.element_id = CastField<FNameProperty>(ElemProp)->GetPropertyValue_InContainer(ParamRowData);
                            UE_LOG(LogTemp, Warning, TEXT("Skill %s: Found skl_element as FNameProperty, value=%s"), *SkillRowName.ToString(), *NewSkillData.element_id.ToString());
                        }
                        else if (ElemProp->IsA<FStrProperty>())
                        {
                            NewSkillData.element_id = FName(*CastField<FStrProperty>(ElemProp)->GetPropertyValue_InContainer(ParamRowData));
                            UE_LOG(LogTemp, Warning, TEXT("Skill %s: Found skl_element as FNameProperty, value=%s"), *SkillRowName.ToString(), *NewSkillData.element_id.ToString());
                        }
                    }
                    auto GetFloatValue = [&](const TCHAR* PropName, float& OutValue) {
                        FProperty* Prop = ParamRowStruct->FindPropertyByName(PropName);
                        if (!Prop) {
                            for (TFieldIterator<FProperty> ItProp(ParamRowStruct); ItProp; ++ItProp) {
                                if (ItProp->GetName().Contains(PropName, ESearchCase::IgnoreCase)) {
                                    Prop = *ItProp;
                                    break;
                                }
                            }
                        }

                        if (Prop) {
                            if (FNumericProperty* NumericProp = CastField<FNumericProperty>(Prop)) {
                                if (NumericProp->IsFloatingPoint()) {
                                    OutValue = (float)NumericProp->GetFloatingPointPropertyValue(NumericProp->ContainerPtrToValuePtr<void>(ParamRowData));
                                    return true;
                                } else if (NumericProp->IsInteger()) {
                                    OutValue = (float)NumericProp->GetSignedIntPropertyValue(NumericProp->ContainerPtrToValuePtr<void>(ParamRowData));
                                    return true;
                                }
                            }
                        }
                        return false;
                    };

                    GetFloatValue(TEXT("btl_skl_attack"), NewSkillData.btl_skl_attack);
                    GetFloatValue(TEXT("btl_skl_cost"), NewSkillData.btl_skl_cost);

                    UE_LOG(LogTemp, Log, TEXT("Skill %s: Atk=%f, Cost=%f (via reflection)"), *SkillRowName.ToString(), NewSkillData.btl_skl_attack, NewSkillData.btl_skl_cost);
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Skill %s: Parameter Row not found in DT_SkillParameter"), *SkillRowName.ToString());
                }
            }

            FilteredSkills.Add(NewSkillData);
        }
    }

    UE_LOG(LogTemp, Log, TEXT("UBattleSkillWindow: Filtered %d skills for Job %s"), FilteredSkills.Num(), *JobString);

    // UIへ反映
    for (int32 i = 0; i < SkillItems.Num(); ++i)
    {
        if (FilteredSkills.IsValidIndex(i))
        {
            SkillItems[i]->SetSkillData(FilteredSkills[i]);
        }
        else
        {
            SkillItems[i]->SetSkillName(FText::FromString(TEXT("----")));
            // データをクリアすべきだが、SetSkillData(Empty)などが必要か？
            // とりあえず名前だけクリア表示にしている既存動作を維持
            // 必要なら FSkillDataType() で初期化してもよいが、表示上の都合で名前だけ変えている可能性あり
    }
    }
}

void UBattleSkillWindow::FindSkillItemsRecursive(UWidget* Root)
{
    if (!Root) return;

    UE_LOG(LogTemp, Verbose, TEXT("Exploring Widget: %s (%s)"), *Root->GetName(), *Root->GetClass()->GetName());

    // 自身が特技項目かチェック
    if (UBattleSkillItem* Item = Cast<UBattleSkillItem>(Root))
    {
        SkillItems.Add(Item);
        UE_LOG(LogTemp, Log, TEXT("Found Skill Item: %s, SkillName: %s"), *Root->GetName(), *Item->SkillData.skill_name.ToString());
        return; // 項目の中身までは探索しない
    }

    // 子ウィジェットを探索
    if (UUserWidget* UserWidget = Cast<UUserWidget>(Root))
    {
        if (UserWidget->WidgetTree)
        {
            FindSkillItemsRecursive(UserWidget->WidgetTree->RootWidget);
        }
    }
    else if (UPanelWidget* PanelWidget = Cast<UPanelWidget>(Root))
    {
        for (int32 i = 0; i < PanelWidget->GetChildrenCount(); ++i)
        {
            FindSkillItemsRecursive(PanelWidget->GetChildAt(i));
        }
    }
}

void UBattleSkillWindow::RefreshSelection()
{
    for (int32 i = 0; i < SkillItems.Num(); ++i)
    {
        if (i == SelectIndex)
        {
            SkillItems[i]->OnSelected();
            // 選択されたアイテムをスクロールして表示
            if (ScrollBox)
            {
                ScrollBox->ScrollWidgetIntoView(SkillItems[i]);
            }
        }
        else
        {
            SkillItems[i]->OnDeselected();
        }
    }
}

void UBattleSkillWindow::FindScrollBoxRecursive(UWidget* Root)
{
    if (!Root || ScrollBox) return;

    if (UScrollBox* FoundScrollBox = Cast<UScrollBox>(Root))
    {
        ScrollBox = FoundScrollBox;
        UE_LOG(LogTemp, Log, TEXT("UBattleSkillWindow: Found ScrollBox: %s"), *ScrollBox->GetName());
        return;
    }

    if (UUserWidget* UserWidget = Cast<UUserWidget>(Root))
    {
        if (UserWidget->WidgetTree)
        {
            FindScrollBoxRecursive(UserWidget->WidgetTree->RootWidget);
        }
    }
    else if (UPanelWidget* PanelWidget = Cast<UPanelWidget>(Root))
    {
        for (int32 i = 0; i < PanelWidget->GetChildrenCount(); ++i)
        {
            FindScrollBoxRecursive(PanelWidget->GetChildAt(i));
        }
    }
}
