// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "RoleSelect/RoleSelectDefines.h"

#include "RoleSelectCursor.generated.h"
#define MOVE_CURSOR_TIME 0.25f


#define MOVE_CURSOR_DEAD_ZONE FLT_EPSILON


UCLASS()
class COLOSSEUM_API ARoleSelectCursor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoleSelectCursor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




public:

    //  ロール選択後配置カーソル
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void CreateRoleArrangementCursor();


    //  カーソルのスタート位置設定
    UFUNCTION(BlueprintCallable, Category = CATEGORY_RoleSelect)
    void SetCursorPosition(int X = 1, int Y = 0);



public:

    struct FMoveCursorData
    {
        uint8 X = 1; // Xカーソル位置
        uint8 Y = 0;    // Yカーソル位置
        uint8 BeforeX = 1; // 前回のXカーソル位置
        uint8 BeforeY = 0; // 前回のYカーソル位置
        float MoveTime = MOVE_CURSOR_TIME; // カーソル移動時間
        float MoveNowTime = MOVE_CURSOR_TIME; // カーソル移動の補間値
    };

    FMoveCursorData MoveCursorData;


    void StartMoveCursor(int X, int Y, float MoveTime = MOVE_CURSOR_TIME);
    
    //  true:移動中 false:移動完了 
    bool MoveCursor( float DeltaTime,FVector* NowLocation = nullptr);

private:
    UPROPERTY(Transient)
    TObjectPtr<UNiagaraComponent> CursorEffectComponent;

    UPROPERTY(Transient)
    TObjectPtr<UStaticMeshComponent> CursorModel; // ユニットのメッシュコンポーネント

    UPROPERTY(Transient)
    TObjectPtr<UNiagaraSystem> RoleArrangementCursor;
};
