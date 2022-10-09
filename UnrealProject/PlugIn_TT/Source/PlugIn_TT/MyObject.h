// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyObject.generated.h"

/**
 * 
 */
UCLASS()
class PLUGIN_TT_API UMyObject : public UObject
{
	GENERATED_BODY()
public:
	virtual void BeginPlay();
	
};
