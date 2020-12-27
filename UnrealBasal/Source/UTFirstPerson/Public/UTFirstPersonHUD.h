// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UTFirstPersonHUD.generated.h"

UCLASS()
class AUTFirstPersonHUD : public AHUD
{
	GENERATED_BODY()

public:
	AUTFirstPersonHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

