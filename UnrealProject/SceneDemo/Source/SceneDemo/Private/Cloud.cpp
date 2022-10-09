// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneDemo/Public/Cloud.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SceneDemo/Public/Muffin.h"

// Sets default values
ACloud::ACloud()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;

	CloudPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CloudPlane"));
	CloudPlane->SetupAttachment(RootComponent);

	RainPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RainPlane"));
	RainPlane->SetupAttachment(CloudPlane);
	
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText"));
	ScoreText->SetupAttachment(RootComponent);

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(CloudPlane);

}

// Called when the game starts or when spawned
void ACloud::BeginPlay()
{
	Super::BeginPlay();

	SetARandomCloudTexture();

	EnableRain();
	
}

void ACloud::SetARandomCloudTexture()
{
	MatInterface = CloudPlane->GetMaterial(0);
	MatInstance = CloudPlane->CreateDynamicMaterialInstance(0, MatInterface);

	int Index = FMath::RandRange(0, 2);
	if (Textures[Index])
	{
		MatInstance->SetTextureParameterValue(FName(TEXT("Texture")), Textures[Index]);
        
		CloudPlane->SetMaterial(0, MatInstance);
	}
	
}

void ACloud::DisplayScore()
{
	Muffin->IncreaseScore();
	ScoreText->SetText(FText::FromString(FString::FromInt(Muffin->GetScore())));
}

void ACloud::EnableRain()
{
	int Index = FMath::RandRange(0, 2);
	if (Index == 0)
	{
		RainPlane->SetVisibility(true);
		AudioComp->Activate(true);
	}
}

// Called every frame
void ACloud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACloud::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	Muffin = Cast<AMuffin>(OtherActor);
	if (Muffin)
	{
		Muffin->Launch();
		DisplayScore();

		UGameplayStatics::PlaySoundAtLocation(this, CloudSound, GetActorLocation());
		
		FadeOut();
		//Destroy();
	}
}

