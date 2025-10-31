// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleCommandWidget.generated.h"
class ABattleGameMode;
class AUnitBattleParameter;


/**
 * バトルコマンドウイジェット
 */
UCLASS()
class COLOSSEUM_API UBattleCommandWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    //  ウイジェット構築
    virtual void NativeConstruct();


public:
    //  バトルコマンド開始
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void BeginBattleCommand(ABattleGameMode* BattleGameMode, AUnitBattleParameter* BattleUnit);
    virtual void BeginBattleCommand_Implementation(ABattleGameMode* GameMode, AUnitBattleParameter* BattleUnit);

    //  Tickバトルコマンド
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void TickBattleCommand(float DeltaSeconds);
    virtual void TickBattleCommand_Implementation(float DeltaSeconds);

    //  バトルコマンド終了
    UFUNCTION(BlueprintNativeEvent, Category = CATEGORY_Battle)
    void ReleaseBattleCommand(float DeltaSeconds);
    virtual void ReleaseBattleCommand_Implementation(float DeltaSeconds);

    //  全ての矢印を非表示
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void ArrowAllHiddn();


    //  カーソル設定(AddCursorに0を指定するとスタックオーバーフローを起こします。必ず。1か-1を設定してください)
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void SetArrow(int AddCursor);

    //  コマンド選択処理(戻り値：コマンド確定したらそのコマンドを返す。まだならEBattleCommand::NONEを返す)
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    EBattleCommand RunSelectCommand(float DeltaSeconds);

    //  選択コマンドをセット
    UFUNCTION(BlueprintCallable, Category = CATEGORY_Battle)
    void SetSelectedCommand();

public:

    //  ゲームモード
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TObjectPtr<ABattleGameMode> GameMode;

    //  選択ユニット
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    TObjectPtr<AUnitBattleParameter>    SelectUnit;

    //  選択カーソル
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    int    SelectCursor = 0;

    //  バトルコマンドのステート
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_Battle)
    EBattleCommand  Command;


private:
    //  矢印ウイジェット
    TArray<TObjectPtr<UUserWidget>>  BattleArrows;
};
