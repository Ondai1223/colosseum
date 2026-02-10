

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

#define UNIT_CURSOR_EFFECT_NAME TEXT("/Game/FixEffect/Cursoul/Ef_Cursoul.Ef_Cursoul")