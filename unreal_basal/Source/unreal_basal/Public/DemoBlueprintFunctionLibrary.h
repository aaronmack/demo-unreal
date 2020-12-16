// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DemoThirdPartyLibrary.h"
#include "DemoBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_BASAL_API UDemoBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	/** Starts an analytics session without any custom attributes specified */
	UFUNCTION(BlueprintCallable, Category = "MyDemoBlueprint")
	static bool UsefulFunction();

	UFUNCTION(BlueprintCallable, Category = "MyDemoBlueprint")
	static bool UsefulFunction1();
};
