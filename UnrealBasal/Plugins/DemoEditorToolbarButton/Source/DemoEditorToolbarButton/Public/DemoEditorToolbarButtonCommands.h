// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "DemoEditorToolbarButtonStyle.h"

class FDemoEditorToolbarButtonCommands : public TCommands<FDemoEditorToolbarButtonCommands>
{
public:

	FDemoEditorToolbarButtonCommands()
		: TCommands<FDemoEditorToolbarButtonCommands>(TEXT("DemoEditorToolbarButton"), NSLOCTEXT("Contexts", "DemoEditorToolbarButton", "DemoEditorToolbarButton Plugin"), NAME_None, FDemoEditorToolbarButtonStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
