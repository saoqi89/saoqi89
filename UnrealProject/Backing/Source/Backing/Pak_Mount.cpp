// Fill out your copyright notice in the Description page of Project Settings.


#include "Pak_Mount.h"

void APak_Mount::BeginPlay()
{
	Super::BeginPlay();

	//获取当前使用的平台
	InnerPlatformFile = &FPlatformFileManager::Get().GetPlatformFile();
	UE_LOG(LogTemp, Warning, TEXT("InnerPlatformFile: %s"), InnerPlatformFile->GetName());

	//初始化PakPlatformFile 
	PakPlatformFile = new FPakPlatformFile();
	PakPlatformFile->Initialize(InnerPlatformFile, TEXT(""));
	
}

bool APak_Mount::Mount(const FString& PakFileName, UImage* Img)
{
	bool Result = false;
	Path = PakFileName;

	// 切换到 pak平台
	FPlatformFileManager::Get().SetPlatformFile(*PakPlatformFile);

	// 获取pak文件
	PakFile1 = new FPakFile(InnerPlatformFile, *PakFileName, false);
	//TSharedPtr<FPakFile> PakFile = MakeShareable(new FPakFile(InnerPlatformFile, *PakFileName, false));
	//PakFile1 = new FPakFile(InnerPlatformFile, *PakFileName, false);
	FString MountPoint = PakFile1->GetMountPoint();
	UE_LOG(LogTemp, Warning, TEXT("Default Mount Point: %s"), *MountPoint);

#if WITH_EDITOR
	
	// PIE模式下，MountPoint 使用绝对路径
	MountPoint = FPaths::ConvertRelativePathToFull(MountPoint);
	UE_LOG(LogTemp, Warning, TEXT("Default Mount Point Full Path: %s"), *MountPoint);
	

	// 设置pak文件的Mount点，因为在制作pak的时候已在文本中设定 mount point，故省略此步骤
	MountPoint = FPaths::ProjectContentDir() + TEXT("TT/");

	// 可在此处检测 默认MountPoint的绝对路径释放和本条语句执行结果是否一致
	MountPoint = FPaths::ConvertRelativePathToFull(MountPoint);

	static  FString aPath = FPaths::GetProjectFilePath();
	FString asd = FPaths::ProjectDir();
	
	PakFile1->SetMountPoint(*MountPoint);
	UE_LOG(LogTemp, Warning, TEXT("New Mount Point Full Path: %s"), *MountPoint);

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("PIE"));
#else
	
	// 打包模式下，MountPoint 使用相对路径
	int32 pos1 = MountPoint.Find(TEXT("Content/"));
	FString NewMountPoint = MountPoint.RightChop(pos1);
	FString ProjectDir = FPaths::ProjectDir();
	NewMountPoint = ProjectDir + NewMountPoint;

	PakFile1->SetMountPoint(*NewMountPoint);
	UE_LOG(LogTemp, Warning, TEXT("New Mount Point Full Path: %s"), *NewMountPoint);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Packering"));
	
#endif

	// 对pak文件进行挂载
	if (PakPlatformFile->Mount(*PakFileName, 1, *MountPoint))
	{
		LoadFile(Img);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Mount Pak Failed"));
		
	// 设置回原来的PlatformFile, UE4.26 
	// 不加该条语句，本测试崩溃，报错：Pure Virtual function being called while application was running
	FPlatformFileManager::Get().SetPlatformFile(*InnerPlatformFile);

	return Result;
}

void APak_Mount::LoadFile(UImage* Img)
{
	//Image = Img;

	// 遍历 pak 里的资源
	TArray<FString> AssetList;
	PakFile->FindPrunedFilesAtPath(AssetList, *PakFile->GetMountPoint(), true, false, true);
	for (FString itemPath : AssetList)
	{
		UE_LOG(LogTemp, Warning, TEXT("%-30s\t%s"), *FPackageName::GetShortName(itemPath), *itemPath);
		// 此处可异步加载资源
#if WITH_EDITOR
		FString NewFileName = itemPath;
		NewFileName.RemoveFromEnd(TEXT(".uasset"));
		FString name = NewFileName.Right(7);
#else
		FString NewFileName = itemPath;
		NewFileName.RemoveFromEnd(TEXT(".uexp"));
		FString name = NewFileName.Right(5);
#endif
		int32 pos = NewFileName.Find(TEXT("/Content/"));
		NewFileName = NewFileName.RightChop(pos + 8);
		NewFileName = "/Game" + NewFileName + "." + name;
		//NewFileName = "Texture2D''";

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

FString pak_path;
void APak_Mount::MountPak()
{
	
	IPlatformFile* Platform_File = &(FPlatformFileManager::Get().GetPlatformFile());
	Pak_Platform_File = new FPakPlatformFile();
	Pak_Platform_File->Initialize(Platform_File, TEXT(""));
	FPlatformFileManager::Get().SetPlatformFile(*Pak_Platform_File);

#if WITH_EDITOR
	
	FString mountpoint_path = FPaths::ProjectContentDir() + "DLC/";
	mountpoint_path = FPaths::ConvertRelativePathToFull(mountpoint_path);
	UE_LOG(LogClass, Log, TEXT("MountPath = %s"), *mountpoint_path);

#else

	//"../../../PlugIn_TT/Content/DLC/"
	FString mountpoint_path = FPaths::ProjectContentDir() + "DLC/";

#endif
	
	PakFile = new FPakFile(Pak_Platform_File, *pak_path, false);
	PakFile->SetMountPoint(*mountpoint_path);
	if (!Pak_Platform_File->Mount(*pak_path, 0, *mountpoint_path))
	{
		UE_LOG(LogClass, Log, TEXT("Error"));
	}
	else
	{
		LoadFile(Image);
	}
}

void APak_Mount::UnMountPak()
{
	if (Pak_Platform_File)
	{
		Pak_Platform_File->Unmount(*pak_path);
		FPlatformFileManager::Get().RemovePlatformFile(Pak_Platform_File);
		Pak_Platform_File = nullptr;
	}
}

void APak_Mount::Init(const FString PakPath, const FString MountPath, UImage* Img)
{
	pak_path = PakPath;
	Image = Img;
}