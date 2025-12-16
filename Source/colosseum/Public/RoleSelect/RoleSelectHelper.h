// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#define ROLE_SELECT_WIDTH 3 // ロールセレクトの幅
#define ROLE_SELECT_DEPTH 2 // ロールセレクトの奥行き


#define ROL_ARRAY_NUM (ROLE_SELECT_WIDTH * ROLE_SELECT_DEPTH) // ロールセレクトの配列数

#define ROLE_CRATE_UNIT_SCALE  FVector(0.8f,0.8f,0.8f)

/**
 * ロールセレクトヘルパークラス
 * NewObject や new でインスタンスを生成しないでください。
 */
class COLOSSEUM_API RoleSelectHelper
{
public:

    // コンストラクタ
    RoleSelectHelper();

    // デストラクタ
	~RoleSelectHelper();

public:

    //  添え字より座標を算出
    bool CalcPosition(int* OutX, int* OutY, int Num) const;

    //  座標より3D座標を算出
    FVector Calc3DLocation(int X, int Y) const;

};
