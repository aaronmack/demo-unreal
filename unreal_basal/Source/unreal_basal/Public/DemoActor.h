// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DemoActor.generated.h"

void DemoActorUsefulFunction1();

UCLASS()
class UNREAL_BASAL_API ADemoActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADemoActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DemoActor")
		float FloatSpeed = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DemoActor")
		float RotationSpeed = 20.0f;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisualMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
