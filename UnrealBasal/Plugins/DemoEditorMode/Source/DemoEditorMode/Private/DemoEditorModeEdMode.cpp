// Copyright Epic Games, Inc. All Rights Reserved.

#include "DemoEditorModeEdMode.h"
#include "DemoEditorModeEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FDemoEditorModeEdMode::EM_DemoEditorModeEdModeId = TEXT("EM_DemoEditorModeEdMode");

FDemoEditorModeEdMode::FDemoEditorModeEdMode()
{

}

FDemoEditorModeEdMode::~FDemoEditorModeEdMode()
{

}

void FDemoEditorModeEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FDemoEditorModeEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FDemoEditorModeEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FDemoEditorModeEdMode::UsesToolkits() const
{
	return true;
}




