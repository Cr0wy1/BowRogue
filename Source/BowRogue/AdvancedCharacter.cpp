// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CrosshairTraceComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AAdvancedCharacter::AAdvancedCharacter(){

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(30.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	fpCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	fpCameraComp->SetupAttachment(GetCapsuleComponent());
	fpCameraComp->RelativeLocation = FVector(0.0f, 0.0f, 64.f); // Position the camera
	fpCameraComp->bUsePawnControlRotation = true;

	//Movement
	movementComp = GetCharacterMovement();
	movementComp->JumpZVelocity = 860.0f;
	movementComp->GravityScale = 3.0f;
	movementComp->MaxFlySpeed = 2000.0f;
	movementComp->BrakingDecelerationFlying = 2000.0f;

	//Crosshair Trace
	crossTraceComp = CreateDefaultSubobject<UCrosshairTraceComponent>("CrosshairTrace");
	crosshairResult = crossTraceComp->GetCrosshairResultPtr();
}

// Called when the game starts or when spawned
void AAdvancedCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AAdvancedCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAdvancedCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

