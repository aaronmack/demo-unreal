// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoBlueprintFunctionLibrary.h"

bool UDemoBlueprintFunctionLibrary::UsefulFunction()
{	
	static const auto CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("MyGame.SomeCoolDebugValue"));
	int32 Value = CVar->GetInt();
	UE_LOG(LogTemp, Log, TEXT("UDemoBlueprintFunctionLibrary::UsefulFunction Value %d"), Value);

	//Does something
	return false;
}

bool UDemoBlueprintFunctionLibrary::UsefulFunction1()
{

	UE_LOG(LogTemp, Log, TEXT("UDemoBlueprintFunctionLibrary::UsefulFunction1 Value %d"), -2);

	//Does something
	return false;
}

int UDemoBlueprintFunctionLibrary::UsefulFunction2() {
	
	//Does something
	return 1;
}

bool UDemoBlueprintFunctionLibrary::IsStructLocked(const FDemoStruct& InStruct)
{
	return InStruct.lock_count > 0;
}

void UDemoBlueprintFunctionLibrary::LockStruct(FDemoStruct& InStruct)
{
	++InStruct.lock_count;
}

void UDemoBlueprintFunctionLibrary::UnlockStruct(FDemoStruct& InStruct)
{
	if (InStruct.lock_count == 0) {
		FFrame::KismetExecutionMessage(TEXT("LockCount was zero!"), ELogVerbosity::Error);
	}
	else
	{
		--InStruct.lock_count;
	}
}
