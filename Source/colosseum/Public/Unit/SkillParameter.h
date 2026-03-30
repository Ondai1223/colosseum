#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillParameter.generated.h"

USTRUCT(BlueprintType)
struct FSkillParameterDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText skill_name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float btl_skl_attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float btl_skl_cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName skl_element;
};