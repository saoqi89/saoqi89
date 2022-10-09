// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneDemo/Public/Muffin.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMuffin::AMuffin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LaunchVelocity = FVector(0, 0, 1500);

	AirSpeed = 3500.0f;
	GroundSpeed = 300.0f;

	
}

// Called when the game starts or when spawned
void AMuffin::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<APlayerController>(GetController());
	PC->bShowMouseCursor = true;

	GameReset();
}

void AMuffin::MoveTowardsCursor()
{
	FVector MouseLocation, MouseDirection;
	PC->DeprojectMousePositionToWorld(MouseLocation, MouseDirection); //获得世界坐标下鼠标的位置和方向
	float YDirection = FMath::Clamp(MouseLocation.Y - GetActorLocation().Y, -1.0f, 1.0f);
	FVector Direction = FVector(0, YDirection, 0);
	float ScaleValue = FMath::Clamp(FMath::Abs(MouseLocation.Y - GetActorLocation().Y)/100, 0.0f, 1.0f);
	AddMovementInput(Direction, ScaleValue);
	
}

void AMuffin::LaunchOnAnyKeyPressed()
{

	if (!GetCharacterMovement()->IsFalling() && !bGameStarted)
	{
		Launch();
	}
	
	if (!bGameStarted)
	{
		bGameStarted = true;
	}
	
}

void AMuffin::SetSpeed()
{
	if (GetCharacterMovement()->IsFalling())
	{
		GetCharacterMovement()->MaxWalkSpeed = AirSpeed;
	}
	else
	{
		if (bGameStarted)
		{
			GameOver();
		}
		GetCharacterMovement()->MaxWalkSpeed = GroundSpeed;
	}
}

void AMuffin::GameOver()
{
	bDead = true;
	SetActorRotation(FRotator::ZeroRotator);
	EnableInput(PC);
	DisPlayRestart();
}

void AMuffin::GameReset()
{
	bGameStarted = false;
	Score = 0;
	bDead = false;
}


void AMuffin::Launch()
{
	LaunchCharacter(LaunchVelocity, false, true);
}

void AMuffin::IncreaseScore()
{
	Score++;
}

int AMuffin::GetScore() const
{
	return Score;
}

// Called every frame
void AMuffin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bDead)
	{
		MoveTowardsCursor();
		SetSpeed();
	}
	

}

// Called to bind functionality to input
void AMuffin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMuffin::LaunchOnAnyKeyPressed);

}

