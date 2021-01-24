// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "QuestManager.h"
#include "QuestMarker.generated.h"

UCLASS()
class UNREALBASAL_API AQuestMarker : public AActor
{
	GENERATED_BODY()

private:
	UFUNCTION()
	void QuestUpdated(int32 Index);

public:	
	// Sets default values for this actor's properties
	AQuestMarker();

	UFUNCTION(BlueprintCallable)
	void RefreshVisibility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintPure, BlueprintImplementableEvent)
	AQuestManager* GetQuestManager() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* ParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ShowAtProgress = 0;
};
