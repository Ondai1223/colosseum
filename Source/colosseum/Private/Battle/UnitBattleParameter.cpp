// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/UnitBattleParameter.h"
#include "Unit/Unit.h"
#include "Battle/BattleHelper.h"
#include "Battle/BattleGameMode.h"

AUnitBattleParameter::AUnitBattleParameter()
{
}

void AUnitBattleParameter::BeginBattleCommand_Implementation()
{

}

void AUnitBattleParameter::EndBattleCommand_Implementation()
{
    // コマンドキャンセルの処理
    UE_LOG(LogTemp, Warning, TEXT("Unit Command Canceled!"));
}


void AUnitBattleParameter::BattleCommandVisible(bool visible)
{
    if (visible)
    {
        GameMode->InGameWidget->EnableBattleCommand();
    }
    else
    {
        GameMode->InGameWidget->DisenableBattleCommand();
    }
}


void AUnitBattleParameter::SetUnitData(TObjectPtr<AUnit>& Unit)
{
    BattleHelper    helper;

    UnitActor = Unit;
    //  ゲーム座標に変換
    helper.CalcStartLocationToGameLocation(&GameX, &GameY, Unit->GetUnitData().StartPosX, Unit->GetUnitData().StartPosY, Unit->GetUnitData().TeamID);

    //  3D座標に変換
    FVector Location = helper.CalcPanelLocation(GameX, GameY);


    UnitActor->CreateUnitData();
    Set3DLocation(Location);

    //  HP設定
    Hp = UnitActor->GetUnitData().HpMax;
    //  MP設定
    Mp = UnitActor->GetUnitData().MpMax;

    ClearAction();
}




EUnitTeamID AUnitBattleParameter::GetTeamID() const
{
    return UnitActor->GetUnitData().TeamID;
}

EUnitJob AUnitBattleParameter::AUnitBattleParameter::GetJobID() const
{
    return UnitActor->GetUnitData().Job;
}


//  移動力を返す
uint8 AUnitBattleParameter::GetMobility() const
{
    return UnitActor->GetUnitData().Mobility;
}


//  攻撃力を返す
float AUnitBattleParameter::GetAttackPower() const
{
    return UnitActor->GetUnitData().AttackPower;
}

//  防御力を返す
float AUnitBattleParameter::GetDefencePower() const
{
    float currentDefensePower = UnitActor->GetUnitData().DefensePower;

    // 防御状態なら防御力を上げる
    if(IsDiffence()) return currentDefensePower * DEFENSE_PARAMETER;

    return currentDefensePower;
}


// 回転設定
void AUnitBattleParameter::Set3DRotation(const FRotator& rotation)
{
    UnitActor->Set3DRotation(rotation);
}

// 回転取得
FRotator AUnitBattleParameter::Get3DRotation() const
{
    return UnitActor->Get3DRotation();
}


// 位置設定
void AUnitBattleParameter::Set3DLocation(const FVector& Location)
{
    UnitActor->Set3DLocation(Location);
}
// 位置取得
FVector AUnitBattleParameter::Get3DLocation() const
{
    return UnitActor->Get3DLocation();
}
//  表示非表示設定
void AUnitBattleParameter::SetVisible(bool visible)
{
    UnitActor->SetVisible(visible);
}

//  表示されているか
bool AUnitBattleParameter::IsVisible() const
{
    return UnitActor->IsVisible();
}

void AUnitBattleParameter::SetGameMode(ABattleGameMode* InGameMode)
{
    GameMode = InGameMode;
}

TObjectPtr<ABattleGameMode> AUnitBattleParameter::AUnitBattleParameter::GetGameMode() const
{
    return GameMode;
}

void AUnitBattleParameter::SetBattleCharaStatusWidget(TObjectPtr<UBattleCharaStatusWidget> CharaStatusWidget)
{
    BattleCharaStatusWidget = CharaStatusWidget;
}

TObjectPtr<UBattleCharaStatusWidget> AUnitBattleParameter::GetBattleCharaStatusWidget()
{
    return BattleCharaStatusWidget;
}


void AUnitBattleParameter::SetHpGaugeWidget(TObjectPtr<UBattleGauge> HpGauge)
{
    BattleHPGauge = HpGauge;
}


//  ステータスウエジットの取得
TObjectPtr<UBattleGauge> AUnitBattleParameter::GetHpGaugeWidget()
{
    return BattleHPGauge;
}

//  MPゲージの設定
void AUnitBattleParameter::SetMpGaugeWidget(TObjectPtr<UBattleGauge> MpGauge)
{
    BattleMpGauge = MpGauge;
}

//  MPゲージの取得
TObjectPtr<UBattleGauge> AUnitBattleParameter::GetMpGaugeWidget()
{
    return BattleMpGauge;
}



float AUnitBattleParameter::GetHp() const
{
    return Hp;
}
void AUnitBattleParameter::SetHp(float NextHp)
{
    Hp = FMath::Clamp(NextHp, 0.0f, UnitActor->GetUnitData().HpMax);
}


float AUnitBattleParameter::GetMaxHp() const
{
    return UnitActor->GetUnitData().HpMax;
}


float AUnitBattleParameter::GetMp() const
{
    return Mp;
}

void AUnitBattleParameter::SetMp(float NextMp)
{
    Mp = FMath::Clamp(NextMp, 0.0f, UnitActor->GetUnitData().MpMax);
}

float AUnitBattleParameter::GetMaxMp() const
{
    return UnitActor->GetUnitData().MpMax;
}

bool AUnitBattleParameter::IsActionEnd() const
{
    bool IsActionEnd = ActionEnd || IsDead() || (MoveEnd && AttackEnd) || (MoveEnd && SkillEnd);
    return IsActionEnd;
}

void AUnitBattleParameter::ClearAction()
{
    ActionEnd = false;
    AttackEnd = false;
    MoveEnd = false;
    SkillEnd = false;
}


void AUnitBattleParameter::PlayAnimationWait(float ShiftTime )
{
    UnitActor->PlayAnimationWait(ShiftTime);
}
void AUnitBattleParameter::PlayAnimationMove(float ShiftTime )
{
    UnitActor->PlayAnimationMove(ShiftTime);
}

void AUnitBattleParameter::PlayAnimationAttack(float ShiftTime )
{
    UnitActor->PlayAnimationAttack(ShiftTime);
}

void AUnitBattleParameter::PlayAnimationDamage(float ShiftTime)
{
    UnitActor->PlayAnimationDamage(ShiftTime);
}

void AUnitBattleParameter::PlayAnimationDeath(float ShiftTime)
{
    UnitActor->PlayAnimationDeath(ShiftTime);
}


void AUnitBattleParameter::PlayAnimationGuard(float ShiftTime)
{
    UnitActor->PlayAnimationGuard(ShiftTime);
}
void AUnitBattleParameter::PlayAnimationSkillAttack(float ShiftTime)
{
    UnitActor->PlayAnimationSkillAttack(ShiftTime);
}

void AUnitBattleParameter::PlayAnimationBuf(float ShiftTime)
{
    UnitActor->PlayAnimationBuf(ShiftTime);

}





bool AUnitBattleParameter::IsEndOfAnime() const
{
    return UnitActor->IsEndOfAnime();
}




