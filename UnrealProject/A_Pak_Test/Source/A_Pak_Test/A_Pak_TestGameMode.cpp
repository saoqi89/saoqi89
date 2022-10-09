// Copyright Epic Games, Inc. All Rights Reserved.

#include "A_Pak_TestGameMode.h"
#include "A_Pak_TestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AA_Pak_TestGameMode::AA_Pak_TestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	//PlayerControllerClass = AMyPlayerController::StaticClass();
}
