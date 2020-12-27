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
	return InStruct.m_isLocked;
}

bool UDemoBlueprintFunctionLibrary::LockStruct(FDemoStruct& InStruct)
{
	InStruct.m_isLocked = true;
	return true;
}

bool UDemoBlueprintFunctionLibrary::UnlockStruct(FDemoStruct& InStruct)
{
	InStruct.m_isLocked = false;
	return true;
}
