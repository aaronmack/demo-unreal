// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoFirstPersonCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ADemoFirstPersonCharacter::ADemoFirstPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADemoFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADemoFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADemoFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("DemoForward"), this, &ADemoFirstPersonCharacter::DemoForward);
	PlayerInputComponent->BindAction(TEXT("DemoJump"), EInputEvent::IE_Pressed, this, &ADemoFirstPersonCharacter::DemoJump);
	PlayerInputComponent->BindAction(TEXT("DemoGrab"), EInputEvent::IE_Pressed, this, &ADemoFirstPersonCharacter::DemoGrab);
	PlayerInputComponent->BindAction(TEXT("DemoRelease"), EInputEvent::IE_Pressed, this, &ADemoFirstPersonCharacter::DemoRelease);

}

void ADemoFirstPersonCharacter::DemoForward(float AxisValue)
{
	// UE_LOG(LogTemp, Warning, TEXT("ADemoFirstPersonCharacter DemoForward %f"), AxisValue);
	GetCharacterMovement()->AddInputVector(GetActorForwardVector() * AxisValue);
}

void ADemoFirstPersonCharacter::DemoJump()
{
	UE_LOG(LogTemp, Warning, TEXT("ADemoFirstPersonCharacter DemoJump"));
	ADemoFirstPersonCharacter::Jump();
}

void ADemoFirstPersonCharacter::DemoGrab()
{
	UE_LOG(LogTemp, Warning, TEXT("ADemoFirstPersonCharacter DemoGrab"));
	GetGrabber()->Grab();
}

void ADemoFirstPersonCharacter::DemoRelease()
{
	UE_LOG(LogTemp, Warning, TEXT("ADemoFirstPersonCharacter DemoRelease"));
	GetGrabber()->Release();
}

