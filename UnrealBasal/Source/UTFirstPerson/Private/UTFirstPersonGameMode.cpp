// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTFirstPersonGameMode.h"
#include "UTFirstPersonHUD.h"
#include "UTFirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUTFirstPersonGameMode::AUTFirstPersonGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUTFirstPersonHUD::StaticClass();
}
