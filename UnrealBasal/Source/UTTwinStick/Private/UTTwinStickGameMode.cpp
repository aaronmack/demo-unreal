// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTTwinStickGameMode.h"
#include "UTTwinStickPawn.h"

AUTTwinStickGameMode::AUTTwinStickGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AUTTwinStickPawn::StaticClass();
}

