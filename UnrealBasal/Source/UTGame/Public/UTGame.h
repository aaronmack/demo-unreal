// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DemoActor.h"
#include "DemoBlack.h"
#include "ExampleLibrary.h"

int var_a = ADemoActor::DemoActorUsefulFunction2();
int var_b = FDemoBlackModule::DemoBlackUsefulFunction1();
int var_c = DemoBlackUsefulFunction();
// int var_d = ExampleLibraryFunction2();  
/* 
	error: The game module 'UTGame• could not be loaded. 
	There may be an operating system error, the module may not be properly set up, 
	or a plugin which has been included into the build has not been turned on.
*/