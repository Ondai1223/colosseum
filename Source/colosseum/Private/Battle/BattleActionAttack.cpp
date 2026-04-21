// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle/BattleActionAttack.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#ifndef ENABLE_BATTLE_ACTION_INTERFACE_GAME_MODE_PROXY
#include "Battle/BattleGameMode.h"
#else
#include "Battle/BattleGameModeProxy.h"
#endif // ENABLE_BATTLE_ACTION_INTERFACE_GAME_MODE_PROXY


#define BP_BATTLE_ATTACK_CAMERA_PATH TEXT("/Game/Battle/Blueprints/BP_BattleAttackCamera.BP_BattleAttackCamera_C")  /// BP_Unit
#define BATTLE_ATTACK_CAMERA_MOVE_TIME 0.01f
#define BATTLE_ATTACK_CAMERA_ATTACK_MOVE_TIME 1.5f
#define BATTLE_ATTACK_EFFECT TEXT("/Game/FixEffect/BattleEffect/Ef_Btl_Attack_01.Ef_Btl_Attack_01")

#define DEFFENCE_PARAMETER  15 //防御力のパラメータ
//  選択パネルの設定
//  CenterGameX     :   中心となるX座標
//  CenterGameY     :   中心となるX座標
//  GameMode        :   ゲームモード
void UBattleActionAttack::SetSelectPanel(int CenterGameX, int CenterGameY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleActionGameModeProxy* GameMode, const FSkillDataType& SkillData)
{
    //  攻撃範囲の設定
    GameMode->BattleSelector->SetPanel(CenterGameX + 1, CenterGameY,true);
    GameMode->BattleSelector->SetPanel(CenterGameX - 1, CenterGameY,true);
    GameMode->BattleSelector->SetPanel(CenterGameX, CenterGameY + 1,true);
    GameMode->BattleSelector->SetPanel(CenterGameX, CenterGameY - 1,true);
}


//  スキル選択開始
//  ActionUnit      :   スキルを行使するユニット
//  GameMode        :   ゲームモード
void UBattleActionAttack::SelectSkillBegin(TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleActionGameModeProxy* GameMode)
{
    ;   //  攻撃では使用しない
}

//  スキル選択のTick
//  -1でまだ選択が終わっていない
//  -2でキャンセル
//  0以上で選択したスキル
int UBattleActionAttack::SelectSkillTick(TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleActionGameModeProxy* GameMode, FSkillDataType& OutSkillData)
{
    ;   //  攻撃では使用しない
    return BATTLE_ACTION_SKILL_SELECT_CANSEL;
}

//  アクション計算
//  ActionResult    :   アクション結果格納先
//  TargetLocations :   ターゲットするゲーム座標
//  ActionUnit      :   アクションを起こすユニット
//  GameMode        :   ゲームモード
//  SkillID         :   スキルID(特技を選択した時のみ有効）
void UBattleActionAttack::CalcAction(FActionResultData* ActionResult, const TArray<FGameLocation>& TargetLocations, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleActionGameModeProxy* GameMode, const FSkillDataType& SkillData)
{
    //  ダメージ計算
    //  共通のアクションユニットの設定
    ActionResult->ActionUnit = ActionUnit;

    for (TArray<FGameLocation>::TConstIterator Ite(TargetLocations); Ite; ++Ite)
    {
        TObjectPtr Target = GameMode->GetUnit(Ite->X, Ite->Y);
        if (Target) {
            FActionAttackTargetData TargetData;
            TargetData.TargetUnit = Target;

            /* ここから */
            // UnitBattleParameterからUnitのパラメータを取得して計算する.
            // 
            // 攻撃する側: ActionUnit(SelectUnit) 攻撃力を参照
            // 攻撃を受ける側: Target 防御力を参照
            // ダメージ計算： 攻撃力(行)/防御力(被)＊攻撃倍率(15)＝ダメージ
            // 通常攻撃ではスキルを使用しないので,MPは減らない.
            //

            float attackPower = ActionUnit->GetAttackPower();
            float defensePower = Target->GetDefencePower();
            float calculatedDamage = attackPower / defensePower * DEFFENCE_PARAMETER;
            
            // Clamp(変数, Min, Max);変数の取りうる値を制限する.
            FMath::Clamp(calculatedDamage, 0, Target->GetMaxHp());
           

            UE_LOG(LogTemp, Warning, TEXT("calculatedDamage: %f, attackPower: %f, defensePower: %f"), calculatedDamage, attackPower, defensePower);

            TargetData.HpDamage = calculatedDamage;    //  HPダメージ
            /* ここまで */

            TargetData.MpDamage = 0.0f;
            ActionResult->ActionAttackResult.AttackTargets.Add(TargetData);
        }
    }
}

//  アクション結果を反映
//  ActionResult    :   結果格納先
//  GameMode        :   ゲームモード
void UBattleActionAttack::ReflectAction(FActionResultData& ActionResult, ABattleActionGameModeProxy* GameMode)
{
    //  数値の反映
    //  ここでは数値の反映だけを行います。アニメーションなどはBeginAction,TickAction内で行ってください

    for (TArray<FActionAttackTargetData>::TIterator Ite(ActionResult.ActionAttackResult.AttackTargets); Ite; ++Ite)
    {
        float initHp = Ite->TargetUnit->GetHp();
        float NextHp = Ite->TargetUnit->GetHp() - Ite->HpDamage;
        float NextMp = Ite->TargetUnit->GetMp() - Ite->MpDamage;

        Ite->TargetUnit->SetHp(NextHp);
        Ite->TargetUnit->SetMp(NextMp);
        UE_LOG(LogTemp, Warning, TEXT("Hp: %f--> NextHp: %f"), initHp, NextHp);
    }
}

//  アクション開始
void UBattleActionAttack::BeginAction(FActionResultData& ActionResult, ABattleActionGameModeProxy* GameMode)
{
   

    BattleHelper    helper;
    if (AttackCamera == nullptr)
    {
        //  アニメーションなどの開始
        AttackState = EAttackState::MoveStartCamera;


        TSubclassOf<ABattleAttackCamera> BP_AttackCamera = helper.Load<ABattleAttackCamera>(BP_BATTLE_ATTACK_CAMERA_PATH);

        if (BP_AttackCamera == nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("FAILED BP_AttackCamera"));
        }
        else
        {
            AttackCamera = GetWorld()->SpawnActor<ABattleAttackCamera>(BP_AttackCamera);
            AttackCamera->CameraActor = GameMode->BattleCamera;
        }
    }


    if (AttackCamera)
    {
        BackupCameraEye = AttackCamera->CameraActor->GetActorLocation();
        BackupCameraRotator = AttackCamera->CameraActor->GetActorRotation();


        TObjectPtr<AUnitBattleParameter> SelectUnit = ActionResult.ActionUnit;
        FVector LoockAtLocation = ActionResult.ActionUnit->Get3DLocation();
        LoockAtLocation.Z = BATTLE_FILED_BLOCK_SIZE * 0.25f;
        FVector EyeLocation = AttackCamera->CameraActor->GetActorLocation();

        FVector EyeNextLocation = helper.CalcAttackAttackStartCameraPosition(SelectUnit->GetGameX(), SelectUnit->GetGameY());


        BackupAttackUnitLocation = SelectUnit->Get3DLocation();
        BackupAttackUnitRotator = SelectUnit->Get3DRotation();

        if (AttackCamera)
        {
            // 攻撃するアクターにカメラを合わせてカメラ移動開始
            AttackCamera->Initialize(
                EyeLocation,
                EyeNextLocation,
                LoockAtLocation,
                LoockAtLocation,
                BATTLE_ATTACK_CAMERA_MOVE_TIME,
                EMoveType::Normal,
                ECurveType::Sign
            );

            float waittime = 0.0f;
            switch (ActionResult.ActionUnit->GetJobID())
            {
            case EUnitJob::EUJ_Tank:
                // 戦士の特技処理
                waittime = 0.8f;
                break;
            case EUnitJob::EUJ_Rounder:
                // ラウンダーの特技処理
                waittime = 1.1f;
                break;
            case EUnitJob::EUJ_Healer:
                // ヒーラーの特技処理
                waittime = 1.15f;
                break;
            case EUnitJob::EUJ_Magician:
                // マジシャンの特技処理
                waittime = 1.1f;
                break;
            default:
                break;
            }

            //  行動をスタックに積む
            PushState(EAttackState::None);  //　終了ステートを設定
            PushState(EAttackState::MoveBack);  //　元に戻す
            PushState(EAttackState::Wait, 1.0f);    //  少し待ってからカメラ移動開始
            PushState(EAttackState::End);    //  終了処理
            PushState(EAttackState::AnimeWaitEnd);    //  攻撃アニメーション再生
            PushState(EAttackState::Attack, waittime);    //  攻撃
            PushState(EAttackState::Wait);
            PushState(EAttackState::PlayAnimAttack);    //  攻撃アニメーション再生
            PushState(EAttackState::PlayAnimWait);    //  待機アニメーション再生
            PushState(EAttackState::MoveToTarget);  //  ターゲット位置まで移動
            PushState(EAttackState::PlayAnimMove);  //  移動アニメーション再生
            PushState(EAttackState::MoveStartCamera);   //  カメラ移動開始
            PushState(EAttackState::Wait, 1.5f);    //  少し待ってからカメラ移動開始


            //  まず、カメラワークが終わるのを待つ
            AttackState = EAttackState::CameraFinishWait;
        }


    }

}

//  アクションTick
//  ActionResult    :   アクション結果
//  DeltaSecounds   :   細分時間
//  GameMode        :   ゲームモード
//  @Return         :   true 終了 : false 続行
bool UBattleActionAttack::TickAction(FActionResultData& ActionResult, float DeltaSecounds, ABattleActionGameModeProxy* GameMode)
{

    BattleHelper    helper;

    switch (AttackState)
    {
    case EAttackState::MoveStartCamera:
        {
            //  カメラが攻撃するユニットの前に移動し終わった
            TObjectPtr<AUnitBattleParameter> ActionUnit = ActionResult.ActionUnit;
            TObjectPtr<AUnitBattleParameter> TargetUnit = ActionResult.ActionAttackResult.AttackTargets[0].TargetUnit;
            FVector EyeStartLocation = AttackCamera->GetCurrentEyeLocation();
            FVector StartLookAtLocation = AttackCamera->GetCurrentLookAtLocation();
            FVector EndLookAtLocation = helper.CalcAttackActionPosition(TargetUnit->GetGameX(),TargetUnit->GetGameY(),ActionUnit->GetGameX(), ActionUnit->GetGameY());
            EndLookAtLocation.Z = StartLookAtLocation.Z;

            FVector Vec = EndLookAtLocation - StartLookAtLocation;
            Vec.Y = 0.0f;
            Vec.Normalize();
            FVector EyeNextLocation = EyeStartLocation + Vec * BATTLE_FILED_OFFSET_SIZE;
            AttackCamera->Initialize(
                EyeStartLocation,
                EyeNextLocation,
                StartLookAtLocation,
                EndLookAtLocation,
                BATTLE_ATTACK_CAMERA_ATTACK_MOVE_TIME,
                EMoveType::Normal,
                ECurveType::Sign
            );

            PopNextState();
        }
        return false;
    case EAttackState::MoveToTarget:
        FVector location = AttackCamera->GetCurrentLookAtLocation();
        location.Z = 0.0f;
        ActionResult.ActionUnit->Set3DLocation(location);
        if (AttackCamera->IsFinished())
        {
            PopNextState();
        }
        return false;
    case EAttackState::PlayAnimAttack:
        ActionResult.ActionUnit->PlayAnimationAttack();
        PopNextState();
        return false;
    case EAttackState::Attack:
        {
            for (TArray<FActionAttackTargetData>::TIterator Ite(ActionResult.ActionAttackResult.AttackTargets); Ite; ++Ite)
            {
                //  お前はもう死んでいる
                if (Ite->TargetUnit->IsDead()) {
#if 0
                    Ite->TargetUnit->SetVisible(false);
#else
                    Ite->TargetUnit->PlayAnimationDeath();
#endif
                }
                else
                {
                    FRotator rotation = FRotator::ZeroRotator;
                    Ite->TargetUnit->PlayAnimationDamage();
                    if (Ite->TargetUnit->GetTeamID() == EUnitTeamID::EUTID_Team2)
                    {
						rotation.Yaw = 180.0f;
                    }
					SpawnNiagaraEffect(Ite->TargetUnit->Get3DLocation(), rotation);
                }
            }

            PopNextState();
        }
        return false;
    case EAttackState::End:
        {
            bool EndOfAnim = true;;
            for (TArray<FActionAttackTargetData>::TIterator Ite(ActionResult.ActionAttackResult.AttackTargets); Ite; ++Ite)
            {
                //  アニメーションの終了まち
                if (!Ite->TargetUnit->IsEndOfAnime()) {
                    EndOfAnim = false;
                }
            }
            if (EndOfAnim)
            {
                PopNextState();
            }
        }
        return false;
    case EAttackState::Wait:
        {   // 指定秒数待ってから遷移移動
            if (AttackStateStack.Num() > 0)
            {
                FAttackStateWaitData& WaitData = AttackStateStack.Last();
                WaitData.WaitTime -= DeltaSecounds;
                if (WaitData.WaitTime <= 0.0f)
                {
                    PopNextState();
                }
            }
        }
        return false;
    case EAttackState::PlayAnimMove:
        {
            ActionResult.ActionUnit->PlayAnimationMove();
            PopNextState();
        }
        return false;
    case EAttackState::PlayAnimWait:
        ActionResult.ActionUnit->PlayAnimationWait();
        PopNextState();
        return false;
    case EAttackState::AnimeWaitEnd:
        if (ActionResult.ActionUnit->IsEndOfAnime())
        {
            PopNextState();
        }
        return false;
    case EAttackState::CameraFinishWait:
        {
            if (AttackCamera->IsFinished())
            {
                PopNextState();
            }
        }
        return false;
    case EAttackState::MoveBack:
        AttackCamera->CameraActor->SetActorLocation(BackupCameraEye);
        AttackCamera->CameraActor->SetActorRotation(BackupCameraRotator);
        ActionResult.ActionUnit->Set3DLocation(BackupAttackUnitLocation);
        ActionResult.ActionUnit->Set3DRotation(BackupAttackUnitRotator);

        PopNextState();
        return false;
    }



    return true;    //  trueで終了
}


void UBattleActionAttack::PushState(EAttackState NextState , float WaitTime )
{
    FAttackStateWaitData WaitData;
    WaitData.NextState = NextState;
    WaitData.WaitTime = WaitTime;
    AttackStateStack.Add(WaitData);
}


//  スタックより次のステートへ移行
void UBattleActionAttack::PopNextState()
{
    if (AttackStateStack.Num() > 0)
    {
        FAttackStateWaitData WaitData = AttackStateStack.Pop();
        AttackState = WaitData.NextState;
    }
}

void UBattleActionAttack::SpawnNiagaraEffect(const FVector& Location, const FRotator& Rotator)
{
    AttackNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, BATTLE_ATTACK_EFFECT);
    if (AttackNiagaraSystem)
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), AttackNiagaraSystem, Location, Rotator);
	}
}