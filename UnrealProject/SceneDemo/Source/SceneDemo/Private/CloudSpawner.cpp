// Fill out your copyright notice in the Description page of Project Settings.

	
#include "SceneDemo/Public/CloudSpawner.h"

#include <ThirdParty/CryptoPP/5.6.5/include/misc.h>

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SceneDemo/Public/Cloud.h"

// Sets default values
ACloudSpawner::ACloudSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	TriggerArea = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerArea"));
	DefaultRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComponent"));

	RootComponent = DefaultRootComponent;
	SpawnArea->SetupAttachment(DefaultRootComponent);
	TriggerArea->SetupAttachment(DefaultRootComponent);

	InitialSpawnAmount = 6;
	SpawnSpacing = 300.0f;

	
}

// Called when the game starts or when spawned
void ACloudSpawner::BeginPlay()
{
	Super::BeginPlay();
	Reset();
}

void ACloudSpawner::SpawnCloud()
{
	FVector SpawnOrigin = SpawnArea->Bounds.Origin;     //中心点
	FVector SpawnExtent = SpawnArea->Bounds.BoxExtent;  //范围
	
	float YLocation =  UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent).Y;
	FVector SpawnLocation = FVector(SpawnArea->GetComponentLocation().X, YLocation, SpawnArea->GetComponentLocation().Z);

	FActorSpawnParameters SpawnParameters;
	GetWorld()->SpawnActor<ACloud>(Cloud, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);

	AddActorWorldOffset(FVector(0, 0, SpawnSpacing));
}

void ACloudSpawner::Reset()
{
	InitialSpawnAmount = 6;

	SetActorLocation(FVector::ZeroVector);

	TArray<AActor*>FoundClouds;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACloud::StaticClass(), FoundClouds);
	for (AActor* TActor : FoundClouds)
	{
		ACloud* MyCloud = Cast<ACloud>(TActor);
		if (MyCloud != nullptr)
		{
			MyCloud->Destroy();
		}
	}
	
	while (InitialSpawnAmount > 0)
	{
		InitialSpawnAmount--;
		SpawnCloud();
	}
}

// Called every frame
void ACloudSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACloudSpawner::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	Muffin = Cast<AMuffin>(OtherActor);
	if (Muffin)
	{
		SpawnCloud();
	}
}
