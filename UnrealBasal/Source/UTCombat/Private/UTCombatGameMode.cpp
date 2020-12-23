// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTCombatGameMode.h"
#include "UTCombatCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUTCombatGameMode::AUTCombatGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonBP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
