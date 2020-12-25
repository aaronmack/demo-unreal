// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class UNREALBASAL_API SDemoCompoundWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoCompoundWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
