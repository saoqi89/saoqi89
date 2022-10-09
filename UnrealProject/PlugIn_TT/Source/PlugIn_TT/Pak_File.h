// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPlatformFilePak.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "HAL/PlatformFilemanager.h"
#include "NRunnable.h"
#include "GameFramework/PlayerController.h"
#include "Pak_File.generated.h"


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

/**
 * 
 */
UCLASS()
class PLUGIN_TT_API APak_File : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION(BlueprintCallable)
		bool Mount(const FString PakPath, const FString MountPath);
	
	UFUNCTION(BlueprintCallable)
		void LoadFile();
	
	UFUNCTION(BlueprintCallable)
		void UnMountPak();

	UFUNCTION(BlueprintCallable)
		void InitTT(UUserWidget* UMG, const FString Msg);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UUserWidget> HUDAsset;
	class UUserWidget* HUD;

	UFUNCTION(BlueprintCallable)
		void CreateImageWidget(UUserWidget* UMG);

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
	
		void GetString(const FString Msg);

	float Tick = 1.0;
	FTimerHandle TestHandel;

	//Timer执行函数
	void Change();

	TSharedPtr<class SConstraintCanvas > MyCanvas;
	
	TRefCountPtr<FPakFile> PakFile;
	
	FPakPlatformFile* PakPlatformFile;

	IPlatformFile* InnerPlatformFile;

	FString pak_path;
	
	//FString Path;

	FString Mount_Path;

	FString MountPoint;

	UUserWidget* _UMG;
	
	FString _Msg;
	
	UTexture2D* Obj = nullptr;

	TArray<FString> AssetList;

	TArray<UTexture2D*> Texture2Darr;

	/*Image*/
	TArray<UImage*> Images;
	UImage* NewImage;

	/*Struct*/
	FTT_State Ftt_State;
	/*Map*/
	TMap<int, FTT_State>MMap;
	
private:
	
	UImage* Image = nullptr;
	
};

