// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "KawaiiPhysics/Public/KawaiiPhysicsSyncBone.h"
#include "Runtime/Engine/Classes/Curves/CurveFloat.h"
#include "Runtime/Engine/Public/Animation/BoneReference.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeKawaiiPhysicsSyncBone() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FBoneReference();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FRuntimeFloatCurve();
KAWAIIPHYSICS_API UEnum* Z_Construct_UEnum_KawaiiPhysics_ESyncBoneDirection();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone();
KAWAIIPHYSICS_API UScriptStruct* Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget();
UPackage* Z_Construct_UPackage__Script_KawaiiPhysics();
// End Cross Module References

// Begin Enum ESyncBoneDirection
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ESyncBoneDirection;
static UEnum* ESyncBoneDirection_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ESyncBoneDirection.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ESyncBoneDirection.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_KawaiiPhysics_ESyncBoneDirection, (UObject*)Z_Construct_UPackage__Script_KawaiiPhysics(), TEXT("ESyncBoneDirection"));
	}
	return Z_Registration_Info_UEnum_ESyncBoneDirection.OuterSingleton;
}
template<> KAWAIIPHYSICS_API UEnum* StaticEnum<ESyncBoneDirection>()
{
	return ESyncBoneDirection_StaticEnum();
}
struct Z_Construct_UEnum_KawaiiPhysics_ESyncBoneDirection_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Both.Comment", "/** \xe4\xb8\xa1\xe6\x96\xb9\xe3\x81\xae\xe6\x96\xb9\xe5\x90\x91\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe3\x82\x92\xe9\x81\xa9\xe7\x94\xa8 */" },
		{ "Both.Name", "ESyncBoneDirection::Both" },
		{ "Both.ToolTip", "\xe4\xb8\xa1\xe6\x96\xb9\xe3\x81\xae\xe6\x96\xb9\xe5\x90\x91\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe3\x82\x92\xe9\x81\xa9\xe7\x94\xa8" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsSyncBone.h" },
		{ "Negative.Comment", "/** \xe8\xb2\xa0\xe3\x81\xae\xe6\x96\xb9\xe5\x90\x91\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe3\x81\xae\xe3\x81\xbf\xe3\x82\x92\xe9\x81\xa9\xe7\x94\xa8 */" },
		{ "Negative.Name", "ESyncBoneDirection::Negative" },
		{ "Negative.ToolTip", "\xe8\xb2\xa0\xe3\x81\xae\xe6\x96\xb9\xe5\x90\x91\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe3\x81\xae\xe3\x81\xbf\xe3\x82\x92\xe9\x81\xa9\xe7\x94\xa8" },
		{ "None.Comment", "/** \xe7\xa7\xbb\xe5\x8b\x95\xe3\x82\x92\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84 */" },
		{ "None.Name", "ESyncBoneDirection::None" },
		{ "None.ToolTip", "\xe7\xa7\xbb\xe5\x8b\x95\xe3\x82\x92\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x97\xe3\x81\xaa\xe3\x81\x84" },
		{ "Positive.Comment", "/** \xe6\xad\xa3\xe3\x81\xae\xe6\x96\xb9\xe5\x90\x91\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe3\x81\xae\xe3\x81\xbf\xe3\x82\x92\xe9\x81\xa9\xe7\x94\xa8 */" },
		{ "Positive.Name", "ESyncBoneDirection::Positive" },
		{ "Positive.ToolTip", "\xe6\xad\xa3\xe3\x81\xae\xe6\x96\xb9\xe5\x90\x91\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe3\x81\xae\xe3\x81\xbf\xe3\x82\x92\xe9\x81\xa9\xe7\x94\xa8" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ESyncBoneDirection::Both", (int64)ESyncBoneDirection::Both },
		{ "ESyncBoneDirection::Positive", (int64)ESyncBoneDirection::Positive },
		{ "ESyncBoneDirection::Negative", (int64)ESyncBoneDirection::Negative },
		{ "ESyncBoneDirection::None", (int64)ESyncBoneDirection::None },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_KawaiiPhysics_ESyncBoneDirection_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_KawaiiPhysics,
	nullptr,
	"ESyncBoneDirection",
	"ESyncBoneDirection",
	Z_Construct_UEnum_KawaiiPhysics_ESyncBoneDirection_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_KawaiiPhysics_ESyncBoneDirection_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_KawaiiPhysics_ESyncBoneDirection_Statics::Enum_MetaDataParams), Z_Construct_UEnum_KawaiiPhysics_ESyncBoneDirection_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_KawaiiPhysics_ESyncBoneDirection()
{
	if (!Z_Registration_Info_UEnum_ESyncBoneDirection.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ESyncBoneDirection.InnerSingleton, Z_Construct_UEnum_KawaiiPhysics_ESyncBoneDirection_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ESyncBoneDirection.InnerSingleton;
}
// End Enum ESyncBoneDirection

// Begin ScriptStruct FKawaiiPhysicsSyncTarget
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_KawaiiPhysicsSyncTarget;
class UScriptStruct* FKawaiiPhysicsSyncTarget::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_KawaiiPhysicsSyncTarget.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_KawaiiPhysicsSyncTarget.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget, (UObject*)Z_Construct_UPackage__Script_KawaiiPhysics(), TEXT("KawaiiPhysicsSyncTarget"));
	}
	return Z_Registration_Info_UScriptStruct_KawaiiPhysicsSyncTarget.OuterSingleton;
}
template<> KAWAIIPHYSICS_API UScriptStruct* StaticStruct<FKawaiiPhysicsSyncTarget>()
{
	return FKawaiiPhysicsSyncTarget::StaticStruct();
}
struct Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsSyncBone.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Bone_MetaData[] = {
		{ "Category", "SyncTarget" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe9\x81\xa9\xe7\x94\xa8\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3 */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsSyncBone.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x81\xa9\xe7\x94\xa8\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIncludeChildBones_MetaData[] = {
		{ "Category", "SyncTarget" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe3\x81\x93\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe5\xad\x90\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x82\xe3\x81\x99\xe3\x81\xb9\xe3\x81\xa6\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xab\xe3\x81\x99\xe3\x82\x8b\xe3\x81\x8b */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsSyncBone.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe3\x81\x93\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xae\xe5\xad\x90\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x82\x82\xe3\x81\x99\xe3\x81\xb9\xe3\x81\xa6\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xab\xe3\x81\x99\xe3\x82\x8b\xe3\x81\x8b" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Alpha_MetaData[] = {
		{ "Category", "SyncTarget" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe7\xa7\xbb\xe5\x8b\x95\xe3\x82\x92\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8b\xe5\xba\xa6\xe5\x90\x88\xe3\x81\x84 */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsSyncBone.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xa7\xbb\xe5\x8b\x95\xe3\x82\x92\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8b\xe5\xba\xa6\xe5\x90\x88\xe3\x81\x84" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ModifyBoneIndex_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe9\x81\xa9\xe5\xbf\x9c\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xaeModifyBone\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8bIndex\n" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsSyncBone.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x81\xa9\xe5\xbf\x9c\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xaeModifyBone\xe3\x81\xab\xe3\x81\x8a\xe3\x81\x91\xe3\x82\x8bIndex" },
#endif
	};
#if WITH_EDITORONLY_DATA
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TransitionBySyncBone_MetaData[] = {
		{ "ModuleRelativePath", "Public/KawaiiPhysicsSyncBone.h" },
	};
#endif // WITH_EDITORONLY_DATA
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Bone;
	static void NewProp_bIncludeChildBones_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIncludeChildBones;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Alpha;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ModifyBoneIndex;
#if WITH_EDITORONLY_DATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_TransitionBySyncBone;
#endif // WITH_EDITORONLY_DATA
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FKawaiiPhysicsSyncTarget>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::NewProp_Bone = { "Bone", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsSyncTarget, Bone), Z_Construct_UScriptStruct_FBoneReference, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Bone_MetaData), NewProp_Bone_MetaData) }; // 4218265988
void Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::NewProp_bIncludeChildBones_SetBit(void* Obj)
{
	((FKawaiiPhysicsSyncTarget*)Obj)->bIncludeChildBones = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::NewProp_bIncludeChildBones = { "bIncludeChildBones", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FKawaiiPhysicsSyncTarget), &Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::NewProp_bIncludeChildBones_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIncludeChildBones_MetaData), NewProp_bIncludeChildBones_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::NewProp_Alpha = { "Alpha", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsSyncTarget, Alpha), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Alpha_MetaData), NewProp_Alpha_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::NewProp_ModifyBoneIndex = { "ModifyBoneIndex", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsSyncTarget, ModifyBoneIndex), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ModifyBoneIndex_MetaData), NewProp_ModifyBoneIndex_MetaData) };
#if WITH_EDITORONLY_DATA
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::NewProp_TransitionBySyncBone = { "TransitionBySyncBone", nullptr, (EPropertyFlags)0x0010000800000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsSyncTarget, TransitionBySyncBone), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TransitionBySyncBone_MetaData), NewProp_TransitionBySyncBone_MetaData) };
#endif // WITH_EDITORONLY_DATA
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::NewProp_Bone,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::NewProp_bIncludeChildBones,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::NewProp_Alpha,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::NewProp_ModifyBoneIndex,
#if WITH_EDITORONLY_DATA
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::NewProp_TransitionBySyncBone,
#endif // WITH_EDITORONLY_DATA
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_KawaiiPhysics,
	nullptr,
	&NewStructOps,
	"KawaiiPhysicsSyncTarget",
	Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::PropPointers),
	sizeof(FKawaiiPhysicsSyncTarget),
	alignof(FKawaiiPhysicsSyncTarget),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget()
{
	if (!Z_Registration_Info_UScriptStruct_KawaiiPhysicsSyncTarget.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_KawaiiPhysicsSyncTarget.InnerSingleton, Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_KawaiiPhysicsSyncTarget.InnerSingleton;
}
// End ScriptStruct FKawaiiPhysicsSyncTarget

// Begin ScriptStruct FKawaiiPhysicsSyncBone
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_KawaiiPhysicsSyncBone;
class UScriptStruct* FKawaiiPhysicsSyncBone::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_KawaiiPhysicsSyncBone.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_KawaiiPhysicsSyncBone.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone, (UObject*)Z_Construct_UPackage__Script_KawaiiPhysics(), TEXT("KawaiiPhysicsSyncBone"));
	}
	return Z_Registration_Info_UScriptStruct_KawaiiPhysicsSyncBone.OuterSingleton;
}
template<> KAWAIIPHYSICS_API UScriptStruct* StaticStruct<FKawaiiPhysicsSyncBone>()
{
	return FKawaiiPhysicsSyncBone::StaticStruct();
}
struct Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/KawaiiPhysicsSyncBone.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Bone_MetaData[] = {
		{ "Category", "SyncBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\x90\x8c\xe6\x9c\x9f\xe5\x85\x83\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3 */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsSyncBone.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x90\x8c\xe6\x9c\x9f\xe5\x85\x83\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Targets_MetaData[] = {
		{ "Category", "SyncBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe9\x81\xa9\xe7\x94\xa8\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xa8\xe9\x81\xa9\xe7\x94\xa8\xe5\xba\xa6 */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsSyncBone.h" },
		{ "TitleProperty", "{Bone}" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x81\xa9\xe7\x94\xa8\xe5\xaf\xbe\xe8\xb1\xa1\xe3\x81\xae\xe3\x83\x9c\xe3\x83\xbc\xe3\x83\xb3\xe3\x81\xa8\xe9\x81\xa9\xe7\x94\xa8\xe5\xba\xa6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GlobalAlpha_MetaData[] = {
		{ "Category", "SyncBone" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\x85\xa8\xe4\xbd\x93\xe3\x81\xab\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x95\xe3\x82\x8c\xe3\x82\x8b\xe7\xa7\xbb\xe5\x8b\x95\xe3\x81\xae\xe5\xba\xa6\xe5\x90\x88\xe3\x81\x84 */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsSyncBone.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x85\xa8\xe4\xbd\x93\xe3\x81\xab\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x95\xe3\x82\x8c\xe3\x82\x8b\xe7\xa7\xbb\xe5\x8b\x95\xe3\x81\xae\xe5\xba\xa6\xe5\x90\x88\xe3\x81\x84" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeltaDistanceScaleCurve_MetaData[] = {
		{ "Category", "SyncBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// SyncBone\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe8\xb7\x9d\xe9\x9b\xa2\xe3\x81\xab\xe5\xbf\x9c\xe3\x81\x98\xe3\x81\xa6\n// \xe5\x90\x84Target\xe3\x81\xab\xe5\xaf\xbe\xe3\x81\x97\xe3\x81\xa6\xe3\x81\xae\xe8\xa3\x9c\xe6\xad\xa3\xe5\x87\xa6\xe7\x90\x86\xe3\x81\xab\xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xbc\xe3\x83\xab\xe3\x82\x92\xe3\x81\x8b\xe3\x81\x91\xe3\x82\x8b\xe3\x82\xab\xe3\x83\xbc\xe3\x83\x96\n" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsSyncBone.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "SyncBone\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe8\xb7\x9d\xe9\x9b\xa2\xe3\x81\xab\xe5\xbf\x9c\xe3\x81\x98\xe3\x81\xa6\n\xe5\x90\x84Target\xe3\x81\xab\xe5\xaf\xbe\xe3\x81\x97\xe3\x81\xa6\xe3\x81\xae\xe8\xa3\x9c\xe6\xad\xa3\xe5\x87\xa6\xe7\x90\x86\xe3\x81\xab\xe3\x82\xb9\xe3\x82\xb1\xe3\x83\xbc\xe3\x83\xab\xe3\x82\x92\xe3\x81\x8b\xe3\x81\x91\xe3\x82\x8b\xe3\x82\xab\xe3\x83\xbc\xe3\x83\x96" },
#endif
		{ "XAxisName", "Distance" },
		{ "YAxisName", "Scale" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ApplyDirectionX_MetaData[] = {
		{ "Category", "SyncBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** X\xe8\xbb\xb8\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe3\x82\x92\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8b\xe6\x96\xb9\xe5\x90\x91 */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsSyncBone.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "X\xe8\xbb\xb8\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe3\x82\x92\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8b\xe6\x96\xb9\xe5\x90\x91" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ApplyDirectionY_MetaData[] = {
		{ "Category", "SyncBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Y\xe8\xbb\xb8\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe3\x82\x92\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8b\xe6\x96\xb9\xe5\x90\x91 */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsSyncBone.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Y\xe8\xbb\xb8\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe3\x82\x92\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8b\xe6\x96\xb9\xe5\x90\x91" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ApplyDirectionZ_MetaData[] = {
		{ "Category", "SyncBone" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Z\xe8\xbb\xb8\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe3\x82\x92\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8b\xe6\x96\xb9\xe5\x90\x91 */" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsSyncBone.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Z\xe8\xbb\xb8\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe3\x82\x92\xe9\x81\xa9\xe7\x94\xa8\xe3\x81\x99\xe3\x82\x8b\xe6\x96\xb9\xe5\x90\x91" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InitialPoseLocation_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// SyncBone\xe3\x81\xae\xe5\x88\x9d\xe6\x9c\x9f\xe5\xba\xa7\xe6\xa8\x99\n" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsSyncBone.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "SyncBone\xe3\x81\xae\xe5\x88\x9d\xe6\x9c\x9f\xe5\xba\xa7\xe6\xa8\x99" },
#endif
	};
#if WITH_EDITORONLY_DATA
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeltaDistance_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// SyncBone\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe8\xb7\x9d\xe9\x9b\xa2\n" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsSyncBone.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "SyncBone\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe8\xb7\x9d\xe9\x9b\xa2" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScaledDeltaDistance_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// SyncBone\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe8\xb7\x9d\xe9\x9b\xa2(Alpha, Scale\xe8\xa8\x88\xe7\xae\x97\xe5\xbe\x8c)\n" },
#endif
		{ "ModuleRelativePath", "Public/KawaiiPhysicsSyncBone.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "SyncBone\xe3\x81\xae\xe7\xa7\xbb\xe5\x8b\x95\xe8\xb7\x9d\xe9\x9b\xa2(Alpha, Scale\xe8\xa8\x88\xe7\xae\x97\xe5\xbe\x8c)" },
#endif
	};
#endif // WITH_EDITORONLY_DATA
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Bone;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Targets_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Targets;
	static const UECodeGen_Private::FStructPropertyParams NewProp_GlobalAlpha;
	static const UECodeGen_Private::FStructPropertyParams NewProp_DeltaDistanceScaleCurve;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ApplyDirectionX_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ApplyDirectionX;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ApplyDirectionY_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ApplyDirectionY;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ApplyDirectionZ_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ApplyDirectionZ;
	static const UECodeGen_Private::FStructPropertyParams NewProp_InitialPoseLocation;
#if WITH_EDITORONLY_DATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_DeltaDistance;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ScaledDeltaDistance;
#endif // WITH_EDITORONLY_DATA
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FKawaiiPhysicsSyncBone>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_Bone = { "Bone", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsSyncBone, Bone), Z_Construct_UScriptStruct_FBoneReference, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Bone_MetaData), NewProp_Bone_MetaData) }; // 4218265988
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_Targets_Inner = { "Targets", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget, METADATA_PARAMS(0, nullptr) }; // 802446928
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_Targets = { "Targets", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsSyncBone, Targets), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Targets_MetaData), NewProp_Targets_MetaData) }; // 802446928
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_GlobalAlpha = { "GlobalAlpha", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsSyncBone, GlobalAlpha), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GlobalAlpha_MetaData), NewProp_GlobalAlpha_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_DeltaDistanceScaleCurve = { "DeltaDistanceScaleCurve", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsSyncBone, DeltaDistanceScaleCurve), Z_Construct_UScriptStruct_FRuntimeFloatCurve, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeltaDistanceScaleCurve_MetaData), NewProp_DeltaDistanceScaleCurve_MetaData) }; // 1495033350
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_ApplyDirectionX_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_ApplyDirectionX = { "ApplyDirectionX", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsSyncBone, ApplyDirectionX), Z_Construct_UEnum_KawaiiPhysics_ESyncBoneDirection, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ApplyDirectionX_MetaData), NewProp_ApplyDirectionX_MetaData) }; // 4072561634
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_ApplyDirectionY_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_ApplyDirectionY = { "ApplyDirectionY", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsSyncBone, ApplyDirectionY), Z_Construct_UEnum_KawaiiPhysics_ESyncBoneDirection, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ApplyDirectionY_MetaData), NewProp_ApplyDirectionY_MetaData) }; // 4072561634
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_ApplyDirectionZ_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_ApplyDirectionZ = { "ApplyDirectionZ", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsSyncBone, ApplyDirectionZ), Z_Construct_UEnum_KawaiiPhysics_ESyncBoneDirection, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ApplyDirectionZ_MetaData), NewProp_ApplyDirectionZ_MetaData) }; // 4072561634
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_InitialPoseLocation = { "InitialPoseLocation", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsSyncBone, InitialPoseLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InitialPoseLocation_MetaData), NewProp_InitialPoseLocation_MetaData) };
#if WITH_EDITORONLY_DATA
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_DeltaDistance = { "DeltaDistance", nullptr, (EPropertyFlags)0x0010000800000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsSyncBone, DeltaDistance), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeltaDistance_MetaData), NewProp_DeltaDistance_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_ScaledDeltaDistance = { "ScaledDeltaDistance", nullptr, (EPropertyFlags)0x0010000800000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FKawaiiPhysicsSyncBone, ScaledDeltaDistance), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScaledDeltaDistance_MetaData), NewProp_ScaledDeltaDistance_MetaData) };
#endif // WITH_EDITORONLY_DATA
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_Bone,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_Targets_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_Targets,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_GlobalAlpha,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_DeltaDistanceScaleCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_ApplyDirectionX_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_ApplyDirectionX,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_ApplyDirectionY_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_ApplyDirectionY,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_ApplyDirectionZ_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_ApplyDirectionZ,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_InitialPoseLocation,
#if WITH_EDITORONLY_DATA
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_DeltaDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewProp_ScaledDeltaDistance,
#endif // WITH_EDITORONLY_DATA
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_KawaiiPhysics,
	nullptr,
	&NewStructOps,
	"KawaiiPhysicsSyncBone",
	Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::PropPointers),
	sizeof(FKawaiiPhysicsSyncBone),
	alignof(FKawaiiPhysicsSyncBone),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone()
{
	if (!Z_Registration_Info_UScriptStruct_KawaiiPhysicsSyncBone.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_KawaiiPhysicsSyncBone.InnerSingleton, Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_KawaiiPhysicsSyncBone.InnerSingleton;
}
// End ScriptStruct FKawaiiPhysicsSyncBone

// Begin Registration
struct Z_CompiledInDeferFile_FID_colosseum_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsSyncBone_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ ESyncBoneDirection_StaticEnum, TEXT("ESyncBoneDirection"), &Z_Registration_Info_UEnum_ESyncBoneDirection, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 4072561634U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FKawaiiPhysicsSyncTarget::StaticStruct, Z_Construct_UScriptStruct_FKawaiiPhysicsSyncTarget_Statics::NewStructOps, TEXT("KawaiiPhysicsSyncTarget"), &Z_Registration_Info_UScriptStruct_KawaiiPhysicsSyncTarget, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FKawaiiPhysicsSyncTarget), 802446928U) },
		{ FKawaiiPhysicsSyncBone::StaticStruct, Z_Construct_UScriptStruct_FKawaiiPhysicsSyncBone_Statics::NewStructOps, TEXT("KawaiiPhysicsSyncBone"), &Z_Registration_Info_UScriptStruct_KawaiiPhysicsSyncBone, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FKawaiiPhysicsSyncBone), 2228493275U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_colosseum_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsSyncBone_h_3405568693(TEXT("/Script/KawaiiPhysics"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_colosseum_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsSyncBone_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_colosseum_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsSyncBone_h_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_colosseum_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsSyncBone_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_colosseum_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsSyncBone_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
