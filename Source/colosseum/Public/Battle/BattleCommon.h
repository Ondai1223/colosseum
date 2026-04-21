

#pragma once

/**
 *バトル共通
 */

#define CATEGORY_BattleState "BattleState"


UENUM(BlueprintType)
enum class EBattleNetWorkMode : uint8
{
    EBNM_Normal         UMETA(DisplayName = "通常ゲーム"),
    EBNM_Server         UMETA(DisplayName = "サーバー"),
    EBNM_Client         UMETA(DisplayName = "クライアント"),
};



#define UNITDATA_DUMMY  // ダミーユニットデータの定義

UENUM(BlueprintType)
enum class EBattleTurn : uint8
{
    EBT_None        UMETA(DisplayName = "決まってない状態"),    // ターンなし
    EBT_Player1     UMETA(DisplayName = "ターンプレーヤー１"),  // プレイヤー1のターン
    EBT_Player2     UMETA(DisplayName = "ターンプレーヤー２"),   // プレイヤー2のターン
};

UENUM(BlueprintType)
enum class EBattleState : uint8
{
    EBS_Waiting            UMETA(DisplayName = "待機"),   // 待機中
    EBS_StartTurnDecision   UMETA(DisplayName = "先制後攻の決定"),// 先制後攻の決定
    EBS_Battle              UMETA(DisplayName = "戦闘中"), // 戦闘中
    EBS_NextTurn            UMETA(DisplayName = "次のターンに以降"),
    EBS_Result              UMETA(DisplayName = "結果表示"),       // 結果表示
    EBS_End                 UMETA(DisplayName = "バトル終了"),        //  バトル終了
};

UENUM(BlueprintType)
enum class EBattleResult : uint8
{
    EBR_None        UMETA(DisplayName = "結果なし"),    // 結果なし
    EBR_Player1Win  UMETA(DisplayName = "プレイヤー1の勝利"),  // プレイヤー1の勝利
    EBR_Player2Win  UMETA(DisplayName = "プレイヤー2の勝利"),   // プレイヤー2の勝利
    EBR_Draw        UMETA(DisplayName = "引き分け"),   // 引き分け
};


#define UNIT_CURSOR_EFFECT_NAME TEXT("/Game/FixEffect/Cursoul/Ef_Cursoul_01.Ef_Cursoul_01")

//  スキルアイコン
UENUM(BlueprintType)
enum class EBattleSkillIcon : uint8
{
    //  タンクのスキル
    EBSI_TANK_SHILED                            UMETA(DisplayName = "タンク：不沈の盾"),  // 不沈の盾
    EBSI_TANK_INTUITION                         UMETA(DisplayName = "タンク：研ぎ澄まされた勘"),  // 不屈の闘志
    EBSI_TANK_A_FURIOUS_STRIKE                  UMETA(DisplayName = "タンク：憤怒の一撃"),  // 憤怒の一撃
    EBSI_TANK_LIGHTNING_SPEAR                   UMETA(DisplayName = "タンク：迅雷槍"),  // 迅雷槍
    EBSI_TANK_UNYIELDING_PRESSURE               UMETA(DisplayName = "タンク：不屈の圧"),  // 不屈の圧

    //  ヒーラーのスキル
    EBSI_HEALER_CURE                            UMETA(DisplayName = "ヒーラー：キュア"),  // キュア
    EBSI_HEALER_CURLY                           UMETA(DisplayName = "ヒーラー：キュアリー"),  // キュアリー
    EBSI_HEALER_A_STRIKE_FROM_A_CLEAR_STREAM    UMETA(DisplayName = "ヒーラー：清流の一撃"),  // 清流の一撃
    EBSI_HEALER_MAKE_GUARDIAN                   UMETA(DisplayName = "ヒーラー：メイクガーディアン"),  // メイクガーディアン
    EBSI_HEALER_HORN_POWER                      UMETA(DisplayName = "ヒーラー：ホーンパワー"),  // ホーンパワー

    //  ラウンダーのスキル
    EBSI_ROUNDER_REVENGE_STEP                   UMETA(DisplayName = "ラウンダー：リベンジステップ"),  // リベンジステップ
    EBSI_ROUNDER_IMPORTANT_SWEETS               UMETA(DisplayName = "ラウンダー：大事なお菓子"),  // 大事なお菓子
    EBSI_ROUNDER_SPILL_RIPPER                   UMETA(DisplayName = "ラウンダー：スピルリッパー"),  // スピルリッパー
    EBSI_ROUNDER_FLAME_RIPPER                   UMETA(DisplayName = "ラウンダー：フレイムリッパー(仮)"),  // フレイムリッパー 
    EBSI_ROUNDER_PENETRATE                      UMETA(DisplayName = "ラウンダー：ペネトレイト"),  // ペネトレイト

    //  マジシャンのスキル
    EBSI_MAGICIAN_FOTIA                         UMETA(DisplayName = "マジシャン：フォティア"),  // フォティア
    EBSI_MAGICIAN_KATACT                        UMETA(DisplayName = "マジシャン：カタクト"),  // カタクト
    EBSI_MAGICIAN_ASTRAPE                       UMETA(DisplayName = "マジシャン：アストラペ"),  // アストラペ
    EBSI_MAGICIAN_MAGICAL_PATHOS                UMETA(DisplayName = "マジシャン：マジカルパトス"),  // マジカルパトス
    EBSI_MAGICIAN_FEELING_OF_REGRET             UMETA(DisplayName = "マジシャン：悔しい気持ち"),  // 悔しい気持ち
};


