// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Muffin.generated.h"

UCLASS()
class SCENEDEMO_API AMuffin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMuffin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	APlayerController* PC;

	FVector LaunchVelocity;
	
	void MoveTowardsCursor();

	void LaunchOnAnyKeyPressed();

	void SetSpeed();

	void GameOver();

	UFUNCTION(BlueprintCallable)
	void GameReset();

	UFUNCTION(BlueprintImplementableEvent)
	void DisPlayRestart();

	UPROPERTY(BlueprintReadOnly)
	bool bDead;
	
	bool bGameStarted;
	
	int Score;
	
	UPROPERTY(EditAnywhere, Category = "Speed")
	float AirSpeed;
	UPROPERTY(EditAnywhere, Category = "Speed")
	float GroundSpeed;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Launch();

	void IncreaseScore();

	int GetScore() const;

};
