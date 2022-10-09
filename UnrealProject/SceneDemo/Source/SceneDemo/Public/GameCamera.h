// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Muffin.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameCamera.generated.h"

UCLASS()
class SCENEDEMO_API AGameCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* DestoryArea;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComp;

	APlayerController* PC;

	AMuffin* Muffin;

	void MoveCamera();

	void CheckIfFalling();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTimer();

	UFUNCTION(BlueprintImplementableEvent)
	void ResetTimer();

	UFUNCTION(BlueprintCallable)
	void OnSureFalling();

	UPROPERTY(BlueprintReadWrite)
	bool bFollowPlayer;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
