// Fill out your copyright notice in the Description page of Project Settings.


#include "PakLoaderLibrary.h"

#include "PakLoader.h"

bool UPakLoaderLibrary::IsPackagedBuild()
{
#if WITH_EDITOR == 0
	return true;
#else
	return false;
#endif
}

bool UPakLoaderLibrary::MountPakFile(const FString& PakFilename, const FString& MountPath)
{
	return PakLoader::Get()->MountPakFile(PakFilename, INDEX_NONE, MountPath);
}

bool UPakLoaderLibrary::UnMountPakFile(const FString& PakFilename)
{
	return PakLoader::Get()->UnmountPakFile(PakFilename);
}

bool UPakLoaderLibrary::IsValidPakFile(const FString& PakFilename, int64& PakSize)
{
	return PakLoader::Get()->IsValidPakFile(PakFilename, PakSize, false);
}

void UPakLoaderLibrary::RegisterMountPoint(const FString& RootPath, const FString& ContentPath)
{
	PakLoader::Get()->RegisterMountPoint(RootPath, ContentPath);
}

void UPakLoaderLibrary::UnRegisterMountPoint(const FString& RootPath, const FString& ContentPath)
{
	PakLoader::Get()->UnRegisterMountPoint(RootPath, ContentPath);
}

TArray<FString> UPakLoaderLibrary::GetMountedPakFilename()
{
	return PakLoader::Get()->GetMountedPakFilenames();
}

UTexture2D* UPakLoaderLibrary::GetPakFileTexture2D(const FString& Filename)
{
	return PakLoader::Get()->LoadObjectFormPak<UTexture2D>(Filename);
}

UStaticMesh* UPakLoaderLibrary::GetPakFileStaticMesh(const FString& Filename)
{
	return PakLoader::Get()->LoadObjectFormPak<UStaticMesh>(Filename);
}

TArray<FString> UPakLoaderLibrary::GetFileInPak(const FString& PakFilename, bool bUAssetOnly)
{
	return PakLoader::Get()->GetFilesInPak(PakFilename, bUAssetOnly);
}
