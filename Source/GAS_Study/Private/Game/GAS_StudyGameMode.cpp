// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game/GAS_StudyGameMode.h"

#include "UObject/ConstructorHelpers.h"

AGAS_StudyGameMode::AGAS_StudyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	
}
