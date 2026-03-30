#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterParameter.generated.h"

USTRUCT(BlueprintType)
struct FCharacterParameterDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText chara_name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float par_hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float par_mp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float par_attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float par_defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float par_move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float btl_par_attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float btl_par_defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float btl_par_heal;
};