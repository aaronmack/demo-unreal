// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "DemoEditorStandaloneWindowStyle.h"

class FDemoEditorStandaloneWindowCommands : public TCommands<FDemoEditorStandaloneWindowCommands>
{
public:

	FDemoEditorStandaloneWindowCommands()
		: TCommands<FDemoEditorStandaloneWindowCommands>(TEXT("DemoEditorStandaloneWindow"), NSLOCTEXT("Contexts", "DemoEditorStandaloneWindow", "DemoEditorStandaloneWindow Plugin"), NAME_None, FDemoEditorStandaloneWindowStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};