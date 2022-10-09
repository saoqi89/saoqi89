// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PakLoaderLibrary.generated.h"

/**
 * 
 */

class UTexture2D;
class UStaticMesh;
UCLASS()
class NEW_TT_API UPakLoaderLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, Category = "PakLoader")
	static bool	IsPackagedBuild();
	
	UFUNCTION(BlueprintCallable, Category = "PakLoader")
	static bool MountPakFile(const FString &PakFilename, const FString &MountPath);

	UFUNCTION(BlueprintCallable, Category = "PakLoader")
	static bool UnMountPakFile(const FString &PakFilename);

	UFUNCTION(BlueprintCallable, Category = "PakLoader")
	static bool IsValidPakFile(const FString &PakFilename, int64 &PakSize);

	UFUNCTION(BlueprintCallable, Category = "PakLoader")
	static void RegisterMountPoint(const FString &RootPath, const FString &ContentPath);

	UFUNCTION(BlueprintCallable, Category = "PakLoader")
	static void UnRegisterMountPoint(const FString &RootPath, const FString &ContentPath);

	UFUNCTION(BlueprintPure, Category = "PakLoader")
	static TArray<FString>GetMountedPakFilename();
	
	UFUNCTION(BlueprintPure, Category = "PakLoader")
	static UTexture2D *GetPakFileTexture2D(const FString &Filename);

	UFUNCTION(BlueprintPure, Category = "PakLoader")
	static UStaticMesh *GetPakFileStaticMesh(const FString &Filename);

	UFUNCTION(BlueprintPure, Category = "PakLoader")
	static TArray<FString>GetFileInPak(const FString &PakFilename, bool bUAssetOnly = true);
	
};
