// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HAL/IConsoleManager.h"

int32 GSomeCoolDebugValue = -1;

static FAutoConsoleVariableRef CVarSomeCoolDebugValue(
	TEXT("MyGame.SomeCoolDebugValue"),
	GSomeCoolDebugValue,
	TEXT("This cool debug value controls how the foos are displayed\n")
	TEXT("  -1: Don't show any foos (default)\n")
	TEXT("   0: Show only the nearest foos\n")
	TEXT("   1: Show mid-range foos\n")
	TEXT(" >=2: Show all foos, even hidden ones"));

extern FAutoConsoleVariableRef CVarSomeCoolDebugValue1(
	TEXT("MyGame.SomeCoolDebugValue1"),
	GSomeCoolDebugValue,
	TEXT("This cool debug value controls how the foos are displayed\n")
	TEXT("  -1: Don't show any foos (default)\n")
	TEXT("   0: Show only the nearest foos\n")
	TEXT("   1: Show mid-range foos\n")
	TEXT(" >=2: Show all foos, even hidden ones"));

static FAutoConsoleCommandWithWorldAndArgs GMyCoolCommand(
	TEXT("MyGame.MyCoolCommand"),
	TEXT("Does cool things (this is the help text for the command)"),
	FConsoleCommandWithWorldAndArgsDelegate::CreateLambda([](const TArray<FString>& Args, UWorld* World)
	{
		UE_LOG(LogTemp, Log, TEXT("My cool command was passed %d args"), Args.Num());
	})
);

void UsefulBasalFunction1();
int UsefulBasalFunction2();