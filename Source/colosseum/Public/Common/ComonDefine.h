

#pragma once


#define CATEGORY_Common "Common"	//	共通カテゴリ

UENUM(BlueprintType)
enum class EBattleGameMode : uint8
{
    EBGM_Player_VS_Player       UMETA(DisplayName = "プレーヤーVSプレーヤー"),    // PC一台でプレーヤー同士で対戦
    EBGM_Player_VS_NPC          UMETA(DisplayName = "プレーヤーVS NPC"),    // PC一台でNPCと対戦
    EBGM_Player_VS_NET          UMETA(DisplayName = "プレーヤーVS プレーヤー（ネット対戦）"),    // PC２台でプレーヤー同士が対戦
};


