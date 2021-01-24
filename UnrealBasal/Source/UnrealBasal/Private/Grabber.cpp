// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("Grabber Constructor"));
}


void UGrabber::Grab()
{
	AActor* HitActor;
	UPrimitiveComponent* HitComponent;
	if (TraceForPhysicsBodies(HitActor, HitComponent))
	{
		HitComponent->SetSimulatePhysics(true);
		GetPhysicsComponent()->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitComponent->GetCenterOfMass(),
			FRotator()
		);
		NotifyQuestActor(HitActor);
	}
	UE_LOG(LogTemp, Warning, TEXT("Grabber Grab"));
}

void UGrabber::Release()
{
	GetPhysicsComponent()->ReleaseComponent();
	UE_LOG(LogTemp, Warning, TEXT("Grabber Release"));
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber BeginPlay"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// UE_LOG(LogTemp, Warning, TEXT("Grabber TickComponent"));
}

FVector UGrabber::GetMaxGrabLocation() const
{
	return GetComponentLocation() + UKismetMathLibrary::GetForwardVector(GetComponentRotation()) * MaxGrabDistance;
}

FVector UGrabber::GetHoldLocation() const
{
	return GetComponentLocation() + UKismetMathLibrary::GetForwardVector(GetComponentRotation()) * HoldDistance;
}

UPhysicsHandleComponent* UGrabber::GetPhysicsComponent() const
{
	return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

bool UGrabber::TraceForPhysicsBodies_Implementation(AActor *& HitActor, UPrimitiveComponent *& HitComponent)
{
	return false;
}