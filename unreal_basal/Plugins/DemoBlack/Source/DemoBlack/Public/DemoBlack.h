// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "HAL/IConsoleManager.h"
//#include "unreal_basal.h"
//#include "DemoBlueprintFunctionLibrary.h"

void DemoBlackUsefulFunction();

class FDemoBlackModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
