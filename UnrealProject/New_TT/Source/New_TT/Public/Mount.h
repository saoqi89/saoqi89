// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPlatformFilePak.h"
#include "GameFramework/Actor.h"
#include "Mount.generated.h"

class FPakPlatformFile;

UCLASS()
class NEW_TT_API AMount : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMount();

	UFUNCTION(BlueprintCallable)
	bool Mount(const FString PakPath, const FString MountPath);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	FString pak_path;
	FString Mount_Path;
	FString MountPoint;

	TRefCountPtr<FPakFile> PakFile;
	FPakPlatformFile* PakPlatformFile;
	IPlatformFile* InnerPlatformFile;

};
