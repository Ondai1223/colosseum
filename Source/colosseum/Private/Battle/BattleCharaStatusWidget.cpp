// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/BattleCharaStatusWidget.h"
#include "Common/CharaFace.h"

#define CHAR_FACE_NAME_1P   TEXT("WBP_InGame_CharaFace_1P")
#define CHAR_FACE_NAME_2P   TEXT("WBP_InGame_CharaFace_2P")

void UBattleCharaStatusWidget::NativeConstruct()
{
    Super::NativeConstruct();
    // ここに初期化コードを追加できます



}


void UBattleCharaStatusWidget::BeginBattleStatus_Implementation()
{

}

void UBattleCharaStatusWidget::ReflectBattleStatus_Implementation()
{
}

void UBattleCharaStatusWidget::SelectBattleStatus_Implementation()
{

}

void UBattleCharaStatusWidget::CanselBattleStatus_Implementation()
{
}

EUnitTeamID UBattleCharaStatusWidget::GetUnitTeamID() const
{
    return BattleUnitParameter->GetTeamID();
}


void UBattleCharaStatusWidget::SetUnitBattleParameter(class AUnitBattleParameter* BattleUnit)
{
    BattleUnitParameter = BattleUnit;

    if (GetUnitTeamID() == EUnitTeamID::EUTID_Team1)
    {
        CharactorFace = Cast<UCharaFace>(GetWidgetFromName(CHAR_FACE_NAME_1P));
    }
    else
    {
        CharactorFace = Cast<UCharaFace>(GetWidgetFromName(CHAR_FACE_NAME_2P));
    }

    if (BattleUnitParameter)
    {
        ChangeFace();
    }
}

void UBattleCharaStatusWidget::SetHpGauge(class UBattleGauge* InHpGauge)
{
    HpGauge = InHpGauge;
}

void UBattleCharaStatusWidget::SetMpGauge(class UBattleGauge* InMpGauge)
{
    MpGauge = InMpGauge;
}

void UBattleCharaStatusWidget::DisplayUnitBattleParameter()
{
    if (BattleUnitParameter)
    {
        // ここでBatttleUnieParameterの情報を使ってUIを更新します
        // 例えば、HPやMPの表示を更新するなど
        SetMaxHp(static_cast<int>(BattleUnitParameter->GetMaxHp()));
        SetMaxMp(static_cast<int>(BattleUnitParameter->GetMaxMp()));
        SetHp(static_cast<int>(BattleUnitParameter->GetHp()));
        SetMp(static_cast<int>(BattleUnitParameter->GetMp()));

        ChangeEndAction();
        ChangeDead();
    }
}


void UBattleCharaStatusWidget::ChangeFace()
{
    CharactorFace->TeamID = BattleUnitParameter->GetTeamID();
    CharactorFace->JobFaceID = BattleUnitParameter->GetJobID();

    CharactorFace->ChangeFace();

}

void UBattleCharaStatusWidget::ChangeEndAction()
{
    bool ActionEnd = BattleUnitParameter->IsActionEnd();
    CharactorFace->ActionEnd = ActionEnd;
    CharactorFace->Dead = BattleUnitParameter->IsDead();
    CharactorFace->EndActionMode();
}

void UBattleCharaStatusWidget::ChangeDead()
{
    CharactorFace->Dead = BattleUnitParameter->IsDead();
    CharactorFace->DeadMode();
}




int UBattleCharaStatusWidget::GetHp() const
{
    if (BattleUnitParameter)
    {
        return static_cast<int>(BattleUnitParameter->GetHp());
    }
    return 0;
}

void UBattleCharaStatusWidget::SetHp(int NewHp)
{
    HpGauge->SetNowPoint(NewHp);
}

int UBattleCharaStatusWidget::GetMaxHp() const
{
    if (BattleUnitParameter)
    {
        return static_cast<int>(BattleUnitParameter->GetMaxHp());
    }
    return 0;
}

void UBattleCharaStatusWidget::SetMaxHp(int NewMaxHp)
{
    HpGauge->SetMaxPoint(NewMaxHp);
}


int UBattleCharaStatusWidget::GetMp() const
{
    if (BattleUnitParameter)
    {
        return static_cast<int>(BattleUnitParameter->GetMp());
    }
    return 0;
}

void UBattleCharaStatusWidget::SetMp(int NewMp)
{
    MpGauge->SetNowPoint(NewMp);
}

int UBattleCharaStatusWidget::GetMaxMp() const
{
    if (BattleUnitParameter)
    {
        return static_cast<int>(BattleUnitParameter->GetMaxMp());
    }
    return 0;
}

void UBattleCharaStatusWidget::SetMaxMp(int NewMaxMp)
{
    MpGauge->SetMaxPoint(NewMaxMp);
}

void UBattleCharaStatusWidget::OpenStatus()
{
    IsStatusOpen = true;
}

void UBattleCharaStatusWidget::CloseStatus()
{
    IsStatusOpen = false;
}

bool UBattleCharaStatusWidget::IsOpenStatus() const
{
    return IsStatusOpen;
}



float UBattleCharaStatusWidget::GetHpRatio() const
{
    if (BattleUnitParameter)
    {
        float MaxHp = BattleUnitParameter->GetMaxHp();
        if (MaxHp > KINDA_SMALL_NUMBER)
        {
            return BattleUnitParameter->GetHp() / MaxHp;
        }
    }
    return 0.0f;
}


float UBattleCharaStatusWidget::GetMpRatio() const
{
    if (BattleUnitParameter)
    {
        float MaxMp = BattleUnitParameter->GetMaxMp();
        if (MaxMp > KINDA_SMALL_NUMBER)
        {
            return BattleUnitParameter->GetMp() / MaxMp;
        }
    }
    return 0.0f;
}
