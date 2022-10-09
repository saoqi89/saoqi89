// Fill out your copyright notice in the Description page of Project Settings.

#include "SceneDemo/Public/GameCamera.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SceneDemo/Public/Cloud.h"

// Sets default values
AGameCamera::AGameCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);

	DestoryArea = CreateDefaultSubobject<UBoxComponent>(TEXT("DestoryArea"));
	DestoryArea->SetupAttachment(RootComponent);

	bFollowPlayer = true;
}

// Called when the game starts or when spawned
void AGameCamera::BeginPlay()
{
	Super::BeginPlay();

	Muffin = Cast<AMuffin>(UGameplayStatics::GetPlayerPawn(this, 0));	
	
	PC = UGameplayStatics::GetPlayerController(this, 0);
	PC->SetViewTargetWithBlend(this, 0);
	
}

void AGameCamera::MoveCamera()
{
	FVector TargetPos = FVector (GetActorLocation().X, GetActorLocation().Y, Muffin->GetActorLocation().Z);
	SetActorLocation(TargetPos);
}

void AGameCamera::CheckIfFalling()
{
	if (Muffin->GetVelocity().Z < 0)
	{
		UpdateTimer();
	}
	else
	{
		ResetTimer();
	}
}

void AGameCamera::OnSureFalling()
{
	bFollowPlayer = false;
	float OldCameraPosX = GetActorLocation().X;
	float OldCameraPosY = GetActorLocation().Y;
	SetActorLocation(FVector(OldCameraPosX, OldCameraPosY, 0));

	float OldMuffinPosX = Muffin->GetActorLocation().X;
	float OldMuffinPosY = Muffin->GetActorLocation().Y;
	Muffin->SetActorLocation(FVector(OldMuffinPosX, OldMuffinPosY, 0));

	Muffin->DisableInput(PC);
}

// Called every frame
void AGameCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bFollowPlayer)
	{
		MoveCamera();
		CheckIfFalling();
	}
		

}

void AGameCamera::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ACloud* Cloud = Cast<ACloud>(OtherActor);
	if (Cloud)
	{
		Cloud->Destroy();
	}
}

