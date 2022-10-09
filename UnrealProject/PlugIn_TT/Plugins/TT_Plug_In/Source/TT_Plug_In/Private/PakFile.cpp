// Fill out your copyright notice in the Description page of Project Settings.


#include "PakFile.h"
#include <map>
#include <ThirdParty/openexr/Deploy/OpenEXR-2.3.0/OpenEXR/include/ImathNamespace.h>

#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/SUserWidget.h"
#include "Widgets/Images/SImage.h"


// Sets default values
APakFile::APakFile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Fill out your copyright notice in the Description page of Project Settings.

void APakFile::BeginPlay()
{
	Super::BeginPlay();

	//获取当前使用的平台
	InnerPlatformFile = &FPlatformFileManager::Get().GetPlatformFile();
	UE_LOG(LogTemp, Warning, TEXT("InnerPlatformFile: %s"), InnerPlatformFile->GetName());

	//初始化PakPlatformFile 
	PakPlatformFile = new FPakPlatformFile();
	PakPlatformFile->Initialize(InnerPlatformFile, TEXT(""));

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GWorld, 0);
	PlayerController->bShowMouseCursor = true;//显示鼠标
	
}

void APakFile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	MMap.Empty();

	if (PakPlatformFile)
	{
		PakPlatformFile->Unmount(*pak_path);
		//FPlatformFileManager::Get().RemovePlatformFile(PakPlatformFile);
		PakPlatformFile = nullptr;
	}
}

void APakFile::Init(const FString PakPath, const FString MountPath, UUserWidget* UMG, const FString Msg)
{
	pak_path = PakPath;
	Mount_Path = MountPath;
	_UMG = UMG;
	_Msg = Msg;
	//Image = Img;
	//APak_File::GetString(Msg);
	//APak_File::CreateImageWidget(UMG);
}

bool APakFile::Mount()
{
	bool Result = false;

	// 切换到 pak平台
	FPlatformFileManager::Get().SetPlatformFile(*PakPlatformFile);

	// 获取pak文件
	PakFile = new FPakFile(InnerPlatformFile, *pak_path, false);
	FString MountPoint = PakFile->GetMountPoint();
	UE_LOG(LogTemp, Warning, TEXT("Default Mount Point: %s"), *MountPoint);

#if WITH_EDITOR
	
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

	// 对pak文件进行挂载
	if (PakPlatformFile->Mount(*pak_path, 1, *MountPoint))
	{
		LoadFile();
		Result = true;
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Mount Pak Failed"));
		
	// 设置回原来的PlatformFile
	// 不加该条语句，本测试崩溃，报错：Pure Virtual function being called while application was running
	FPlatformFileManager::Get().SetPlatformFile(*InnerPlatformFile);

	return Result;
}

void APakFile::LoadFile()
{
	// 遍历 pak 里的资源
	PakFile->FindPrunedFilesAtPath(AssetList, *PakFile->GetMountPoint(), true, false, true);
	for (int i = 0; i < AssetList.Num(); i++)
	{
		FString itemPath = AssetList[i];
		UE_LOG(LogTemp, Warning, TEXT("%-30s\t%s"), *FPackageName::GetShortName(itemPath), *itemPath);

		FString NewFileName = itemPath;
		int32 pos = NewFileName.Find(TEXT("/Content/"));
		NewFileName = NewFileName.RightChop(pos + 8);
		//NewFileName = "/Game" + NewFileName + "." + name;

		FString ShortName = FPackageName::GetShortName(NewFileName);
		FString LeftStr, RightStr;
		ShortName.Split(TEXT("."), &LeftStr, &RightStr);
		
		// Edioor中文件路径: /Game/MountPath/Name.Name
		NewFileName = "/Game/" + Mount_Path + LeftStr + "." + LeftStr;

		FString Name = FString::Printf(TEXT("Texture2D'%s'"), *NewFileName);

		FString FileName = Name.Right(16);
		//文件加载格式： TEXT("Texture2D'/Game/MountPath/Name.Name'"));
		Obj = FindObject<UTexture2D>(nullptr, *Name);
		if (!Obj)
		{
			Obj = LoadObject<UTexture2D>(nullptr, *Name);
			if (Obj)
			{
				/*MMap[i].Texture2D = Obj;
				//Texture2Darr.Add(Obj);
				MMap[i].Texture2D = Obj;*/
				Ftt_State.Texture2D = Obj;
				MMap.Add(i, Ftt_State);
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("hello"));
			}
		}
		else
			UE_LOG(LogTemp, Error, TEXT("Load File Failed"));
		
	}
}

void APakFile::UnMountPak()
{
	if (PakPlatformFile)
	{
		PakPlatformFile->Unmount(*pak_path);
		FPlatformFileManager::Get().RemovePlatformFile(PakPlatformFile);
		PakPlatformFile = nullptr;
	}
}

void APakFile::CreateImageWidget(UUserWidget* UMG)
{
	
    UCanvasPanel* RootPanel = Cast<UCanvasPanel>(UMG->GetRootWidget());

	TArray<UWidget*> const NodesArr = RootPanel->GetAllChildren();
	UE_LOG(LogTemp, Error, TEXT("!!! num %d"), NodesArr.Num());	
	
    if (RootPanel)
    {
    	/*NewImage = UMG->WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
    	RootPanel->AddChildToCanvas(NewImage);
    	UMG->WidgetTree->RootWidget = RootPanel;*/
    	//NewImage->SetBrushSize(FVector2D(800, 800));
    	//NewImage->SetRenderTranslation(FVector2D(Ftt_State.InX, Ftt_State.InY));
    	//NewImage->SetBrushFromTexture(Texture2Darr[1]);
    	
		for (int i = 0; i < MMap.Num(); i++)
		{
			UImage* Image1 = UMG->WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
			RootPanel->AddChildToCanvas(Image1);
			/*Image1->SetBrushSize(FVector2D(450.0f, 450.0f));
			Image1->SetRenderTranslation(FVector2D(Ftt_State.InX, Ftt_State.InY));*/

			MMap[i].Image = Image1;
			//MMap.Add(i, Image1);
		}
    	
    	UMG->WidgetTree->RootWidget = RootPanel;
    	
    }
    TArray<UWidget*> const NodesArr2 = RootPanel->GetAllChildren();
    UE_LOG(LogTemp, Error, TEXT("!!! num %d"), NodesArr2.Num());
}

void APakFile::GetString(const FString Msg)
{
	
	TArray<FString>List;
	Msg.ParseIntoArray(List, TEXT(";"), true);

	for (int i = 0; i < List.Num(); i++)
	{
		FString ID, X, Y;
		List[i].Split(TEXT(","), &ID, &X);
		X.Split(TEXT(","), &X, &Y);
		MMap[i].Index = FCString::Atof(*ID);
		MMap[i].InX = FCString::Atof(*X);
		MMap[i].InY = FCString::Atof(*Y);

		UE_LOG(LogTemp, Error, TEXT("Index: %d"), Ftt_State.Index);
		UE_LOG(LogTemp, Error, TEXT("x: %f"), Ftt_State.InX);
		UE_LOG(LogTemp, Error, TEXT("y: %f"), Ftt_State.InY);
		
	}
}

void APakFile::ShowAll()
{
	int const _Len = MMap.Num();
	static int i = 0;

	GetString(_Msg);
	CreateImageWidget(_UMG);

	if (!MMap[i].IsShow)
	{
		for (i = 0; i < _Len; i++)
		{
			const FVector2D Size = MMap[i].Texture2D->GetImportedSize();
			MMap[i].Image->SetBrushSize(FVector2D(65.0f, 65.0f));
			MMap[i].Image->SetRenderTranslation(FVector2D(MMap[i].InX, MMap[i].InY));
			MMap[i].Image->SetBrushFromTexture(MMap[i].Texture2D);
			MMap[i].IsShow = true;
		}
	}


}

void APakFile::HideAll()
{
	if (MMap[1].IsShow)
	{
		for (int i = 0; i < MMap.Num(); i++)
		{
			FSlateBrush Brush;
			MMap[i].Image->SetBrush(Brush);
			MMap[i].IsShow = false;
		}
	}
	
	
}

void APakFile::ShowTTByIndex(const int ID)
{
	GetString(_Msg);
	CreateImageWidget(_UMG);
	if (!MMap[ID].IsShow)
	{
		Obj = MMap[ID].Texture2D;
		MMap[ID].Image->SetBrushSize(FVector2D(64.0f, 64.0f));
		MMap[ID].Image->SetBrushFromTexture(Obj);
		MMap[ID].IsShow = true;
	}
}

void APakFile::HideTTByIndex(const int ID)
{
	if (MMap[ID].IsShow)
	{
		FSlateBrush Brush;
		MMap[ID].Image->SetBrush(Brush);
		MMap[ID].IsShow = false;
	}
}

void APakFile::FlashTT(const int ID, const int Hz)
{
	Tick = Hz;
	GetWorld()->GetTimerManager().ClearTimer(TestHandel);
	GetWorld()->GetTimerManager().SetTimer(TestHandel, this, &APakFile::Change, Tick, true);
	
}

void APakFile::StopFlashTT(const int ID)
{
	GetWorld()->GetTimerManager().ClearTimer(TestHandel);
}



void APakFile::Change()
{
	int len_t = AssetList.Num();
	static int i = 0;

	if (i <= len_t)
	{
		
		i += 1;
	}
	else
	{
		i = 0;
	}

}




