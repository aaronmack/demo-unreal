// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "HAL/IConsoleManager.h"

#define DllExport   __declspec( dllexport )

#include "UnrealBasal.h"
#include "DemoBlueprintFunctionLibrary.h"

DllExport int DemoBlackUsefulFunction();

class FDemoBlackModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static int DemoBlackUsefulFunction1() { return 1; };
};
