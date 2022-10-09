// Fill out your copyright notice in the Description page of Project Settings.


#include "Mount.h"

#include "IPlatformFilePak.h"

// Sets default values
AMount::AMount()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool AMount::Mount(const FString PakPath, const FString MountPath)
{
	pak_path = PakPath;
	Mount_Path = MountPath;
	bool Result = false;

	// 切换到 pak平台
	FPlatformFileManager::Get().SetPlatformFile(*PakPlatformFile);

	// 获取pak文件
	PakFile = new FPakFile(InnerPlatformFile, *pak_path, false);
	MountPoint = PakFile->GetMountPoint();
	UE_LOG(LogTemp, Warning, TEXT("Default Mount Point: %s"), *MountPoint);

#if !WITH_EDITOR

	// PIE模式下，MountPoint 使用绝对路径
	MountPoint = FPaths::ConvertRelativePathToFull(MountPoint);
	UE_LOG(LogTemp, Warning, TEXT("Default Mount Point Full Path: %s"), *MountPoint);
	
	// 设置pak文件的Mount点，因为在制作pak的时候已在文本中设定 mount point，故省略此步骤
	MountPoint = FPaths::ProjectContentDir() + Mount_Path;

	// 可在此处检测 默认MountPoint的绝对路径释放和本条语句执行结果是否一致
	MountPoint = FPaths::ConvertRelativePathToFull(MountPoint);

	static  FString aPath = FPaths::GetProjectFilePath();
	FString asd = FPaths::ProjectDir();
	
	PakFile->SetMountPoint(*MountPoint);
	UE_LOG(LogTemp, Warning, TEXT("New Mount Point Full Path: %s"), *MountPoint);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("PIE"));

#else

	MountPoint = FPaths::ConvertRelativePathToFull(MountPoint);
	// 打包模式下，MountPoint 使用相对路径
	int32 pos1 = MountPoint.Find(TEXT("Content/"));
	FString NewMountPoint = MountPoint.RightChop(pos1);
	FString ProjectDir = FPaths::ProjectDir();
	NewMountPoint = ProjectDir + NewMountPoint;

	FString MountPoint1(FPaths::ProjectContentDir());

	FString Engine(FPaths::EngineContentDir());
	PakFile->SetMountPoint(*NewMountPoint);
	UE_LOG(LogTemp, Warning, TEXT("New Mount Point Full Path: %s"), *NewMountPoint);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Packering"));

#endif

	return true;
	
}

// Called when the game starts or when spawned
void AMount::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMount::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

