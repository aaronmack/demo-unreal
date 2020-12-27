// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DemoObject.generated.h"

/**
 * 
 */
UCLASS()
class UNREALBASAL_API UDemoObject : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="PythonDemo")
	/**
	 * 
	 * function name in Unreal [udo_py_useful_function]
	 */
	bool UDOPyUsefulFunction(const int32 InValue);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PythonDemo")
	int32 TestVar1 = 0;
};
