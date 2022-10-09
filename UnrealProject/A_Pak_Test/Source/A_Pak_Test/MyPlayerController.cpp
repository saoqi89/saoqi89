// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "IPlatformFilePak.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "Engine.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Engine/AssetManager.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//����ԭ�ȵ�PlatFrom
	OldPlatform = &FPlatformFileManager::Get().GetPlatformFile();

	//��ʼ��PakPlatform
	PakPlatform = MakeShareable(new FPakPlatformFile());
	PakPlatform->Initialize(&FPlatformFileManager::Get().GetPlatformFile(), TEXT(""));
	
	/*---------------------------------------------------------------------------------------*/
	
	//��ȡ��ǰʹ�õ�ƽ̨
	InnerPlatformFile = &FPlatformFileManager::Get().GetPlatformFile();
	UE_LOG(LogTemp, Warning, TEXT("InnerPlatformFile: %s"), InnerPlatformFile->GetName());

	//��ʼ��PakPlatformFile 
	PakPlatformFile = MakeShareable(new FPakPlatformFile());
	PakPlatformFile.Get()->Initialize(InnerPlatformFile, TEXT(""));

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GWorld, 0);
	PlayerController->bShowMouseCursor = true;//��ʾ���
	PlayerController->SetIgnoreLookInput(true);//������겻����ת��
	
}

void AMyPlayerController::LoadPak(const FString& PakPath, UImage *UImage)
{
	
	UE_LOG(LogTemp, Warning, TEXT("Start LoadPak = %s"), *PakPath);

	FPlatformFileManager::Get().SetPlatformFile(*PakPlatform.Get());
	FString PakFullPath = PakPath;
	FPakFile *pak = new FPakFile(PakPlatform.Get(), *PakFullPath, false);
	
	//����pak�ľ���·��
	//TSharedPtr<FPakFile> PakTemp = MakeShareable(pak);
	TRefCountPtr<FPakFile> PakTemp = new FPakFile(OldPlatform, *PakFullPath, false);
	//TRefCountPtr<FPakFile> PakTemp = new FPakFile(PakPlatform.Get(), *PakFullPath, false);
	//TRefCountPtr<FPakFile> PakTemp = MakeShareable(*pak);

	FString OldPakMountPoint = PakTemp->GetMountPoint();
	int32 Pos = OldPakMountPoint.Find("Content/");
	FString NewMountPoint = OldPakMountPoint.RightChop(Pos);

	NewMountPoint = FPaths::ProjectDir() + NewMountPoint;

	//�����µĹ��ص�
	PakTemp->SetMountPoint(*NewMountPoint);

	//LOG
	const FString MountPoint(*pak->GetMountPoint());
	UE_LOG(LogTemp, Warning, TEXT("GetMountPoint %s"), *MountPoint);
	
	//��̬�ļ�
	if (PakPlatform->Mount(*PakFullPath, 1, *NewMountPoint))
	{
		//�����ļ�
		TArray<FString> FoundFilename;
		PakTemp->FindPrunedFilesAtPath(FoundFilename, *PakTemp->GetMountPoint(), true, false, false);

		if (FoundFilename.Num() > 0)
		{
			//�����ļ��б��е��ļ�
			for (FString &Filename : FoundFilename)
			{
				/*if (Filename.EndsWith(TEXT(".uasset")))
				{*/
					FString NewFileName = Filename;
					NewFileName.RemoveFromEnd(TEXT(".uasset"));
					FString name = NewFileName.Right(7);
					int32 pos = NewFileName.Find(TEXT("/Content/"));
					NewFileName = NewFileName.RightChop(pos + 8);
					NewFileName = "/Game" + NewFileName + "." + name;
					//NewFileName = "Texture2D''";

					FString Name = FString::Printf(TEXT("Texture2D'%s'"), *NewFileName);

					FString	path = "Texture2D'/Game/asda.asda'";
					//NewFileName = NewFileName + name;

					UObject *LoadObj = StaticLoadObject(UObject::StaticClass(), NULL, *Name);

					//����ǿתΪStaticMesh
					UStaticMesh* SM = Cast<UStaticMesh>(LoadObj);
					if (SM)
					{
						AStaticMeshActor* MeshActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), FVector(0, 0, 460), FRotator(0));
						MeshActor->SetMobility(EComponentMobility::Movable);
						MeshActor->GetStaticMeshComponent()->SetStaticMesh(SM);
						break;
					}

					FString FileName = Name.Right(16);
					UTexture2D *Obj = LoadObject<UTexture2D>(nullptr, *Name, *FileName);
					if (Obj)
					{
						
					}
					
					UTexture2D* T = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass() ,nullptr, *path));
					if (T)
					{
						
						UImage->SetBrushFromTexture(T);
						UImage->SetRenderTranslation(FVector2D(20.0f, 100.0f));
						//UImage *DynIamge = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
						break;
					}
				//}
			}
		}
	}

	
	FPlatformFileManager::Get().SetPlatformFile(*OldPlatform);

}

bool AMyPlayerController::ShutDown(const FString& PakFileName, UImage *Image)
{

	bool Result = false;

	// �л��� pakƽ̨
	FPlatformFileManager::Get().SetPlatformFile(*PakPlatformFile.Get());

	// ��ȡpak�ļ�
	//TRefCountPtr<FPakFile> PakFile = new FPakFile(InnerPlatformFile, *PakFileName, false);
	//TSharedPtr<FPakFile> PakFile = MakeShareable(new FPakFile(InnerPlatformFile, *PakFileName, false));
	PakFile1 = new FPakFile(InnerPlatformFile, *PakFileName, false);
	FString MountPoint = PakFile1->GetMountPoint();
	UE_LOG(LogTemp, Warning, TEXT("Default Mount Point: %s"), *MountPoint);

#if !WITH_EDITOR
	
	// PIEģʽ�£�MountPoint ʹ�þ���·��
	MountPoint = FPaths::ConvertRelativePathToFull(MountPoint);
	UE_LOG(LogTemp, Warning, TEXT("Default Mount Point Full Path: %s"), *MountPoint);
	

	// ����pak�ļ���Mount�㣬��Ϊ������pak��ʱ�������ı����趨 mount point����ʡ�Դ˲���
	MountPoint = FPaths::ProjectContentDir() + TEXT("TT/");

	// ���ڴ˴���� Ĭ��MountPoint�ľ���·���ͷźͱ������ִ�н���Ƿ�һ��
	MountPoint = FPaths::ConvertRelativePathToFull(MountPoint);

	PakFile1->SetMountPoint(*MountPoint);
	UE_LOG(LogTemp, Warning, TEXT("New Mount Point Full Path: %s"), *MountPoint);

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("PIE"));
#else
	
	// ���ģʽ�£�MountPoint ʹ�����·��
	int32 pos1 = MountPoint.Find(TEXT("Content/"));
	FString NewMountPoint = MountPoint.RightChop(pos1);
	FString ProjectDir = FPaths::ProjectDir();
	NewMountPoint = ProjectDir + NewMountPoint;

	PakFile->SetMountPoint(*NewMountPoint);
	UE_LOG(LogTemp, Warning, TEXT("New Mount Point Full Path: %s"), *NewMountPoint);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Packering"));
	
#endif

	// ��pak�ļ����й���
	if (PakPlatformFile->Mount(*PakFileName, 1, *MountPoint))
	{
		LoadFile(Image);
		
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Mount Pak Failed"));
		
	// ���û�ԭ����PlatformFile, UE4.26 
	// ���Ӹ�����䣬�����Ա���������Pure Virtual function being called while application was running
	FPlatformFileManager::Get().SetPlatformFile(*InnerPlatformFile);

	//PakPlatform->Unmount(*PakFileName);

	return Result;
}

void AMyPlayerController::LoadFile(UImage* Img)
{
	// ���� pak �����Դ
	TArray<FString> AssetList;
	PakFile1->FindPrunedFilesAtPath(AssetList, *PakFile1->GetMountPoint(), true, false, true);
	for (FString itemPath : AssetList)
	{
		UE_LOG(LogTemp, Warning, TEXT("%-30s\t%s"), *FPackageName::GetShortName(itemPath), *itemPath);
		// �˴����첽������Դ

		FString NewFileName = itemPath;
		FString ShortName = FPackageName::GetShortName(NewFileName);
		FString LeftStr, RightStr;
		ShortName.Split(TEXT("."), &LeftStr, &RightStr);
		//NewFileName.RemoveFromEnd(TEXT(".uasset"));
		//FString name = NewFileName.Right(7);
		int32 pos = NewFileName.Find(TEXT("/Content/"));
		NewFileName = NewFileName.RightChop(pos + 8);
		//NewFileName = "/Game" + NewFileName + "." + name;
		NewFileName = "/Game/TT/" + LeftStr + "." + LeftStr;

		FString Name = FString::Printf(TEXT("Texture2D'%s'"), *NewFileName);

		FString FileName = Name.Right(16);
		//UTexture2D *Obj = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/TT/T_TT_18.T_TT_18'"));
		UTexture2D *Obj = FindObject<UTexture2D>(nullptr, *Name);
		if (!Obj)
		{
			Obj = LoadObject<UTexture2D>(nullptr, *Name);
			if (Obj)
			{
				Img->SetBrushFromTexture(Obj);
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("hello"));
			}
			
		}
		else
			UE_LOG(LogTemp, Error, TEXT("Load BP_PakTest1 Class Failed"));
		//FPlatformProcess::Sleep(1);
	}			
}

void AMyPlayerController::UnMount()
{
	if (PakPlatformFile)
	{
		//PakPlatformFile->Unmount(*los);
		FPlatformFileManager::Get().RemovePlatformFile(InnerPlatformFile);
		PakPlatformFile = nullptr;
	}
}


AMyPlayerController::AMyPlayerController()
{
	//��ȡƽ̨�ļ����ӹ�����
	PlatformFileManager = &FPlatformFileManager::Get();
	//��ȡƽ̨I/O�ӿڣ����ڲ���ƽ̨�ļ�
	HandleOriginPlatform = &PlatformFileManager->GetPlatformFile();
}

bool AMyPlayerController::Mount(const FString PakFilePath, UImage* Image)
{
	//�ж��ļ�ʱ����pak�ļ�
	if (!PakFilePath.EndsWith(".pak"))
	{
		return false;
	}  
	if (!HandlePakPlatform)
	{
		//����Pakƽ̨�ļ�ϵͳ
		HandlePakPlatform = new FPakPlatformFile();
	}
	//ʹ��ƽ̨�ӿڳ�ʼ��Pak�ļ�ƽ̨��װ��
	HandlePakPlatform->Initialize(HandleOriginPlatform, TEXT(""));
	//��PakPlatformFile���õ���㣬�����ļ�ʱ���Ȳ���PakPlatformFile�ڵ��ļ�
	PlatformFileManager->SetPlatformFile(*HandlePakPlatform);
	//�ж��ļ��Ƿ����
	if (!HandleOriginPlatform->FileExists(*PakFilePath))
	{ 
		PlatformFileManager->SetPlatformFile(*HandleOriginPlatform);
		return false;
	}
	//����pak����
	PakFile = new FPakFile(HandlePakPlatform, *PakFilePath, false);
	if (!PakFile)
	{
		PlatformFileManager->SetPlatformFile(*HandleOriginPlatform);
		return false;
	}   
	
	TArray<FString> ExistPakFiles;
	//��ѯ�ѹ��ص�����pak������
	HandlePakPlatform->GetMountedPakFilenames(ExistPakFiles);
	//�жϵ�ǰpak���Ƿ��ѹ���
	if (ExistPakFiles.Find(PakFilePath) >= 0)
	{
		PlatformFileManager->SetPlatformFile(*HandleOriginPlatform);
		return false;
	}
	int32 Pos = PakFile->GetMountPoint().Find("Content/");
	FString MountPoint = PakFile->GetMountPoint().RightChop(Pos);
	MountPoint = FPaths::ProjectDir() + MountPoint;
	PakFile->SetMountPoint(*MountPoint);
	//ʹ��pak����¼�Ĺ��ص����pak��
	if (!HandlePakPlatform->Mount(*PakFilePath, 0, *PakFile->GetMountPoint()))
	{
		PlatformFileManager->SetPlatformFile(*HandleOriginPlatform);
		return false;
	}

	// ���� pak �����Դ
	TArray<FString> AssetList;
	PakFile->FindPrunedFilesAtPath(AssetList, *PakFile->GetMountPoint(), true, false, true);
	for (FString itemPath : AssetList)
	{
		UE_LOG(LogTemp, Warning, TEXT("%-30s\t%s"), *FPackageName::GetShortName(itemPath), *itemPath);
		// �˴����첽������Դ

		FString NewFileName = itemPath;
		NewFileName.RemoveFromEnd(TEXT(".uasset"));
		FString name = NewFileName.Right(7);
		int32 pos = NewFileName.Find(TEXT("/Content/"));
		NewFileName = NewFileName.RightChop(pos + 8);
		NewFileName = "/Game" + NewFileName + "." + name;
		//NewFileName = "Texture2D''";

		FString Name = FString::Printf(TEXT("Texture2D'%s'"), *NewFileName);

		FString FileName = Name.Right(16);
		//UTexture2D *Obj = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/TT/T_TT_18.T_TT_18'"));
		UTexture2D *Obj = LoadObject<UTexture2D>(nullptr, *Name);
		if (Obj)
		{
			Image->SetBrushFromTexture(Obj);
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("hello"));
		}
		else
			UE_LOG(LogTemp, Error, TEXT("Load BP_PakTest1 Class Failed"));
		//FPlatformProcess::Sleep(1);
	}
	FPlatformFileManager::Get().SetPlatformFile(*HandleOriginPlatform);
	
	//PlatformFileManager->SetPlatformFile(*HandleOriginPlatform);
	return true;
}

void AMyPlayerController::Load(UImage* Image)
{
	// ���� pak �����Դ
	TArray<FString> AssetList;
	PakFile->FindPrunedFilesAtPath(AssetList, *PakFile->GetMountPoint(), true, false, true);
	for (FString itemPath : AssetList)
	{
		UE_LOG(LogTemp, Warning, TEXT("%-30s\t%s"), *FPackageName::GetShortName(itemPath), *itemPath);
		// �˴����첽������Դ

		FString NewFileName = itemPath;
		NewFileName.RemoveFromEnd(TEXT(".uasset"));
		FString name = NewFileName.Right(7);
		int32 pos = NewFileName.Find(TEXT("/Content/"));
		NewFileName = NewFileName.RightChop(pos + 8);
		NewFileName = "/Game" + NewFileName + "." + name;
		//NewFileName = "Texture2D''";

		FString Name = FString::Printf(TEXT("Texture2D'%s'"), *NewFileName);

		FString FileName = Name.Right(16);
		//UTexture2D *Obj = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/TT/T_TT_18.T_TT_18'"));
		UTexture2D *Obj = LoadObject<UTexture2D>(nullptr, *Name);
		if (Obj)
		{
			Image->SetBrushFromTexture(Obj);
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("hello"));
		}
		else
			UE_LOG(LogTemp, Error, TEXT("Load BP_PakTest1 Class Failed"));
		//FPlatformProcess::Sleep(1);
	}
	FPlatformFileManager::Get().SetPlatformFile(*HandleOriginPlatform);
}

AMyPlayerController::~AMyPlayerController()
{
	PlatformFileManager = nullptr;
	HandleOriginPlatform = nullptr;
	HandlePakPlatform = nullptr;
}

