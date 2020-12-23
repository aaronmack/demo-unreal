// Copyright Epic Games, Inc. All Rights Reserved.

#include "DemoEditorStandaloneWindowCommands.h"

#define LOCTEXT_NAMESPACE "FDemoEditorStandaloneWindowModule"

void FDemoEditorStandaloneWindowCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "DemoEditorStandaloneWindow", "Bring up DemoEditorStandaloneWindow window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
