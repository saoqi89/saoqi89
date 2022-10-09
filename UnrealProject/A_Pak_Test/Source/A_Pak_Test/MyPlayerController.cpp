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

	//保存原先的PlatFrom
	OldPlatform = &FPlatformFileManager::Get().GetPlatformFile();

	//初始化PakPlatform
	PakPlatform = MakeShareable(new FPakPlatformFile());
	PakPlatform->Initialize(&FPlatformFileManager::Get().GetPlatformFile(), TEXT(""));
	
	/*---------------------------------------------------------------------------------------*/
	
	//获取当前使用的平台
	InnerPlatformFile = &FPlatformFileManager::Get().GetPlatformFile();
	UE_LOG(LogTemp, Warning, TEXT("InnerPlatformFile: %s"), InnerPlatformFile->GetName());

	//初始化PakPlatformFile 
	PakPlatformFile = MakeShareable(new FPakPlatformFile());
	PakPlatformFile.Get()->Initialize(InnerPlatformFile, TEXT(""));

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GWorld, 0);
	PlayerController->bShowMouseCursor = true;//显示鼠标
	PlayerController->SetIgnoreLookInput(true);//设置鼠标不控制转向
	
}

void AMyPlayerController::LoadPak(const FString& PakPath, UImage *UImage)
{
	
	UE_LOG(LogTemp, Warning, TEXT("Start LoadPak = %s"), *PakPath);

	FPlatformFileManager::Get().SetPlatformFile(*PakPlatform.Get());
	FString PakFullPath = PakPath;
	FPakFile *pak = new FPakFile(PakPlatform.Get(), *PakFullPath, false);
	
	//传入pak的绝对路径
	//TSharedPtr<FPakFile> PakTemp = MakeShareable(pak);
	TRefCountPtr<FPakFile> PakTemp = new FPakFile(OldPlatform, *PakFullPath, false);
	//TRefCountPtr<FPakFile> PakTemp = new FPakFile(PakPlatform.Get(), *PakFullPath, false);
	//TRefCountPtr<FPakFile> PakTemp = MakeShareable(*pak);

	FString OldPakMountPoint = PakTemp->GetMountPoint();
	int32 Pos = OldPakMountPoint.Find("Content/");
	FString NewMountPoint = OldPakMountPoint.RightChop(Pos);

	NewMountPoint = FPaths::ProjectDir() + NewMountPoint;

	//设置新的挂载点
	PakTemp->SetMountPoint(*NewMountPoint);

	//LOG
	const FString MountPoint(*pak->GetMountPoint());
	UE_LOG(LogTemp, Warning, TEXT("GetMountPoint %s"), *MountPoint);
	
	//静态文件
	if (PakPlatform->Mount(*PakFullPath, 1, *NewMountPoint))
	{
		//查找文件
		TArray<FString> FoundFilename;
		PakTemp->FindPrunedFilesAtPath(FoundFilename, *PakTemp->GetMountPoint(), true, false, false);

		if (FoundFilename.Num() > 0)
		{
			//遍历文件列表中的文件
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

					//类型强转为StaticMesh
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

	// 切换到 pak平台
	FPlatformFileManager::Get().SetPlatformFile(*PakPlatformFile.Get());

	// 获取pak文件
	//TRefCountPtr<FPakFile> PakFile = new FPakFile(InnerPlatformFile, *PakFileName, false);
	//TSharedPtr<FPakFile> PakFile = MakeShareable(new FPakFile(InnerPlatformFile, *PakFileName, false));
	PakFile1 = new FPakFile(InnerPlatformFile, *PakFileName, false);
	FString MountPoint = PakFile1->GetMountPoint();
	UE_LOG(LogTemp, Warning, TEXT("Default Mount Point: %s"), *MountPoint);

#if !WITH_EDITOR
	
	// PIE模式下，MountPoint 使用绝对路径
	MountPoint = FPaths::ConvertRelativePathToFull(MountPoint);
	UE_LOG(LogTemp, Warning, TEXT("Default Mount Point Full Path: %s"), *MountPoint);
	

	// 设置pak文件的Mount点，因为在制作pak的时候已在文本中设定 mount point，故省略此步骤
	MountPoint = FPaths::ProjectContentDir() + TEXT("TT/");

	// 可在此处检测 默认MountPoint的绝对路径释放和本条语句执行结果是否一致
	MountPoint = FPaths::ConvertRelativePathToFull(MountPoint);

	PakFile1->SetMountPoint(*MountPoint);
	UE_LOG(LogTemp, Warning, TEXT("New Mount Point Full Path: %s"), *MountPoint);

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("PIE"));
#else
	
	// 打包模式下，MountPoint 使用相对路径
	int32 pos1 = MountPoint.Find(TEXT("Content/"));
	FString NewMountPoint = MountPoint.RightChop(pos1);
	FString ProjectDir = FPaths::ProjectDir();
	NewMountPoint = ProjectDir + NewMountPoint;

	PakFile->SetMountPoint(*NewMountPoint);
	UE_LOG(LogTemp, Warning, TEXT("New Mount Point Full Path: %s"), *NewMountPoint);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Packering"));
	
#endif

	// 对pak文件进行挂载
	if (PakPlatformFile->Mount(*PakFileName, 1, *MountPoint))
	{
		LoadFile(Image);
		
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Mount Pak Failed"));
		
	// 设置回原来的PlatformFile, UE4.26 
	// 不加该条语句，本测试崩溃，报错：Pure Virtual function being called while application was running
	FPlatformFileManager::Get().SetPlatformFile(*InnerPlatformFile);

	//PakPlatform->Unmount(*PakFileName);

	return Result;
}

void AMyPlayerController::LoadFile(UImage* Img)
{
	// 遍历 pak 里的资源
	TArray<FString> AssetList;
	PakFile1->FindPrunedFilesAtPath(AssetList, *PakFile1->GetMountPoint(), true, false, true);
	for (FString itemPath : AssetList)
	{
		UE_LOG(LogTemp, Warning, TEXT("%-30s\t%s"), *FPackageName::GetShortName(itemPath), *itemPath);
		// 此处可异步加载资源

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
	//获取平台文件链接管理器
	PlatformFileManager = &FPlatformFileManager::Get();
	//获取平台I/O接口，用于操作平台文件
	HandleOriginPlatform = &PlatformFileManager->GetPlatformFile();
}

bool AMyPlayerController::Mount(const FString PakFilePath, UImage* Image)
{
	//判断文件时候是pak文件
	if (!PakFilePath.EndsWith(".pak"))
	{
		return false;
	}  
	if (!HandlePakPlatform)
	{
		//创建Pak平台文件系统
		HandlePakPlatform = new FPakPlatformFile();
	}
	//使用平台接口初始化Pak文件平台包装器
	HandlePakPlatform->Initialize(HandleOriginPlatform, TEXT(""));
	//将PakPlatformFile设置到最顶层，查找文件时优先查找PakPlatformFile内的文件
	PlatformFileManager->SetPlatformFile(*HandlePakPlatform);
	//判断文件是否存在
	if (!HandleOriginPlatform->FileExists(*PakFilePath))
	{ 
		PlatformFileManager->SetPlatformFile(*HandleOriginPlatform);
		return false;
	}
	//创建pak对象
	PakFile = new FPakFile(HandlePakPlatform, *PakFilePath, false);
	if (!PakFile)
	{
		PlatformFileManager->SetPlatformFile(*HandleOriginPlatform);
		return false;
	}   
	
	TArray<FString> ExistPakFiles;
	//查询已挂载的所有pak包名称
	HandlePakPlatform->GetMountedPakFilenames(ExistPakFiles);
	//判断当前pak包是否已挂载
	if (ExistPakFiles.Find(PakFilePath) >= 0)
	{
		PlatformFileManager->SetPlatformFile(*HandleOriginPlatform);
		return false;
	}
	int32 Pos = PakFile->GetMountPoint().Find("Content/");
	FString MountPoint = PakFile->GetMountPoint().RightChop(Pos);
	MountPoint = FPaths::ProjectDir() + MountPoint;
	PakFile->SetMountPoint(*MountPoint);
	//使用pak包记录的挂载点挂载pak包
	if (!HandlePakPlatform->Mount(*PakFilePath, 0, *PakFile->GetMountPoint()))
	{
		PlatformFileManager->SetPlatformFile(*HandleOriginPlatform);
		return false;
	}

	// 遍历 pak 里的资源
	TArray<FString> AssetList;
	PakFile->FindPrunedFilesAtPath(AssetList, *PakFile->GetMountPoint(), true, false, true);
	for (FString itemPath : AssetList)
	{
		UE_LOG(LogTemp, Warning, TEXT("%-30s\t%s"), *FPackageName::GetShortName(itemPath), *itemPath);
		// 此处可异步加载资源

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
	// 遍历 pak 里的资源
	TArray<FString> AssetList;
	PakFile->FindPrunedFilesAtPath(AssetList, *PakFile->GetMountPoint(), true, false, true);
	for (FString itemPath : AssetList)
	{
		UE_LOG(LogTemp, Warning, TEXT("%-30s\t%s"), *FPackageName::GetShortName(itemPath), *itemPath);
		// 此处可异步加载资源

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

