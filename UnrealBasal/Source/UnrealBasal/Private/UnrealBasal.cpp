// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealBasal.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, UnrealBasal, "UnrealBasal" );

void UnrealBasalUsefulFunction1() {

}

int UnrealBasalUsefulFunction2() {
	UE_LOG(LogTemp, Log, TEXT("UnrealBasalUsefulFunction2: %d"), 2);
	return 2;
}