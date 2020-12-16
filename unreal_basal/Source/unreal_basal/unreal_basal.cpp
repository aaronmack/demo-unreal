// Fill out your copyright notice in the Description page of Project Settings.

#include "unreal_basal.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, unreal_basal, "unreal_basal" );

void UsefulBasalFunction1() {

}

int UsefulBasalFunction2() {
	UE_LOG(LogTemp, Log, TEXT("UsefulBasalFunction2: %d"), 2);
	return 2;
}