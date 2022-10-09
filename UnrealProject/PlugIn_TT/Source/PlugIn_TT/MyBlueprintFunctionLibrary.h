// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pak_File.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PLUGIN_TT_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	virtual void BeginPlay();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	
	UFUNCTION(BlueprintCallable, Category = "TT_plugin|Init")
		static bool Mount(const FString PakPath, const FString MountPath);
	
	UFUNCTION(BlueprintCallable, Category = "TT_plugin|Init")
		static void LoadFile();
	
	UFUNCTION(BlueprintCallable, Category = "TT_plugin|Init")
		static void UnMountPak();

	UFUNCTION(BlueprintCallable, Category = "TT_plugin|Init")
		static void Init(const FString PakPath, const FString MountPath, UUserWidget* UMG, const FString Msg);

	UFUNCTION(BlueprintCallable, Category = "TT_plugin|Control")
		static void ShowAll();

	UFUNCTION(BlueprintCallable, Category = "TT_plugin|Control")
		static void HideAll();	

	UFUNCTION(BlueprintCallable, Category = "TT_plugin|Control")
		static void ShowTTByIndex(const int ID);

	UFUNCTION(BlueprintCallable, Category = "TT_plugin|Control")
		static void HideTTByIndex(const int ID);

	UFUNCTION(BlueprintCallable, Category = "TT_plugin|Control")
		static void FlashTT(const int ID, const int Hz);

	UFUNCTION(BlueprintCallable, Category = "TT_plugin|Control")
		static void StopFlashTT(const int ID);

private:
	APak_File* Pak_File;// = NewObject<APak_File>();
	
};
