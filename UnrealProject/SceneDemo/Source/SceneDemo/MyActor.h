// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class SCENEDEMO_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	int A;

	UPROPERTY(EditDefaultsOnly)
	int B;

public:
	UPROPERTY(BlueprintReadOnly)
	int AAA;

	UPROPERTY(BlueprintReadWrite)
	int Bbb;

	UFUNCTION(BlueprintCallable)
	static void Test();

	void Asd();

	UFUNCTION(BlueprintImplementableEvent)
	void FunctionEvent();

	/*UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "MyBPAsyncAction")
		static UMyBPAsyncAction* AsyncCountdown(UObject* WorldContextObject, AAsyncTickActor* AsyncTickActor, int32 StartNum);*/

	/*UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void asd();*/
};
