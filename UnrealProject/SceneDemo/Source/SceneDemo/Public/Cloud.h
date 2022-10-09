// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Muffin.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Cloud.generated.h"

UCLASS()
class SCENEDEMO_API ACloud : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACloud();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Show")
	UStaticMeshComponent* CloudPlane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Show")
	UStaticMeshComponent* RainPlane;
	
	UPROPERTY(EditAnywhere, Category = "Show")
	TArray<UTexture*>Textures;

	UPROPERTY(EditAnywhere, Category = "Show")
	UTextRenderComponent* ScoreText;

	UPROPERTY(BlueprintReadOnly, Category = "Show")
	UMaterialInstanceDynamic* MatInstance;
	UMaterialInterface* MatInterface;

	void SetARandomCloudTexture();

	void DisplayScore();

	UFUNCTION(BlueprintImplementableEvent)
	void FadeOut();

	AMuffin* Muffin;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundCue* CloudSound;

	UPROPERTY(VisibleAnywhere, Category = "Sound")
	UAudioComponent* AudioComp;
	
	void EnableRain();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
