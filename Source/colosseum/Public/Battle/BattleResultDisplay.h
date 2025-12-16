// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Battle/BattleGameMode.h"
#include "Battle/BattleHelper.h"
#include "Battle/BattleResultWidget.h"
#include "Battle/Interface/BattleResultDisplayInterface.h"
#include "BattleResultDisplay.generated.h"



/**
 *  戦闘結果表示アクター
 */
UCLASS(Blueprintable)
class COLOSSEUM_API ABattleResultDisplay : public AActor, public IBattleResultDisplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleResultDisplay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    //  戦闘結果表示の設定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    virtual void SetBattleResultDisplay(EBattleResult Result);

    //  戦闘結果表示の取得
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    virtual EBattleResult GetBattleResultDisplay() const;

    //  チーム名１の設定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    virtual void SetTeam1Name(const FString& name);

    //  チーム名１の取得
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    virtual const FString& GetTeam1Name() const;


    //  チーム名２の設定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    virtual void SetTeam2Name(const FString& name);

    //  チーム名２の取得
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    virtual const FString& GetTeam2Name() const;

public:
     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TObjectPtr<UBattleResultWidget> BattleResultWidget;



};
