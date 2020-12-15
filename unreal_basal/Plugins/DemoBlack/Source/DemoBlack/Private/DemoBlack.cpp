// Copyright Epic Games, Inc. All Rights Reserved.

#include "DemoBlack.h"
#include "DemoActor.h"

#define LOCTEXT_NAMESPACE "FDemoBlackModule"

void FDemoBlackModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	int32 MyVar = CVarSomeCoolDebugValue1.GetValueOnGameThread();

	UE_LOG(LogTemp, Log, TEXT("FDemoBlackModule: StartupModule %d"), MyVar);
}

void FDemoBlackModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDemoBlackModule, DemoBlack)