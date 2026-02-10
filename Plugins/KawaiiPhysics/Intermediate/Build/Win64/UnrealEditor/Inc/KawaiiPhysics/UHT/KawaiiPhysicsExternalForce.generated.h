// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "KawaiiPhysicsExternalForce.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef KAWAIIPHYSICS_KawaiiPhysicsExternalForce_generated_h
#error "KawaiiPhysicsExternalForce.generated.h already included, missing '#pragma once' in KawaiiPhysicsExternalForce.h"
#endif
#define KAWAIIPHYSICS_KawaiiPhysicsExternalForce_generated_h

#define FID_colosseum_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsExternalForce_h_52_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FKawaiiPhysics_ExternalForce_Statics; \
	static class UScriptStruct* StaticStruct();


template<> KAWAIIPHYSICS_API UScriptStruct* StaticStruct<struct FKawaiiPhysics_ExternalForce>();

#define FID_colosseum_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsExternalForce_h_237_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FKawaiiPhysics_ExternalForce_Basic_Statics; \
	static class UScriptStruct* StaticStruct(); \
	typedef FKawaiiPhysics_ExternalForce Super;


template<> KAWAIIPHYSICS_API UScriptStruct* StaticStruct<struct FKawaiiPhysics_ExternalForce_Basic>();

#define FID_colosseum_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsExternalForce_h_277_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FKawaiiPhysics_ExternalForce_Gravity_Statics; \
	static class UScriptStruct* StaticStruct(); \
	typedef FKawaiiPhysics_ExternalForce Super;


template<> KAWAIIPHYSICS_API UScriptStruct* StaticStruct<struct FKawaiiPhysics_ExternalForce_Gravity>();

#define FID_colosseum_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsExternalForce_h_336_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FKawaiiPhysics_ExternalForce_Curve_Statics; \
	static class UScriptStruct* StaticStruct(); \
	typedef FKawaiiPhysics_ExternalForce Super;


template<> KAWAIIPHYSICS_API UScriptStruct* StaticStruct<struct FKawaiiPhysics_ExternalForce_Curve>();

#define FID_colosseum_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsExternalForce_h_424_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FKawaiiPhysics_ExternalForce_Wind_Statics; \
	static class UScriptStruct* StaticStruct(); \
	typedef FKawaiiPhysics_ExternalForce Super;


template<> KAWAIIPHYSICS_API UScriptStruct* StaticStruct<struct FKawaiiPhysics_ExternalForce_Wind>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_colosseum_Plugins_KawaiiPhysics_Source_KawaiiPhysics_Public_KawaiiPhysicsExternalForce_h


#define FOREACH_ENUM_EEXTERNALFORCESPACE(op) \
	op(EExternalForceSpace::ComponentSpace) \
	op(EExternalForceSpace::WorldSpace) \
	op(EExternalForceSpace::BoneSpace) 

enum class EExternalForceSpace : uint8;
template<> struct TIsUEnumClass<EExternalForceSpace> { enum { Value = true }; };
template<> KAWAIIPHYSICS_API UEnum* StaticEnum<EExternalForceSpace>();

#define FOREACH_ENUM_EEXTERNALFORCECURVEEVALUATETYPE(op) \
	op(EExternalForceCurveEvaluateType::Single) \
	op(EExternalForceCurveEvaluateType::Average) \
	op(EExternalForceCurveEvaluateType::Max) \
	op(EExternalForceCurveEvaluateType::Min) 

enum class EExternalForceCurveEvaluateType : uint8;
template<> struct TIsUEnumClass<EExternalForceCurveEvaluateType> { enum { Value = true }; };
template<> KAWAIIPHYSICS_API UEnum* StaticEnum<EExternalForceCurveEvaluateType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
