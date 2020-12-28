// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DemoBlueprintFunctionLibrary.generated.h"

// Must include "xxx.generated.h"
USTRUCT(BlueprintType)
struct FDemoStruct
{
	GENERATED_USTRUCT_BODY()

		FDemoStruct(int new_lock_count = 0): lock_count(new_lock_count) {}
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DemoStruct")
		int lock_count = 0;
};


/**
 * 
 */
UCLASS()
class UNREALBASAL_API UDemoBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	/** Starts an analytics session without any custom attributes specified */
	UFUNCTION(BlueprintCallable, Category = "MyDemoBlueprint")
	static bool UsefulFunction();

	UFUNCTION(BlueprintCallable, Category = "MyDemoBlueprint")
	static bool UsefulFunction1();

public:
	UFUNCTION(BlueprintCallable, Category = "MyDemoBlueprint")
	static int UsefulFunction2();


public:
	UFUNCTION(BlueprintPure, Category="PythonDemo", meta=(ScriptMethod="IsLocked"))
	static bool IsStructLocked(const FDemoStruct& InStruct);

	UFUNCTION(BlueprintCallable, Category = "PythonDemo", meta = (ScriptMethod = "Lock"))
	static void LockStruct(UPARAM(ref) FDemoStruct& InStruct);

	UFUNCTION(BlueprintCallable, Category = "PythonDemo", meta = (ScriptMethod = "Unlock"))
	static void UnlockStruct(UPARAM(ref) FDemoStruct& InStruct);
};
