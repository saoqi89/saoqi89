// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cloud.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "CloudSpawner.generated.h"

UCLASS()
class SCENEDEMO_API ACloudSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACloudSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnCloud();

	UFUNCTION(BlueprintCallable)
	void Reset();
	
	UPROPERTY(VisibleAnywhere, Category = "Component | Spawn")	
	UBoxComponent* SpawnArea;

	UPROPERTY(VisibleAnywhere, Category = "Component | Trigger")	
	UBoxComponent* TriggerArea;

	UPROPERTY(VisibleAnywhere, Category = "Component | DefaultRoot")	
	USceneComponent* DefaultRootComponent;

	UPROPERTY(EditAnywhere, Category = "Cloud")
	TSubclassOf<ACloud> Cloud;
	
	AMuffin* Muffin;
	
	UPROPERTY(EditAnywhere, Category = "Cloud")
	int InitialSpawnAmount;
	UPROPERTY(EditAnywhere, Category = "Cloud")
	float SpawnSpacing;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
