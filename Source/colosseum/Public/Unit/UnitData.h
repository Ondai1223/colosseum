// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitJob.h"
#include "UnitTeamID.h"
#include "CharacterParameter.h"
#include "UnitData.generated.h"
/**
 *  ユニットデータ
 */
USTRUCT(BlueprintType)
struct FUnitData
{
    GENERATED_BODY()

    float HpMax = 100; // ユニットの体力
    float MpMax = 100; // ユニットのマナ
    float AttackPower = 50; // ユニットの攻撃力
    float DefensePower = 20; // ユニットの防御力
    float Mobility = 2; // ユニットの移動力
    EUnitJob Job = EUnitJob::EUJ_None; // ユニットのジョブ
    EUnitTeamID TeamID = EUnitTeamID::EUTID_None;   //  ユニットのチームID
    uint8 StartPosX = 0;    // ユニットの開始位置X座標
    uint8 StartPosY = 0;    // ユニットの開始位置Y座標

    FUnitData(EUnitJob InJob = EUnitJob::EUJ_None)
    {
        SetJob(InJob);
    }

    //  ジョブの設定とパラメータの反映
    void SetJob(EUnitJob InJob)
    {
        Job = InJob;
        ReflectCharacterParameter();
    }

    //  データテーブルからパラメータを反映
    void ReflectCharacterParameter()
    {
        if (Job == EUnitJob::EUJ_None) return;

        // DataTableをロード
        UDataTable* DataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Table/DT_CharacterParameter"));
        if (!DataTable)
        {
            UE_LOG(LogTemp, Warning, TEXT("CharacterParameter not found!"));
            return;
        }

        // ジョブに対応する行名を取得
        FName RowName;
        switch (Job)
        {
        case EUnitJob::EUJ_Tank:     RowName = TEXT("Tank"); break;
        case EUnitJob::EUJ_Rounder:  RowName = TEXT("Rounder"); break;
        case EUnitJob::EUJ_Magician: RowName = TEXT("Magician"); break;
        case EUnitJob::EUJ_Healer:   RowName = TEXT("Healer"); break;
        default: return;
        }

        // 堅牢なリフレクション方式を採用（FindRowの型不一致エラーを回避）
        const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();
        uint8* const* RowDataPtr = RowMap.Find(RowName);
        UScriptStruct* RowStruct = DataTable->RowStruct;

        if (RowDataPtr && RowStruct)
        {
            uint8* RowData = *RowDataPtr;

            // プロパティを名前で検索して値を抽出（float/double両対応 + あいまい検索）
            auto GetFloatValue = [&](const TCHAR* PropName, float& OutValue) {
                FProperty* Prop = RowStruct->FindPropertyByName(PropName);
                
                // 見つからない場合は全プロパティをループして部分一致を試みる（初回のみログ出力）
                if (!Prop) {
                    for (TFieldIterator<FProperty> It(RowStruct); It; ++It) {
                        FString ActualName = It->GetName();
                        if (ActualName.Contains(PropName, ESearchCase::IgnoreCase)) {
                            Prop = *It;
                            UE_LOG(LogTemp, Log, TEXT("Property %s found as %s via fuzzy match"), PropName, *ActualName);
                            break;
                        }
                    }
                }

                if (Prop) {
                    if (FNumericProperty* NumericProp = CastField<FNumericProperty>(Prop)) {
                        if (NumericProp->IsFloatingPoint()) {
                            OutValue = (float)NumericProp->GetFloatingPointPropertyValue(NumericProp->ContainerPtrToValuePtr<void>(RowData));
                            return true;
                        } else if (NumericProp->IsInteger()) {
                            OutValue = (float)NumericProp->GetSignedIntPropertyValue(NumericProp->ContainerPtrToValuePtr<void>(RowData));
                            return true;
                        }
                    }
                    UE_LOG(LogTemp, Warning, TEXT("Property %s found but is not numeric (Type: %s)"), PropName, *Prop->GetClass()->GetName());
                } else {
                    // 全プロパティ名を一覧出力してヒントを出す（一度だけ出力されるようにするなどの配慮が必要だが、デバッグ用として一旦出す）
                    FString AllProps;
                    for (TFieldIterator<FProperty> It(RowStruct); It; ++It) {
                        AllProps += It->GetName() + TEXT(", ");
                    }
                    UE_LOG(LogTemp, Warning, TEXT("Property %s NOT found. Available: [%s]"), PropName, *AllProps);
                }
                return false;
            };

            bool bSuccess = true;
            bSuccess &= GetFloatValue(TEXT("par_hp"), HpMax);
            bSuccess &= GetFloatValue(TEXT("par_mp"), MpMax);
            bSuccess &= GetFloatValue(TEXT("par_attack"), AttackPower);
            bSuccess &= GetFloatValue(TEXT("par_defense"), DefensePower);
            bSuccess &= GetFloatValue(TEXT("par_move"), Mobility);

            if (bSuccess) {
                UE_LOG(LogTemp, Warning, TEXT("Job: %s reflected via robust reflection. HP: %f, ATK: %f"), *RowName.ToString(), HpMax, AttackPower);
            } else {
                UE_LOG(LogTemp, Warning, TEXT("Job: %s reflected PARTIALLY (some fields missing) via reflection. HP: %f, ATK: %f"), *RowName.ToString(), HpMax, AttackPower);
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Row %s not found or RowStruct is invalid in DT_CharacterParameter"), *RowName.ToString());
        }
    }
};
