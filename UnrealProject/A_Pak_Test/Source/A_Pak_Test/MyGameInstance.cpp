// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

//UMyGameInstance::BeginPlay()
//{
//	Super::BeginPlay();
//
//	//获取当前使用的平台
//	InnerPlatformFile = &FPlatformFileManager::Get().GetPlatformFile();
//	UE_LOG(LogTemp, Warning, TEXT("InnerPlatformFile: %s"), InnerPlatformFile->GetName());
//
//	//初始化PakPlatformFile 
//	PakPlatformFile = MakeShareable(new FPakPlatformFile());
//	PakPlatformFile.Get()->Initialize(InnerPlatformFile, TEXT(""));
//
//}

void  UMyGameInstance::Init()
{
	//获取当前使用的平台
	InnerPlatformFile = &FPlatformFileManager::Get().GetPlatformFile();
	UE_LOG(LogTemp, Warning, TEXT("InnerPlatformFile: %s"), InnerPlatformFile->GetName());

	//初始化PakPlatformFile 
	PakPlatformFile = MakeShareable(new FPakPlatformFile());
	PakPlatformFile.Get()->Initialize(InnerPlatformFile, TEXT(""));
}

bool UMyGameInstance::LoadPak(FString PakPath)
{
	bool Result = false;

	// 切换到 pak平台
	FPlatformFileManager::Get().SetPlatformFile(*PakPlatformFile.Get());

	// 获取pak文件
	//TSharedPtr<FPakFile> PakFile = MakeShareable(new FPakFile(InnerPlatformFile, *PakPath, false));

	TRefCountPtr<FPakFile> PakFile = new FPakFile(InnerPlatformFile, *PakPath, false);
	FString MountPoint = PakFile->GetMountPoint();
	UE_LOG(LogTemp, Warning, TEXT("Default Mount Point: %s"), *MountPoint);

#if WITH_EDITOR
	// PIE模式下，MountPoint 使用绝对路径
	// 打包模式下，MountPoint 使用相对路径
	MountPoint = FPaths::ConvertRelativePathToFull(MountPoint);
	UE_LOG(LogTemp, Warning, TEXT("Default Mount Point Full Path: %s"), *MountPoint);

	// 设置pak文件的Mount点，因为在制作pak的时候已在文本中设定 mount point，故省略此步骤
	MountPoint = FPaths::ProjectContentDir() + TEXT("DLC/");

	// 可在此处检测 默认MountPoint的绝对路径释放和本条语句执行结果是否一致
	MountPoint = FPaths::ConvertRelativePathToFull(MountPoint);

	PakFile->SetMountPoint(*MountPoint);
	UE_LOG(LogTemp, Warning, TEXT("New Mount Point Full Path: %s"), *MountPoint);
#endif

	// 对pak文件进行挂载
	if (PakPlatformFile->Mount(*PakPath, 1, *MountPoint))
	{
		// 加载 pak 里的资源
		UClass* BP_PakTestClass = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/DLC/BP_MyActor.BP_MyActor_C'"));
		if (BP_PakTestClass)
		{
			GetWorld()->SpawnActor<AActor>(BP_PakTestClass, FVector::ZeroVector, FRotator::ZeroRotator);
			Result = true;
		}
		else
			UE_LOG(LogTemp, Error, TEXT("Load BP_PakTest1 Class Failed"));

		// 遍历 pak 里的资源
		TArray<FString> AssetList;
		PakFile->FindPrunedFilesAtPath(AssetList, *PakFile->GetMountPoint(), true, false, true);
		for (FString itemPath : AssetList)
		{
			UE_LOG(LogTemp, Warning, TEXT("%-30s\t%s"), *FPackageName::GetShortName(itemPath), *itemPath);
			// 此处可异步加载资源
		}
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Mount Pak Failed"));

	// 设置回原来的PlatformFile, UE4.26 
	// 不加该条语句，本测试崩溃，报错：Pure Virtual function being called while application was running
	FPlatformFileManager::Get().SetPlatformFile(*InnerPlatformFile);

	return Result;

}