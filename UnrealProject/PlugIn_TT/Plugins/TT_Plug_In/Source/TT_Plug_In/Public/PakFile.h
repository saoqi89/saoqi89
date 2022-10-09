// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPlatformFilePak.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "HAL/PlatformFilemanager.h"
//#include "NRunnable.h"
#include "GameFramework/Actor.h"
#include "PakFile.generated.h"

struct FTT_State
{
	float InX;
	float InY;
	int Index;
	UImage* Image;
	UTexture2D* Texture2D;
	bool IsShow;
	bool IsFlash;
};

UCLASS()
class TT_PLUG_IN_API APakFile : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APakFile();
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable)
		void Init(const FString PakPath, const FString MountPath, UUserWidget* UMG, const FString Msg);
	
	UFUNCTION(BlueprintCallable)
		bool Mount();
	
	UFUNCTION(BlueprintCallable)
		void LoadFile();

	UFUNCTION(BlueprintCallable)
		void UnMountPak();

	UFUNCTION(BlueprintCallable, Category = "TT_plugin|Control")
		void ShowAll();

	UFUNCTION(BlueprintCallable, Category = "TT_plugin|Control")
		void HideAll();	

	UFUNCTION(BlueprintCallable, Category = "TT_plugin|Control")
		void ShowTTByIndex(const int ID);

	UFUNCTION(BlueprintCallable, Category = "TT_plugin|Control")
		void HideTTByIndex(const int ID);

	UFUNCTION(BlueprintCallable, Category = "TT_plugin|Control")
		void FlashTT(const int ID, const int Hz);

	UFUNCTION(BlueprintCallable, Category = "TT_plugin|Control")
		void StopFlashTT(const int ID);

	void CreateImageWidget(UUserWidget* UMG);
	void GetString(const FString Msg);
	//Timer执行函数
	void Change();

private:
	
	float Tick = 1.0;
	
	FTimerHandle TestHandel;
	
	TRefCountPtr<FPakFile> PakFile;
	
	FPakPlatformFile* PakPlatformFile;

	IPlatformFile* InnerPlatformFile;

	FString pak_path;
	
	//FString Path;

	FString Mount_Path;

	UUserWidget* _UMG;
	
	FString _Msg;
	
	UTexture2D* Obj = nullptr;

	TArray<FString> AssetList;

	/*Struct*/
	FTT_State Ftt_State;
	/*Map*/
	TMap<int, FTT_State>MMap;
	
	
};
