// Copyright Epic Games, Inc. All Rights Reserved.

#include "DemoEditorMode.h"
#include "DemoEditorModeEdMode.h"

#define LOCTEXT_NAMESPACE "FDemoEditorModeModule"

void FDemoEditorModeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FDemoEditorModeEdMode>(FDemoEditorModeEdMode::EM_DemoEditorModeEdModeId, LOCTEXT("DemoEditorModeEdModeName", "DemoEditorModeEdMode"), FSlateIcon(), true);
}

void FDemoEditorModeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FDemoEditorModeEdMode::EM_DemoEditorModeEdModeId);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDemoEditorModeModule, DemoEditorMode)