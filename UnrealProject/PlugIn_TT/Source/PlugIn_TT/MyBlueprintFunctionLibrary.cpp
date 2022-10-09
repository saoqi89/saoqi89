// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

void UMyBlueprintFunctionLibrary::BeginPlay()
{
	APak_File* Pak_File = NewObject<APak_File>();
	//Pak_File->BeginPlay();
	Pak_File->BeginPlay();
}

void UMyBlueprintFunctionLibrary::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	APak_File* Pak_File = NewObject<APak_File>();
	Pak_File->EndPlay(EndPlayReason);
}

bool UMyBlueprintFunctionLibrary::Mount(const FString PakPath, const FString MountPath)
{
	//APak_File* Pak_File = NewObject<APak_File>();
//	return Pak_File->Mount(PakPath, MountPath);
	return true;
}

void UMyBlueprintFunctionLibrary::LoadFile()
{
	//APak_File* Pak_File = NewObject<APak_File>();
	Pak_File->LoadFile();
}

void UMyBlueprintFunctionLibrary::UnMountPak()
{
	//APak_File* Pak_File = NewObject<APak_File>();
	Pak_File->UnMountPak();
}

void UMyBlueprintFunctionLibrary::Init(const FString PakPath, const FString MountPath, UUserWidget* UMG,
                                       const FString Msg)
{
	//APak_File* Pak_File = NewObject<APak_File>();
	Pak_File->InitTT(UMG, Msg);
}

void UMyBlueprintFunctionLibrary::ShowAll()
{
	//APak_File* Pak_File = NewObject<APak_File>();
	Pak_File->ShowAll();
}

void UMyBlueprintFunctionLibrary::HideAll()
{
	//APak_File* Pak_File = NewObject<APak_File>();
	Pak_File->HideAll();
}

void UMyBlueprintFunctionLibrary::ShowTTByIndex(const int ID)
{
	//APak_File* Pak_File = NewObject<APak_File>();
	Pak_File->ShowTTByIndex(ID);
}

void UMyBlueprintFunctionLibrary::HideTTByIndex(const int ID)
{
	//APak_File* Pak_File = NewObject<APak_File>();
	Pak_File->HideTTByIndex(ID);
}

void UMyBlueprintFunctionLibrary::FlashTT(const int ID, const int Hz)
{
	//APak_File* Pak_File = NewObject<APak_File>();
	Pak_File->FlashTT(ID, Hz);
}

void UMyBlueprintFunctionLibrary::StopFlashTT(const int ID)
{
	//APak_File* Pak_File = NewObject<APak_File>();
	Pak_File->StopFlashTT(ID);
}
