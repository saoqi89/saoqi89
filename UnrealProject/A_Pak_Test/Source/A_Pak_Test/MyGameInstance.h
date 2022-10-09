// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPlatformFilePak.h"
#include "HAL/PlatformFilemanager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class A_PAK_TEST_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	//virtual BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void Init();

	UFUNCTION(BlueprintCallable)
		bool LoadPak(FString PakPath);
	
private:

	TSharedPtr<FPakPlatformFile> PakPlatformFile;
	IPlatformFile* InnerPlatformFile;
};
