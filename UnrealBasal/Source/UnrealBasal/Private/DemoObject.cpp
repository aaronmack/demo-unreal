// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoObject.h"

bool UDemoObject::UDOPyUsefulFunction(const int32 InValue) {
	UE_LOG(LogTemp, Log, TEXT("DemoObject: %d"), TestVar1);
	return true;
}