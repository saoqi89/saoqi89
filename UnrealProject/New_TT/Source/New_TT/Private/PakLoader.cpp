// Fill out your copyright notice in the Description page of Project Settings.


#include "PakLoader.h"

PakLoader *PakLoader::Instance = nullptr;

PakLoader::PakLoader()
{
	UE_LOG(LogTemp, Warning, TEXT("PakLoader::Pakloader()"));
}

PakLoader::~PakLoader()
{
	UE_LOG(LogTemp, Warning, TEXT("PakLoader::Pakloader()"));
	ResetPlatformFile();
}

PakLoader* PakLoader::Get()
{
	if (!Instance)
	{
		Instance = new PakLoader();
	}
	return Instance;
	
}

FPakPlatformFile* PakLoader::GetPakPlatformFile()
{
	if (!PakPlatformFile)
	{
		IPlatformFile* CurrentPlatformFile = FPlatformFileManager::Get().FindPlatformFile(TEXT("PakFile"));
		if (CurrentPlatformFile)
		{
			UE_LOG(LogTemp, Error, TEXT("Found PakPlatformFile"));
			PakPlatformFile = static_cast<FPakPlatformFile*>(CurrentPlatformFile);
		}
		else
		{
			PakPlatformFile = new FPakPlatformFile();

			ensure(PakPlatformFile != nullptr);

			IPlatformFile &PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
#if WITH_EDITOR
			OriginalPlatformFile = &PlatformFile;
#endif
			if (PakPlatformFile->Initialize(&PlatformFile, TEXT("")))
			{
				FPlatformFileManager::Get().SetPlatformFile(*PakPlatformFile);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to Initialize PakPlatformFile"));
			}
			
		}
	}
	ensure(PakPlatformFile != nullptr);
	return PakPlatformFile;
}

void PakLoader::ResetPlatformFile()
{
#if WITH_EDITOR
	if (OriginalPlatformFile)
	{
		FPlatformFileManager::Get().SetPlatformFile(*OriginalPlatformFile);
	}
#endif
	
}

TArray<FString> PakLoader::GetMountedPakFilenames()
{
	TArray<FString>MountedPakFilenames;
	GetPakPlatformFile()->GetMountedPakFilenames(MountedPakFilenames);
	return MountedPakFilenames;
	
}

bool PakLoader::IsValidPakFile(const FString& PakFilename, int64& OutPakSize, bool bSigned)
{
	if (!FPaths::FileExists(PakFilename))
	{
		return false;
	}

	FPakFile* Pak = nullptr;
	TRefCountPtr<FPakFile>PakFile = new FPakFile(GetPakPlatformFile(), *PakFilename, bSigned);
	TArray<FString>AssetList;
	PakFile->FindPrunedFilesAtPath(AssetList, *PakFile->GetMountPoint());
	Pak = PakFile.GetReference();

	if (!Pak->IsValid())
	{
		PakFile.SafeRelease();
		return false;
	}

	OutPakSize = Pak->TotalSize();
	PakFile.SafeRelease();

	return true;
	
}

int32 PakLoader::GetPakOrderFromPakFilename(const FString& PakFilePath)
{
	if (PakFilePath.StartsWith(FString::Printf(TEXT("%sPaks/%s-"), *FPaths::ProjectContentDir(), FApp::GetProjectName())))
	{
		return 4;
	}
	else if (PakFilePath.StartsWith(FPaths::ProjectContentDir()))
	{
		return 3;
	}
	else if (PakFilePath.StartsWith(FPaths::EngineContentDir()))
	{
		return 2;
	}
	else if (PakFilePath.StartsWith(FPaths::ProjectSavedDir()))
	{
		return 1;
	}

	return 0;
	
}

bool PakLoader::MountPakFile(const FString& PakFilename, int32 PakOrder, const FString& MountPath)
{
	if (PakOrder == INDEX_NONE)
	{
		PakOrder = GetPakOrderFromPakFilename(PakFilename);
	}
	
	bool bResult = false;
	if (MountPath.Len() > 0)
	{
		bResult = GetPakPlatformFile()->Mount(*PakFilename, PakOrder, *MountPath);
	}
	else
	{
		bResult = GetPakPlatformFile()->Mount(*PakFilename, PakOrder, nullptr);
	}

	return bResult;
}

bool PakLoader::UnmountPakFile(const FString& PakFilename)
{
	return GetPakPlatformFile()->Unmount(*PakFilename);
}

void PakLoader::RegisterMountPoint(const FString& RootPath, const FString& ContentPath)
{
	FPackageName::RegisterMountPoint(RootPath, ContentPath);
}

void PakLoader::UnRegisterMountPoint(const FString& RootPath, const FString& ContentPath)
{
	FPackageName::UnRegisterMountPoint(RootPath, ContentPath);
}

TArray<FString> PakLoader::GetFilesInPak(const FString& PakFilename, bool bUAssetOnly)
{
	FPakFile* Pak = nullptr;

	TRefCountPtr<FPakFile> PakFile = new FPakFile(GetPakPlatformFile(), *PakFilename, false);
	Pak = PakFile.GetReference();

	TArray<FString>PakItemsName;
	if (Pak->IsValid())
	{
		TArray<FPakFile::FFilenameIterator> Records;

		for (FPakFile::FFilenameIterator It(*Pak, false); It; ++It)
		{
			Records.Add(It);
		}

		for (auto &It : Records)
		{
			if (bUAssetOnly)
			{
				if (FPaths::GetExtension(It.Filename()) == TEXT("uasset"))
				{
					PakItemsName.Add(It.Filename());
				}
			}
			else
			{
				PakItemsName.Add(It.Filename());
			}
		}
		
	}
	PakFile.SafeRelease();
	return PakItemsName;
}
