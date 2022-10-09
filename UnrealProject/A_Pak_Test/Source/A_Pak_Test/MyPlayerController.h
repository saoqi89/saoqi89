// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPlatformFilePak.h"
#include "HAL/PlatformFilemanager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class A_PAK_TEST_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
		void LoadPak(const FString& PakPath ,UImage *UImage);

	UFUNCTION(BlueprintCallable)
		bool ShutDown(const FString& akFileName, UImage *Image);

	UFUNCTION(BlueprintCallable)
		void LoadFile(UImage* Img);

	UFUNCTION(BlueprintCallable)
		void UnMount();

	FPakFile *PakFile1;
	

	class IPlatformFile* OldPlatform;
	TSharedPtr<FPakPlatformFile> PakPlatform;
	
	
	TSharedPtr<FPakPlatformFile> PakPlatformFile;

	IPlatformFile* InnerPlatformFile;

public:
	AMyPlayerController();

	UFUNCTION(BlueprintCallable)
	bool Mount(const FString PakFilePath, UImage* Image);

	UFUNCTION(BlueprintCallable)
		void Load(UImage* Image);

	FPakFile *PakFile = nullptr;
private:
	~AMyPlayerController();
	
	FPakPlatformFile* HandlePakPlatform;
	IPlatformFile* HandleOriginPlatform;
	FPlatformFileManager* PlatformFileManager;
	
public: 
	UFUNCTION(BlueprintCallable)
	bool IsWithEditor()
	{
#if WITH_EDITOR
		return true;
#else
		return false;
#endif
	}
};
