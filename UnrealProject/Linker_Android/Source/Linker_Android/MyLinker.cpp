// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLinker.h"

#ifdef __cplusplus 
extern "C" {
#endif

	AMyLinker* AMyLinker::M_StaticSelf = nullptr;
	// Sets default values
	AMyLinker::AMyLinker()
	{
		// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = true;
		M_StaticSelf = this;

	}

	// Called when the game starts or when spawned
	void AMyLinker::BeginPlay()
	{
		Super::BeginPlay();
#if PLATFORM_ANDROID
		//registerLinkerActor(M_StaticSelf);
		#endif
		
	}

	// Called every frame
	void AMyLinker::Tick(float DeltaTime)
	{
		Super::Tick(DeltaTime);

	}

	void AMyLinker::DataManageI(int IValue)
	{
		if (IValue)
		{
			UE_LOG(LogTemp, Error, TEXT("Value is Int, Num = %d"), IValue);
			Int();
		}
		
		return;
	}

	void AMyLinker::DataManageF(float FValue)
	{
		if (FValue)
		{
			UE_LOG(LogTemp, Error, TEXT("Value is Float, Num = %d"), FValue);
			Float();
		}
		
		return;
	}

	void AMyLinker::Action(int Ivalue, float Fvalue)
	{
		if (Ivalue == 0)
		{
			M_StaticSelf->DataManageF(Fvalue);
		}
		else if (Fvalue == 0.0)
		{
			M_StaticSelf->DataManageI(Ivalue);
		}
	}

#ifdef __cplusplus
}
#endif
