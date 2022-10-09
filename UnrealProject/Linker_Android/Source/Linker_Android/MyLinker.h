// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyLinker.generated.h"

UCLASS()
class LINKER_ANDROID_API AMyLinker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyLinker();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Int Manage
	void DataManageI(int IValue);

	//Float Manage
	void DataManageF(float FValue);

	UFUNCTION(BlueprintCallable, Category = "qwe")
	static void Action(int Ivalue, float Fvalue);

	UFUNCTION(BlueprintImplementableEvent)
	void Int();

	UFUNCTION(BlueprintImplementableEvent)
	void Float();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	static AMyLinker* M_StaticSelf;
	

};
