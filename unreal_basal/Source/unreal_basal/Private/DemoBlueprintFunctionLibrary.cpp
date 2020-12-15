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