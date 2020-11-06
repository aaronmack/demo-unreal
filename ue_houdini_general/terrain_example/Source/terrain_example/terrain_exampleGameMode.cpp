// Copyright Epic Games, Inc. All Rights Reserved.

#include "terrain_exampleGameMode.h"
#include "terrain_exampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

Aterrain_exampleGameMode::Aterrain_exampleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
