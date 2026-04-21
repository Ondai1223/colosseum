// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/BattleActionSkill.h"
#include "Battle/BattleGameMode.h"
#include "NiagaraFunctionLibrary.h"
#include "Battle/BuffAttack.h"
#include "Battle/BuffDefense.h"
#include "Battle/BuffMove.h"
#include "Battle/DebuffAttack.h"
#include "Battle/DebuffDefense.h"
#include "Battle/DebuffMove.h"
#include "Battle/BattleSkillWindow.h"

#ifndef ENABLE_BATTLE_ACTION_INTERFACE_GAME_MODE_PROXY
#include "Battle/BattleGameMode.h"
#else
#include "Battle/BattleGameModeProxy.h"
#endif // !ENABLE_BATTLE_ACTION_INTERFACE_GAME_MODE_PROXY




#define ATTACK_PARAMETER 15
#define HEAL_PARAMETER -1.5
#define SPECIAL_PARAMETER 2
#define FireType FName(TEXT("Fire"))
#define WaterType FName(TEXT("Water"))
#define ThunderType FName(TEXT("Thunder"))

#define BP_BATTLE_SKILL_CAMERA_PATH TEXT("/Game/Battle/Blueprints/BP_BattleAttackCamera.BP_BattleAttackCamera_C")  /// BP_Unit
#define BATTLE_SKILL_CAMERA_MOVE_TIME 0.01f
#define BATTLE_SKILL_CAMERA_SKILL_MOVE_TIME 1.5f

#define BATTLE_ATTACK_SKILL_EFFECT TEXT("/Game/FixEffect/BattleEffect/Ef_Btl_Attack_02.Ef_Btl_Attack_02")
#define BATTLE_ATTACK_SKILL_FIRE_EFFECT TEXT("/Game/FixEffect/BattleEffect/Ef_Btl_Hinoko.Ef_Btl_Hinoko")
#define BATTLE_ATTACK_SKILL_WATER_EFFECT TEXT("/Game/FixEffect/BattleEffect/Ef_Elm_Water_01.Ef_Elm_Water_01")
#define BATTLE_ATTACK_SKILL_THUNDER_EFFECT TEXT("/Game/FixEffect/BattleEffect/Ef_Elm_Thunder_01.Ef_Elm_Thunder_01")

#define BATTLE_HEAL_SKILL_EFFECT TEXT("/Game/FixEffect/BattleEffect/Ef_Btl_Heal.Ef_Btl_Heal")
#define BATTLE_BUFF_SKILL_EFFECT TEXT("/Game/FixEffect/BattleEffect/Ef_Btl_Buff.Ef_Btl_Buff")
#define BATTLE_DEBUFF_SKILL_EFFECT TEXT("/Game/FixEffect/BattleEffect/Ef_Btl_Debuff.Ef_Btl_Debuff")

//  選択パネルの設定
//  CenterGameX     :   中心となるX座標
//  CenterGameY     :   中心となるX座標
//  GameMode        :   ゲームモード
void UBattleActionSkill::SetSelectPanel(int CenterGameX, int CenterGameY, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleActionGameModeProxy* GameMode, const FSkillDataType& SkillData)
{
    FName TargetId = SkillData.target_id;

    if (TargetId == TEXT("self"))
    {
        GameMode->BattleSelector->SetPanel(CenterGameX, CenterGameY, true);
    }
    else if (TargetId == TEXT("self_and_back"))
    {
        GameMode->BattleSelector->SetPanel(CenterGameX, CenterGameY, true);
        GameMode->BattleSelector->SetPanel(CenterGameX, CenterGameY + 1, true);
    }
    else if (TargetId == TEXT("self_line"))
    {
        EUnitTeamID MyTeam = ActionUnit->GetTeamID();
        const TArray<TObjectPtr<AUnitBattleParameter>>& MyTeamUnits = (MyTeam == EUnitTeamID::EUTID_Team1) ? GameMode->Player1UnitsActors : GameMode->Player2UnitsActors;
        
        TArray<int32> TargetRows;
        for (const auto& Ally : MyTeamUnits)
        {
            if (Ally && !Ally->IsDead())
            {
                TargetRows.AddUnique(Ally->GetGameY());
            }
        }

        for (int32 y : TargetRows)
        {
            for (int x = 0; x < GAME_LOCATION_WIDTH; ++x)
            {
                GameMode->BattleSelector->SetPanel(x, y, true);
            }
        }
    }
    else if (TargetId == TEXT("other"))
    {
        EUnitTeamID MyTeam = ActionUnit->GetTeamID();
        const TArray<TObjectPtr<AUnitBattleParameter>>& EnemyUnits = (MyTeam == EUnitTeamID::EUTID_Team1) ? GameMode->Player2UnitsActors : GameMode->Player1UnitsActors;
        for (const auto& Enemy : EnemyUnits)
        {
            if (Enemy && !Enemy->IsDead())
            {
                GameMode->BattleSelector->SetPanel(Enemy->GetGameX(), Enemy->GetGameY(), true);
            }
        }
    }
    else if (TargetId == TEXT("other_line"))
    {
        EUnitTeamID MyTeam = ActionUnit->GetTeamID();
        const TArray<TObjectPtr<AUnitBattleParameter>>& EnemyUnits = (MyTeam == EUnitTeamID::EUTID_Team1) ? GameMode->Player2UnitsActors : GameMode->Player1UnitsActors;
        
        TArray<int32> TargetRows;
        for (const auto& Enemy : EnemyUnits)
        {
            if (Enemy && !Enemy->IsDead())
            {
                TargetRows.AddUnique(Enemy->GetGameY());
            }
        }

        for (int32 y : TargetRows)
        {
            for (int x = 0; x < GAME_LOCATION_WIDTH; ++x)
            {
                GameMode->BattleSelector->SetPanel(x, y, true);
            }
        }
    }

    return;
}


//  スキル選択開始
//  ActionUnit      :   スキルを行使するユニット
//  GameMode        :   ゲームモード
void UBattleActionSkill::SelectSkillBegin(TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleActionGameModeProxy* GameMode)
{
    // TODO: マスターデータ作成後対応。ESkillArea等を用意し、Area毎にUnitからの相対位置を計算する予定
    GameMode->InGameWidget->OpenSkillWindow();
    if (GameMode->InGameWidget)
    {
        GameMode->InGameWidget->ResetSelection(ActionUnit->GetJobID());
    }
}

//  スキル選択のTick
//  -1でまだ選択が終わっていない
//  -2でキャンセル
//  0以上で選択したスキル
int UBattleActionSkill::SelectSkillTick(TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleActionGameModeProxy* GameMode, FSkillDataType& OutSkillData)
{
    // TODO: UnitのIDからマスターデータ参照でSkillID取得。SkillID→Skill情報の取得で実装する予定
    
    // 入力を取得
    FVector2D Axis = GameMode->BattleController->GetLeftAxisTrigger();
    
    if (Axis.Size() > 0.1f)
    {
        UE_LOG(LogTemp, Log, TEXT("SelectSkillTick: Axis Input detected Y=%f"), Axis.Y);
    }

    // 選択の移動
    if (GameMode->InGameWidget)
    {
        if (Axis.Y > 0.5f)
        {
            UE_LOG(LogTemp, Log, TEXT("SelectSkillTick: Moving Prev via Proxy"));
            GameMode->InGameWidget->PrevSkill();
        }
        else if (Axis.Y < -0.5f)
        {
            UE_LOG(LogTemp, Log, TEXT("SelectSkillTick: Moving Next via Proxy"));
            GameMode->InGameWidget->NextSkill();
        }
    }
    
    // 決定
    if (GameMode->BattleController->IsOkTrigger())
    {
        UE_LOG(LogTemp, Log, TEXT("SelectSkillTick: OK Trigger detected"));
        if (GameMode->InGameWidget)
        {
            FSkillDataType SelectedData = GameMode->InGameWidget->GetSelectedSkillData();
            UE_LOG(LogTemp, Log, TEXT("SelectSkillTick: Confirmed SkillName=%s"), *SelectedData.skill_name.ToString());
            OutSkillData = SelectedData;
            return BATTLE_ACTION_SKILL_SELECT_DECIDE;
        }
    }
    
    // キャンセル
    if (GameMode->BattleController->IsCanselTrigger())
    {
        UE_LOG(LogTemp, Log, TEXT("SelectSkillTick: Cansel Trigger detected"));
        return -2;
    }

    return -1; // 選択待ち状態にする
}

//  アクション計算
//  ActionResult    :   アクション結果格納先
//  TargetLocations :   ターゲットするゲーム座標
//  ActionUnit      :   アクションを起こすユニット
//  GameMode        :   ゲームモード
//  SkillID         :   スキルID(特技を選択した時のみ有効）
void UBattleActionSkill::CalcAction(FActionResultData* ActionResult, const TArray<FGameLocation>& TargetLocations, TObjectPtr<AUnitBattleParameter>& ActionUnit, ABattleActionGameModeProxy* GameMode, const FSkillDataType& SkillData)
{
    ActionResult->ActionUnit = ActionUnit;
    ActionResult->ActionSkillResult.SkillID = 0; // TODO: SkillDataに含まれるIDを使用するなどの対応が必要だが、現状uint32なので0固定かハッシュ値など検討
    // FSkillDataTypeをActionResultに持たせるのがベストだが、BreakingChangeが広がりすぎるため一旦保留
    // 必要に応じて FActionResultData 側も改修すべきだが、今回のスコープではInterface対応を優先
	SelectLocations.Empty();
    for (TArray<FGameLocation>::TConstIterator Ite(TargetLocations); Ite; ++Ite)
    {
        TObjectPtr Target = GameMode->GetUnit(Ite->X, Ite->Y);
		SelectLocations.Add(*Ite);
        ActionResult->ActionSkillResult.SkillData = SkillData;
        if (Target)
        {
            FActionAttackTargetData TargetData;
            TargetData.TargetUnit = Target;
            // FActionTargetAndLocationへの情報格納
            FActionTargetAndLocation TargetLocation;
            TargetLocation.Location.X = Ite->X;
            TargetLocation.Location.Y = Ite->Y;
            TargetLocation.Target = Target;
            // FActionSkillkResultDataへの情報格納
            ActionResult->ActionSkillResult.TargetUnits.Add(TargetLocation);

            // ダメージ計算
            // 攻撃力(行動キャラ)＊特技倍率 / 防御力(被)＊攻撃倍率＝ダメージ
			float attackPower = ActionUnit->GetAttackPower(); // 攻撃力
            float defensePower = Target->GetDefencePower(); // 防御力
			float multiplier = SkillData.btl_skl_attack; // 特技倍率
            float calculatedDamage = 0.0f;
            switch (SkillData.skill_ability) 
            {
                case ESkillAbility::Attack:
                    calculatedDamage = (attackPower * multiplier) / defensePower * ATTACK_PARAMETER; // 物理攻撃時の計算式
				    break;
                case ESkillAbility::Heal:
                    UE_LOG(LogTemp, Warning, TEXT("回復の計算"));
                    calculatedDamage = attackPower * multiplier * HEAL_PARAMETER; // 回復時の計算式
                    break;
				case ESkillAbility::Buff:
                    UE_LOG(LogTemp, Warning, TEXT("バフの計算"));
                    // calculatedDamage = 1.3f; // バフ時の計算式
                    break;
                case ESkillAbility::Debuff:
                    UE_LOG(LogTemp, Warning, TEXT("デバフの計算"));
                    // calculatedDamage = 1.3f; //デバフ時の計算式
					break;
            }
            

            // Clamp(変数, Min, Max);変数の取りうる値を制限する.
            calculatedDamage = FMath::Clamp(calculatedDamage, -Target->GetMaxHp(), Target->GetMaxHp());
            
            // MPコストの記録（一回だけ設定されれば良いが、計算ループ内でも一貫性のためセット）
            ActionResult->ActionSkillResult.MpCost = SkillData.btl_skl_cost;

            UE_LOG(LogTemp, Warning, TEXT("攻撃特技の計算：calculatedDamage: %f, attackPower: %f, defensePower: %f, btl_skl_attack: %f"), calculatedDamage, attackPower, defensePower, SkillData.btl_skl_attack);

            TargetData.HpDamage = calculatedDamage;
            TargetData.MpDamage = 0.0f;
            ActionResult->ActionAttackResult.AttackTargets.Add(TargetData);
        }
    }


}

//  アクション結果を反映
//  ActionResult    :   結果格納先
//  GameMode        :   ゲームモード
void UBattleActionSkill::ReflectAction(FActionResultData& ActionResult, ABattleActionGameModeProxy* GameMode)
{
    // TODO: 一旦BattleActionAttackに合わせておく。マスターデータ対応後、計算式を書く
    for (TArray<FActionAttackTargetData>::TIterator Ite(ActionResult.ActionAttackResult.AttackTargets); Ite; ++Ite)
    {
        float NextHp = Ite->TargetUnit->GetHp() - Ite->HpDamage;
        float NextMp = Ite->TargetUnit->GetMp() - Ite->MpDamage;

		// 過剰に回復などしないように、HPとMPの値を0～最大値の範囲内に収める
        NextHp = FMath::Clamp(NextHp, 0.0f, Ite->TargetUnit->GetMaxHp());
        NextMp = FMath::Clamp(NextMp, 0.0f, Ite->TargetUnit->GetMaxMp());

        Ite->TargetUnit->SetHp(NextHp);
        Ite->TargetUnit->SetMp(NextMp);
    }

    // MPコストを適用
    if (ActionResult.ActionUnit)
    {
        float NextMp = ActionResult.ActionUnit->GetMp() - ActionResult.ActionSkillResult.MpCost;
        ActionResult.ActionUnit->SetMp(FMath::Max(0.0f, NextMp));
        UE_LOG(LogTemp, Log, TEXT("Skill MP Cost Applied: %f, Remaining MP: %f"), ActionResult.ActionSkillResult.MpCost, ActionResult.ActionUnit->GetMp());
    }
}

//  アクション開始
void UBattleActionSkill::BeginAction(FActionResultData& ActionResult, ABattleActionGameModeProxy* GameMode)
{
    /*
    BattleHelper    helper;
    if (SkillCamera == nullptr)
    {
        //  アニメーションなどの開始
        SkillState = ESkillState::MoveStartCamera;


        TSubclassOf<ABattleAttackCamera> BP_SkillCamera = helper.Load<ABattleAttackCamera>(BP_BATTLE_SKILL_CAMERA_PATH);

        if (BP_SkillCamera == nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("FAILED BP_SkillCamera"));
        }
        else
        {
            SkillCamera = GetWorld()->SpawnActor<ABattleAttackCamera>(BP_SkillCamera);
            SkillCamera->CameraActor = GameMode->BattleCamera;
        }
    }

    if (SkillCamera)
    {
        BackupCameraEye = SkillCamera->CameraActor->GetActorLocation();
        BackupCameraRotator = SkillCamera->CameraActor->GetActorRotation();


        TObjectPtr<AUnitBattleParameter> SelectUnit = ActionResult.ActionUnit;
        FVector LookAtLocation = ActionResult.ActionUnit->Get3DLocation();
        LookAtLocation.Z = BATTLE_FILED_BLOCK_SIZE * 0.25f;
        FVector EyeLocation = SkillCamera->CameraActor->GetActorLocation();

        FVector EyeNextLocation = helper.CalcAttackAttackStartCameraPosition(SelectUnit->GetGameX(), SelectUnit->GetGameY());


        BackupSkillUnitLocation = SelectUnit->Get3DLocation();
        BackupSkillUnitRotator = SelectUnit->Get3DRotation();
        

        if (SkillCamera)
        {
            // 攻撃するアクターにカメラを合わせてカメラ移動開始
            SkillCamera->Initialize(
                EyeLocation,
                EyeNextLocation,
                LookAtLocation,
                LookAtLocation,
                BATTLE_SKILL_CAMERA_MOVE_TIME,
                EMoveType::Normal,
                ECurveType::Sign
            );*/

            float waittime = 0.0f;
            switch (ActionResult.ActionUnit->GetJobID())
            {
            case EUnitJob::EUJ_Tank:
                // 戦士の特技処理
                waittime = 1.0f;
                break;
            case EUnitJob::EUJ_Rounder:
                // ラウンダーの特技処理
                waittime = 1.5f;
                break;
            case EUnitJob::EUJ_Healer:
                // ヒーラーの特技処理
                waittime = 1.0f;
                break;
            case EUnitJob::EUJ_Magician:
                // マジシャンの特技処理
                waittime = 2.5f;
                break;
            default:
                break;
            }
            // 行動をスタックする
            PushState(ESkillState::None);
            //PushState(ESkillState::MoveBack);  //　元に戻す
            //PushState(ESkillState::Wait, 1.0f);    //  少し待ってからカメラ移動開始
            //PushState(ESkillState::End);    //  終了処理
            PushState(ESkillState::AnimeWaitEnd);
            PushState(ESkillState::Skill, waittime);
            PushState(ESkillState::Wait);
            //PushState(ESkillState::PlayAnimSkill);    //  攻撃アニメーション再生
            //PushState(ESkillState::PlayAnimWait);    //  待機アニメーション再生
            //PushState(ESkillState::MoveToTarget);  //  ターゲット位置まで移動
            //PushState(ESkillState::PlayAnimMove);  //  移動アニメーション再生
            //PushState(ESkillState::MoveStartCamera);   //  カメラ移動開始
            //PushState(ESkillState::Wait, 1.5f);    //  少し待ってからカメラ移動開始

            SkillState = ESkillState::PlayAnimSkill;
        }
 //   }
//}

//  アクションTick
//  ActionResult    :   アクション結果
//  DeltaSecounds   :   細分時間
//  GameMode        :   ゲームモード
//  @Return         :   true 終了 : false 続行
bool UBattleActionSkill::TickAction(FActionResultData& ActionResult, float DeltaSecounds, ABattleActionGameModeProxy* GameMode)
{
    BattleHelper    helper;
    switch (SkillState)
    {
    case ESkillState::MoveStartCamera:
        {
        //  カメラが攻撃するユニットの前に移動し終わった
        TObjectPtr<AUnitBattleParameter> ActionUnit = ActionResult.ActionUnit;
        TObjectPtr<AUnitBattleParameter> TargetUnit = ActionResult.ActionAttackResult.AttackTargets[0].TargetUnit;
        FVector EyeStartLocation = SkillCamera->GetCurrentEyeLocation();
        FVector StartLookAtLocation = SkillCamera->GetCurrentLookAtLocation();
        FVector EndLookAtLocation = helper.CalcAttackActionPosition(TargetUnit->GetGameX(), TargetUnit->GetGameY(), ActionUnit->GetGameX(), ActionUnit->GetGameY());
        EndLookAtLocation.Z = StartLookAtLocation.Z;

        FVector Vec = EndLookAtLocation - StartLookAtLocation;
        Vec.Y = 0.0f;
        Vec.Normalize();
        FVector EyeNextLocation = EyeStartLocation + Vec * BATTLE_FILED_OFFSET_SIZE;
        SkillCamera->Initialize(
            EyeStartLocation,
            EyeNextLocation,
            StartLookAtLocation,
            EndLookAtLocation,
            BATTLE_SKILL_CAMERA_SKILL_MOVE_TIME,
            EMoveType::Normal,
            ECurveType::Sign
        );

        PopNextState();
        }
    return false;
    case ESkillState::MoveToTarget:
        FVector location = SkillCamera->GetCurrentLookAtLocation();
        location.Z = 0.0f;
        ActionResult.ActionUnit->Set3DLocation(location);
        if (SkillCamera->IsFinished())
        {
            PopNextState();
        }
        return false;
    case ESkillState::Wait:
    {
        // 指定秒数待ってから遷移移動
        if (SkillStateStack.Num() > 0)
        {
            FSkillStateWaitData& WaitData = SkillStateStack.Last();
            WaitData.WaitTime -= DeltaSecounds;
            if (WaitData.WaitTime <= 0.0f)
            {
                PopNextState();
            }
        }
    }
    return false;
    case ESkillState::PlayAnimSkill:
    {
        ESkillAbility Ability = ActionResult.ActionSkillResult.SkillData.skill_ability;

        // スキルアニメーション再生
        if (ActionResult.ActionUnit)
        {
            if (ActionResult.ActionSkillResult.SkillData.skill_ability == ESkillAbility::Attack)
            {
				ActionResult.ActionUnit->PlayAnimationSkillAttack();
            }
            else
            {
                ActionResult.ActionUnit->PlayAnimationBuf();
            }
        }
        
        PopNextState();
    }
    return false;
    case ESkillState::Skill:
    {
        // スキル処理
        FName Type = ActionResult.ActionSkillResult.SkillData.element_id;
        UBuffDebuffBase* Buff;
		EBuffDebuffType BuffDebuffType = ActionResult.ActionSkillResult.SkillData.buffdebuff_type;
		ESkillAbility Ability = ActionResult.ActionSkillResult.SkillData.skill_ability;
		float Parameter = ActionResult.ActionSkillResult.SkillData.btl_skl_attack;
        for (TArray<FActionAttackTargetData>::TIterator Ite(ActionResult.ActionAttackResult.AttackTargets); Ite; ++Ite)
        {
            switch (Ability)
            {
                case ESkillAbility::Attack:
                    if (Ite->TargetUnit->IsDead())
                    {
                        Ite->TargetUnit->PlayAnimationDeath();
                    }
                    else
                    {
						
                        FRotator rotation = FRotator::ZeroRotator;
                        Ite->TargetUnit->PlayAnimationDamage();

                        if (Ite->TargetUnit->GetTeamID() == EUnitTeamID::EUTID_Team2)
                        {
                            rotation.Yaw = 180.0f;
                        }
                        SpawnAttackNiagaraEffect(Ite->TargetUnit->Get3DLocation(), rotation, Type);
                    }
                    break;
                case ESkillAbility::Heal:
					SpawnOthersNiagaraEffect(Ite->TargetUnit->Get3DLocation(), FRotator::ZeroRotator, Ability);
                    break;
                case ESkillAbility::Buff:
                    // SpawnOthersNiagaraEffect(Ite->TargetUnit->Get3DLocation(), FRotator::ZeroRotator, Ability);
                    if (BuffDebuffType == EBuffDebuffType::EBT_ATTACK)
                    {
                        Buff = NewObject<UBuffAttack>(Ite->TargetUnit);
                        Buff->Init(2, Parameter, Ite->TargetUnit->Get3DLocation());
                        Ite->TargetUnit->AddBuffDebuff(Buff);
                    }
                    if (BuffDebuffType == EBuffDebuffType::EBT_DEFENSE)
                    {
                        Buff = NewObject<UBuffDefense>(Ite->TargetUnit);
                        Buff->Init(2, Parameter, Ite->TargetUnit->Get3DLocation());
                        Ite->TargetUnit->AddBuffDebuff(Buff);
                    }
                    
                    break;
                case ESkillAbility::Debuff:
                    // SpawnOthersNiagaraEffect(Ite->TargetUnit->Get3DLocation(), FRotator::ZeroRotator, Ability);
                    if (BuffDebuffType == EBuffDebuffType::EBT_ATTACK)
                    {
                        Buff = NewObject<UDebuffAttack>(Ite->TargetUnit);
                        Buff->Init(2, Parameter, Ite->TargetUnit->Get3DLocation());
                        Ite->TargetUnit->AddBuffDebuff(Buff);
                    }
                    if (BuffDebuffType == EBuffDebuffType::EBT_DEFENSE)
                    {
                        Buff = NewObject<UDebuffDefense>(Ite->TargetUnit);
                        Buff->Init(2, Parameter, Ite->TargetUnit->Get3DLocation());
                        Ite->TargetUnit->AddBuffDebuff(Buff);
                    }
                    break;
                default:
                    break;
			}
        }
        
        for (TArray<FGameLocation>::TConstIterator Ite(SelectLocations); Ite; ++Ite)
        {
            UE_LOG(LogTemp, Warning, TEXT("Skill Target Location: X=%d, Y=%d"), Ite->X, Ite->Y);
            
            if (Type == FName(TEXT("None")))
            {
                UE_LOG(LogTemp, Warning, TEXT("スキルの属性はNoneです"));
            }
            else
            {
                GameMode->MasoManager->JoinMaso(Ite->X, Ite->Y, Type, ActionResult.ActionUnit, GameMode);
            }
        }

        PopNextState();
    }
    return false;
    case ESkillState::End:
    {
        bool EndOfAnim = true;
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
    case ESkillState::PlayAnimMove:
    {
        ActionResult.ActionUnit->PlayAnimationMove();
        PopNextState();
    }
    return false;
    case ESkillState::PlayAnimWait:
        ActionResult.ActionUnit->PlayAnimationWait();
        PopNextState();
        return false;
    case ESkillState::AnimeWaitEnd:
    {
        // 行動アニメーションの終了待ち
        if (ActionResult.ActionUnit->IsEndOfAnime())
        {
            PopNextState();
        }
        return false;
    }
    case ESkillState::CameraFinishWait:
    {
        if (SkillCamera->IsFinished())
        {
            PopNextState();
        }
    }
    return false;
    case ESkillState::MoveBack:
        SkillCamera->CameraActor->SetActorLocation(BackupCameraEye);
        SkillCamera->CameraActor->SetActorRotation(BackupCameraRotator);
        ActionResult.ActionUnit->Set3DLocation(BackupSkillUnitLocation);
        ActionResult.ActionUnit->Set3DRotation(BackupSkillUnitRotator);

        PopNextState();
        return false;
    }
	return true; // trueで終了, falseで続行
}

void UBattleActionSkill::PushState(ESkillState NextState, float WaitTime)
{
    FSkillStateWaitData WaitData;
    WaitData.NextState = NextState;
    WaitData.WaitTime = WaitTime;
    SkillStateStack.Add(WaitData);
}

//  スタックより次のステートへ移行
void UBattleActionSkill::PopNextState()
{
    if (SkillStateStack.Num() > 0)
    {
        FSkillStateWaitData WaitData = SkillStateStack.Pop();
        SkillState = WaitData.NextState;
    }
}

void UBattleActionSkill::SpawnAttackNiagaraEffect(const FVector& Location, const FRotator& Rotator, const FName Type)
{
    if (Type == FName(TEXT("Fire")))
    {
        UE_LOG(LogTemp, Warning, TEXT("Niagara Effect Spawned: Fire"));
        SkillNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, BATTLE_ATTACK_SKILL_FIRE_EFFECT);
    }
    else if (Type == FName(TEXT("Water")))
    {
        UE_LOG(LogTemp, Warning, TEXT("Niagara Effect Spawned: Water"));
        SkillNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, BATTLE_ATTACK_SKILL_WATER_EFFECT);
    }
    else if(Type == FName(TEXT("Thunder")))
    {
        UE_LOG(LogTemp, Warning, TEXT("Niagara Effect Spawned: Thunder"));
        SkillNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, BATTLE_ATTACK_SKILL_THUNDER_EFFECT);
    }
    else if (Type == FName(TEXT("None")))
    {
        UE_LOG(LogTemp, Warning, TEXT("Niagara Effect Spawned: None"));
        SkillNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, BATTLE_ATTACK_SKILL_EFFECT);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Niagara Effect Spawned: Unknown Type"));
	}
    
    if (SkillNiagaraSystem)
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SkillNiagaraSystem, Location, Rotator);
    }
}

void UBattleActionSkill::SpawnOthersNiagaraEffect(const FVector& Location, const FRotator& Rotator, const ESkillAbility Ability)
{
    switch (Ability)
    {
        case ESkillAbility::Heal:
            SkillNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, BATTLE_HEAL_SKILL_EFFECT);
            break;
        case ESkillAbility::Buff:
            SkillNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, BATTLE_BUFF_SKILL_EFFECT);
            break;
        case ESkillAbility::Debuff:
            SkillNiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, BATTLE_DEBUFF_SKILL_EFFECT);
            break;
        default:
            UE_LOG(LogTemp, Warning, TEXT("Unknown Skill Ability for Niagara Effect"));
            return;
	}

    if (SkillNiagaraSystem)
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SkillNiagaraSystem, Location, Rotator);
    }
}
