// Copyright Epic Games, Inc. All Rights Reserved.

#include "DemoEditorToolbarButtonCommands.h"

#define LOCTEXT_NAMESPACE "FDemoEditorToolbarButtonModule"

void FDemoEditorToolbarButtonCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "DemoEditorToolbarButton", "Execute DemoEditorToolbarButton action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
