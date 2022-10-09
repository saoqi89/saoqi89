// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPlatformFilePak.h"

/**
 * 
 */

 class NEW_TT_API FPakLoaderFileVisitor : public IPlatformFile::FDirectoryVisitor
 {
 public:
 	virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override
 	{
 		if (!bIsDirectory)
 		{
 			Files.Add(FilenameOrDirectory);
 		}
 		return true;
 	}

 	TArray<FString> Files;
 };

class NEW_TT_API PakLoader
{
public:
	PakLoader();
	~PakLoader();

	static PakLoader* Get();

	FPakPlatformFile* GetPakPlatformFile();

	void ResetPlatformFile();

	TArray<FString>GetMountedPakFilenames();

	/* Checks if the file exists and file is a valid pak file format. */
	bool IsValidPakFile(const FString &PakFilename, int64 &OutPakSize, bool bSigned = false);

	/* Returns search pak order acoording to how the path starts. */
	int32 GetPakOrderFromPakFilename(const FString& PakFilePath);

	/* Mounts pak file. Set PakOrder = INDEX_NONE if unsure. Leave mount path empty to use the mount path found in the pak file. */
	bool MountPakFile(const FString &PakFilename, int32 PakOrder, const FString &MountPath);

	/* Unmounts pak file. */
	bool UnmountPakFile(const FString &PakFilename);

	template<class T>
	T *LoadObjectFormPak(const FString &Filename)
	{
		const FString Name = T::StaticClass()->GetName() + TEXT("'") + Filename + TEXT(".") + FPackageName::GetShortName(Filename) + TEXT("'");
		return Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, *Name));
	}

	void RegisterMountPoint(const FString &RootPath, const FString &ContentPath);
	void UnRegisterMountPoint(const FString &RootPath, const FString &ContentPath);

	TArray<FString>GetFilesInPak(const FString &PakFilename, bool bUAssetOnly = true);

protected:
	FPakPlatformFile *PakPlatformFile = nullptr;

#if WITH_EDITOR
	IPlatformFile *OriginalPlatformFile = nullptr;
#endif

private:
	static PakLoader *Instance;
};

