// Copyright Epic Games, Inc. All Rights Reserved.

#include "TT_Plug_In.h"

#define LOCTEXT_NAMESPACE "FTT_Plug_InModule"

void FTT_Plug_InModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FTT_Plug_InModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTT_Plug_InModule, TT_Plug_In)