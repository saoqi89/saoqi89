// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPlatformFilePak.h"
#include "Components/Image.h"
#include "GameFramework/PlayerController.h"
#include "Pak_Mount.generated.h"


/**
 * 
 */
UCLASS()
class BACKING_API APak_Mount : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		bool Mount(const FString& PakPath, UImage* Img);

	UFUNCTION(BlueprintCallable)
		void LoadFile(UImage* Img);
	

	UFUNCTION(BlueprintCallable)
		void MountPak();

	UFUNCTION(BlueprintCallable)
		void UnMountPak();

	UFUNCTION(BlueprintCallable)
		void Init(const FString PakPath, const FString MountPath, UImage* Img);

	TRefCountPtr<FPakFile> PakFile;
	
	FPakPlatformFile* Pak_Platform_File;

	TRefCountPtr<FPakFile> PakFile1;
	
	FPakPlatformFile* PakPlatformFile;

	IPlatformFile* InnerPlatformFile;

	
	
	FString Path;

	
private:
	
	UImage* Image = nullptr;
	
};
