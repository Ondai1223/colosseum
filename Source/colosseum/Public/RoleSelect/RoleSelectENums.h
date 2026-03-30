

#pragma	once

#include "Common/ComonDefine.h"

/**
 *	ロール選択で使う enum
 */

UENUM(BlueprintType)
enum class ERpoleSelectSlotState : uint8
{
    ERSSS_None          UMETA(DisplayName = "状態なし"),    // 状態なし
    ERSSS_SlotCansel    UMETA(DisplayName = "現在のスロットをキャンセル"),
    ERSSS_Selecting     UMETA(DisplayName = "職業選択中"),    // 選択中
    ERSSS_SelectingAnim UMETA(DisplayName = "職業選択アニメーション中"),    // 選択アニメーション中
    ERSSS_SelectingNext UMETA(DisplayName = "次の職業選択設定"),    // 選択アニメーション中
    ERSSS_SelectingCansel UMETA(DisplayName = "ロール選択キャンセル"),  //  ロール選択キャンセル

//    ERSSS_Arrangement_Begin UMETA(DisplayName = "ユニット配置開始"),  // ユニット配置開始
    ERSSS_Arrangement   UMETA(DisplayName = "ユニット配置中"),    // 未選択
//    ERRSS_ArrangementCansel UMETA(DisplayName = "ユニット配置キャンセル"),

    ERRSS_ReadyCansel   UMETA(DisplayName = "準備完了をキャンセル"),  //  準備完了をキャンセル
    ERRSS_CheckReady    UMETA(DisplayName = "ロール確定判定中"),    //  ロール確定判定中
    ERRSS_Ready    UMETA(DisplayName = "準備完了"),    //  準備完了

    ERRSSS_Refresh       UMETA(DisplayName = "リフレッシュ"),    //  リフレッシュ
};



UENUM(BlueprintType)
enum class ERoleSelectState : uint8
{
    ERS_None            UMETA(DisplayName = "状態なし"),    // 状態なし
    ERS_RoleSelect      UMETA(DisplayName = "ロールセレクト中"),  // ロールセレクト中
    ERS_Arrangement     UMETA(DisplayName = "ユニット配置中"),   // ユニット配置中

    ERS_Refresh         UMETA(DisplayName = "リフレッシュ"),   // リフレッシュ

};

UENUM(BlueprintType)
enum class EAUState : uint8
{
    EAUState_None               UMETA(DisplayName = "何もしない"),
    EAUState_Begin              UMETA(DisplayName = "開始"),
    EAUState_SelectPosition     UMETA(DisplayName = "配置処理"),
    EAUState_Selected           UMETA(DisplayName = "配置した"),
    EAUState_SelectPositionCansel UMETA(DisplayName = "配置キャンセル"),
    EAUState_StartPosX          UMETA(DisplayName = "X座標変更"),  //X座標変更
    EAUState_StartPosY          UMETA(DisplayName = "Y座標変更"),  //Y座標変更
    EAUState_ReadyWait          UMETA(DisplayName = "確定待ち"),
    EAUState_Ready              UMETA(DisplayName = "準備OK"),

    EASState_Refresh            UMETA(DisplayName = "リフレッシュ"),
};

// ロール選択のデータタイプ
UENUM(BlueprintType)
enum class ERoleSelectDataType : uint8
{
    ERSDT_None                UMETA(DisplayName = "何もしない"),
    ERSDT_Nagosiation         UMETA(DisplayName = "ネゴシエーション"),

    ERSDT_SlotState           UMETA(DisplayName = "スロットステート"),
    ERSDT_SlotSelectIndex     UMETA(DisplayName = "スロット選択インデックス"),
    ERSDT_GetReady            UMETA(DisplayName = "出撃完了状態"),

    ERSDT_RoleSelectState     UMETA(DisplayName = "ロール選択ステート"),
    ERSDT_RoleSelectIndex     UMETA(DisplayName = "ロール選択、キャラクタのインデックス"),
    ERSDT_RoleSelectJob       UMETA(DisplayName = "ジョブの選択"),
    ERSDT_RoleSelectJobBefore UMETA(DisplayName = "前回のジョブ"),
    ERSDT_RoleSelectTime      UMETA(DisplayName = "ジョブ遷移時間"),
    ERSDT_RoleSelectTimeMax   UMETA(DisplayName = "ジョブ遷移時間最大値"),

    ERSDT_CallID              UMETA(DisplayName = "コールID"),
//    ERSDT_ArrangementState    UMETA(DisplayName = "配置遷移"),
//    ERSDT_ArrangementStartX   UMETA(DisplayName = "X座標"),
//    ERSDT_ArrangementStartY   UMETA(DisplayName = "Y座標"),


    ERSDT_Refresh              UMETA(DisplayName = "リフレッシュ"),
};

//  コールＩＤ(ChangeState_～始まる関数を呼ぶ)
UENUM(BlueprintType)
enum class ERoleSelectCallID : uint8
{
    ERSCID_None         UMETA(DisplayName = "なし"),

    ERSCID_ChangeState_Selecting     UMETA(DisplayName = "ロール選択準備"),
    ERSCID_ChangeState_SelectingNext UMETA(DisplayName = "ロール選択切り替えのタイミング"),
    ERSCID_ChangeState_BeforeSlot    UMETA(DisplayName = "一つ前のスロットに戻す"),
    ERSCID_ChangeState_RoleSelectingToNone UMETA(DisplayName = "ロールセレクトからスロットに戻る処理"),
    ERSCID_ChangeState_ToArrangement  UMETA(DisplayName = "ユニット配置画面へ"),
    ERSCID_ChangeState_ReadyCansel   UMETA(DisplayName = "レディ待ち状態からキャンセル"),
    ERSCID_ChangeState_SelectPositionCansel UMETA(DisplayName = "配置処理キャンセル"),
};
