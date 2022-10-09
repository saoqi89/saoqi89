// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TT_Plug_In/Public/PakFile.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePakFile() {}
// Cross Module References
	TT_PLUG_IN_API UClass* Z_Construct_UClass_APakFile_NoRegister();
	TT_PLUG_IN_API UClass* Z_Construct_UClass_APakFile();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_TT_Plug_In();
	UMG_API UClass* Z_Construct_UClass_UUserWidget_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(APakFile::execStopFlashTT)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_ID);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->StopFlashTT(Z_Param_ID);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(APakFile::execFlashTT)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_ID);
		P_GET_PROPERTY(FIntProperty,Z_Param_Hz);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->FlashTT(Z_Param_ID,Z_Param_Hz);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(APakFile::execHideTTByIndex)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_ID);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->HideTTByIndex(Z_Param_ID);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(APakFile::execShowTTByIndex)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_ID);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ShowTTByIndex(Z_Param_ID);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(APakFile::execHideAll)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->HideAll();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(APakFile::execShowAll)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ShowAll();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(APakFile::execUnMountPak)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->UnMountPak();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(APakFile::execLoadFile)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->LoadFile();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(APakFile::execMount)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->Mount();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(APakFile::execInit)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_PakPath);
		P_GET_PROPERTY(FStrProperty,Z_Param_MountPath);
		P_GET_OBJECT(UUserWidget,Z_Param_UMG);
		P_GET_PROPERTY(FStrProperty,Z_Param_Msg);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Init(Z_Param_PakPath,Z_Param_MountPath,Z_Param_UMG,Z_Param_Msg);
		P_NATIVE_END;
	}
	void APakFile::StaticRegisterNativesAPakFile()
	{
		UClass* Class = APakFile::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "FlashTT", &APakFile::execFlashTT },
			{ "HideAll", &APakFile::execHideAll },
			{ "HideTTByIndex", &APakFile::execHideTTByIndex },
			{ "Init", &APakFile::execInit },
			{ "LoadFile", &APakFile::execLoadFile },
			{ "Mount", &APakFile::execMount },
			{ "ShowAll", &APakFile::execShowAll },
			{ "ShowTTByIndex", &APakFile::execShowTTByIndex },
			{ "StopFlashTT", &APakFile::execStopFlashTT },
			{ "UnMountPak", &APakFile::execUnMountPak },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_APakFile_FlashTT_Statics
	{
		struct PakFile_eventFlashTT_Parms
		{
			int32 ID;
			int32 Hz;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ID_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_ID;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Hz_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_Hz;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_APakFile_FlashTT_Statics::NewProp_ID_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_APakFile_FlashTT_Statics::NewProp_ID = { "ID", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(PakFile_eventFlashTT_Parms, ID), METADATA_PARAMS(Z_Construct_UFunction_APakFile_FlashTT_Statics::NewProp_ID_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_FlashTT_Statics::NewProp_ID_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_APakFile_FlashTT_Statics::NewProp_Hz_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_APakFile_FlashTT_Statics::NewProp_Hz = { "Hz", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(PakFile_eventFlashTT_Parms, Hz), METADATA_PARAMS(Z_Construct_UFunction_APakFile_FlashTT_Statics::NewProp_Hz_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_FlashTT_Statics::NewProp_Hz_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APakFile_FlashTT_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APakFile_FlashTT_Statics::NewProp_ID,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APakFile_FlashTT_Statics::NewProp_Hz,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_APakFile_FlashTT_Statics::Function_MetaDataParams[] = {
		{ "Category", "TT_plugin|Control" },
		{ "ModuleRelativePath", "Public/PakFile.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_APakFile_FlashTT_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_APakFile, nullptr, "FlashTT", nullptr, nullptr, sizeof(PakFile_eventFlashTT_Parms), Z_Construct_UFunction_APakFile_FlashTT_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_FlashTT_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_APakFile_FlashTT_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_FlashTT_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_APakFile_FlashTT()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_APakFile_FlashTT_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_APakFile_HideAll_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_APakFile_HideAll_Statics::Function_MetaDataParams[] = {
		{ "Category", "TT_plugin|Control" },
		{ "ModuleRelativePath", "Public/PakFile.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_APakFile_HideAll_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_APakFile, nullptr, "HideAll", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_APakFile_HideAll_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_HideAll_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_APakFile_HideAll()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_APakFile_HideAll_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_APakFile_HideTTByIndex_Statics
	{
		struct PakFile_eventHideTTByIndex_Parms
		{
			int32 ID;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ID_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_ID;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_APakFile_HideTTByIndex_Statics::NewProp_ID_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_APakFile_HideTTByIndex_Statics::NewProp_ID = { "ID", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(PakFile_eventHideTTByIndex_Parms, ID), METADATA_PARAMS(Z_Construct_UFunction_APakFile_HideTTByIndex_Statics::NewProp_ID_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_HideTTByIndex_Statics::NewProp_ID_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APakFile_HideTTByIndex_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APakFile_HideTTByIndex_Statics::NewProp_ID,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_APakFile_HideTTByIndex_Statics::Function_MetaDataParams[] = {
		{ "Category", "TT_plugin|Control" },
		{ "ModuleRelativePath", "Public/PakFile.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_APakFile_HideTTByIndex_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_APakFile, nullptr, "HideTTByIndex", nullptr, nullptr, sizeof(PakFile_eventHideTTByIndex_Parms), Z_Construct_UFunction_APakFile_HideTTByIndex_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_HideTTByIndex_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_APakFile_HideTTByIndex_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_HideTTByIndex_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_APakFile_HideTTByIndex()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_APakFile_HideTTByIndex_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_APakFile_Init_Statics
	{
		struct PakFile_eventInit_Parms
		{
			FString PakPath;
			FString MountPath;
			UUserWidget* UMG;
			FString Msg;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PakPath_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_PakPath;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MountPath_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_MountPath;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UMG_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_UMG;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Msg_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Msg;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_APakFile_Init_Statics::NewProp_PakPath_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_APakFile_Init_Statics::NewProp_PakPath = { "PakPath", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(PakFile_eventInit_Parms, PakPath), METADATA_PARAMS(Z_Construct_UFunction_APakFile_Init_Statics::NewProp_PakPath_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_Init_Statics::NewProp_PakPath_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_APakFile_Init_Statics::NewProp_MountPath_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_APakFile_Init_Statics::NewProp_MountPath = { "MountPath", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(PakFile_eventInit_Parms, MountPath), METADATA_PARAMS(Z_Construct_UFunction_APakFile_Init_Statics::NewProp_MountPath_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_Init_Statics::NewProp_MountPath_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_APakFile_Init_Statics::NewProp_UMG_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_APakFile_Init_Statics::NewProp_UMG = { "UMG", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(PakFile_eventInit_Parms, UMG), Z_Construct_UClass_UUserWidget_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_APakFile_Init_Statics::NewProp_UMG_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_Init_Statics::NewProp_UMG_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_APakFile_Init_Statics::NewProp_Msg_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_APakFile_Init_Statics::NewProp_Msg = { "Msg", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(PakFile_eventInit_Parms, Msg), METADATA_PARAMS(Z_Construct_UFunction_APakFile_Init_Statics::NewProp_Msg_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_Init_Statics::NewProp_Msg_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APakFile_Init_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APakFile_Init_Statics::NewProp_PakPath,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APakFile_Init_Statics::NewProp_MountPath,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APakFile_Init_Statics::NewProp_UMG,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APakFile_Init_Statics::NewProp_Msg,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_APakFile_Init_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/PakFile.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_APakFile_Init_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_APakFile, nullptr, "Init", nullptr, nullptr, sizeof(PakFile_eventInit_Parms), Z_Construct_UFunction_APakFile_Init_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_Init_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_APakFile_Init_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_Init_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_APakFile_Init()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_APakFile_Init_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_APakFile_LoadFile_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_APakFile_LoadFile_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/PakFile.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_APakFile_LoadFile_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_APakFile, nullptr, "LoadFile", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_APakFile_LoadFile_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_LoadFile_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_APakFile_LoadFile()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_APakFile_LoadFile_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_APakFile_Mount_Statics
	{
		struct PakFile_eventMount_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_APakFile_Mount_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((PakFile_eventMount_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_APakFile_Mount_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(PakFile_eventMount_Parms), &Z_Construct_UFunction_APakFile_Mount_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APakFile_Mount_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APakFile_Mount_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_APakFile_Mount_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/PakFile.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_APakFile_Mount_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_APakFile, nullptr, "Mount", nullptr, nullptr, sizeof(PakFile_eventMount_Parms), Z_Construct_UFunction_APakFile_Mount_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_Mount_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_APakFile_Mount_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_Mount_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_APakFile_Mount()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_APakFile_Mount_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_APakFile_ShowAll_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_APakFile_ShowAll_Statics::Function_MetaDataParams[] = {
		{ "Category", "TT_plugin|Control" },
		{ "ModuleRelativePath", "Public/PakFile.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_APakFile_ShowAll_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_APakFile, nullptr, "ShowAll", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_APakFile_ShowAll_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_ShowAll_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_APakFile_ShowAll()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_APakFile_ShowAll_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_APakFile_ShowTTByIndex_Statics
	{
		struct PakFile_eventShowTTByIndex_Parms
		{
			int32 ID;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ID_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_ID;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_APakFile_ShowTTByIndex_Statics::NewProp_ID_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_APakFile_ShowTTByIndex_Statics::NewProp_ID = { "ID", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(PakFile_eventShowTTByIndex_Parms, ID), METADATA_PARAMS(Z_Construct_UFunction_APakFile_ShowTTByIndex_Statics::NewProp_ID_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_ShowTTByIndex_Statics::NewProp_ID_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APakFile_ShowTTByIndex_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APakFile_ShowTTByIndex_Statics::NewProp_ID,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_APakFile_ShowTTByIndex_Statics::Function_MetaDataParams[] = {
		{ "Category", "TT_plugin|Control" },
		{ "ModuleRelativePath", "Public/PakFile.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_APakFile_ShowTTByIndex_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_APakFile, nullptr, "ShowTTByIndex", nullptr, nullptr, sizeof(PakFile_eventShowTTByIndex_Parms), Z_Construct_UFunction_APakFile_ShowTTByIndex_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_ShowTTByIndex_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_APakFile_ShowTTByIndex_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_ShowTTByIndex_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_APakFile_ShowTTByIndex()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_APakFile_ShowTTByIndex_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_APakFile_StopFlashTT_Statics
	{
		struct PakFile_eventStopFlashTT_Parms
		{
			int32 ID;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ID_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_ID;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_APakFile_StopFlashTT_Statics::NewProp_ID_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_APakFile_StopFlashTT_Statics::NewProp_ID = { "ID", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(PakFile_eventStopFlashTT_Parms, ID), METADATA_PARAMS(Z_Construct_UFunction_APakFile_StopFlashTT_Statics::NewProp_ID_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_StopFlashTT_Statics::NewProp_ID_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APakFile_StopFlashTT_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APakFile_StopFlashTT_Statics::NewProp_ID,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_APakFile_StopFlashTT_Statics::Function_MetaDataParams[] = {
		{ "Category", "TT_plugin|Control" },
		{ "ModuleRelativePath", "Public/PakFile.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_APakFile_StopFlashTT_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_APakFile, nullptr, "StopFlashTT", nullptr, nullptr, sizeof(PakFile_eventStopFlashTT_Parms), Z_Construct_UFunction_APakFile_StopFlashTT_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_StopFlashTT_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_APakFile_StopFlashTT_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_StopFlashTT_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_APakFile_StopFlashTT()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_APakFile_StopFlashTT_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_APakFile_UnMountPak_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_APakFile_UnMountPak_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/PakFile.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_APakFile_UnMountPak_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_APakFile, nullptr, "UnMountPak", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_APakFile_UnMountPak_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_APakFile_UnMountPak_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_APakFile_UnMountPak()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_APakFile_UnMountPak_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_APakFile_NoRegister()
	{
		return APakFile::StaticClass();
	}
	struct Z_Construct_UClass_APakFile_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_APakFile_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_TT_Plug_In,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_APakFile_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_APakFile_FlashTT, "FlashTT" }, // 1517631009
		{ &Z_Construct_UFunction_APakFile_HideAll, "HideAll" }, // 3636983574
		{ &Z_Construct_UFunction_APakFile_HideTTByIndex, "HideTTByIndex" }, // 1469879489
		{ &Z_Construct_UFunction_APakFile_Init, "Init" }, // 3800357557
		{ &Z_Construct_UFunction_APakFile_LoadFile, "LoadFile" }, // 1108575414
		{ &Z_Construct_UFunction_APakFile_Mount, "Mount" }, // 3488219417
		{ &Z_Construct_UFunction_APakFile_ShowAll, "ShowAll" }, // 1062970998
		{ &Z_Construct_UFunction_APakFile_ShowTTByIndex, "ShowTTByIndex" }, // 1319253701
		{ &Z_Construct_UFunction_APakFile_StopFlashTT, "StopFlashTT" }, // 1937838973
		{ &Z_Construct_UFunction_APakFile_UnMountPak, "UnMountPak" }, // 2568309549
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APakFile_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "PakFile.h" },
		{ "ModuleRelativePath", "Public/PakFile.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_APakFile_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APakFile>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_APakFile_Statics::ClassParams = {
		&APakFile::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_APakFile_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_APakFile_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_APakFile()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_APakFile_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(APakFile, 1263803557);
	template<> TT_PLUG_IN_API UClass* StaticClass<APakFile>()
	{
		return APakFile::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_APakFile(Z_Construct_UClass_APakFile, &APakFile::StaticClass, TEXT("/Script/TT_Plug_In"), TEXT("APakFile"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(APakFile);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
