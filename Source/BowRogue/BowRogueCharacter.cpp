// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BowRogueCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Weapon.h"
#include "CrosshairTraceComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ABowRogueCharacter 

ABowRogueCharacter::ABowRogueCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(30.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(0.0f, 0.0f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	armActorComp = CreateDefaultSubobject<UChildActorComponent>("Arm Actor");
	armActorComp->SetupAttachment(Mesh1P, FName("arm_socket"));

	weaponActorComp = CreateDefaultSubobject<UChildActorComponent>("Weapon Actor");
	weaponActorComp->SetupAttachment(armActorComp);
	

	//Movement
	movementComp = GetCharacterMovement();
	movementComp->JumpZVelocity = 860.0f;
	movementComp->GravityScale = 3.0f;
	movementComp->MaxFlySpeed = 2000.0f;
	movementComp->BrakingDecelerationFlying = 2000.0f;


	//Crosshair Trace
	crossTraceComp = CreateDefaultSubobject<UCrosshairTraceComponent>("CrosshairTrace");
}

void ABowRogueCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	Mesh1P->SetHiddenInGame(false, true);
	
	weapon = Cast<AWeapon>(weaponActorComp->GetChildActor() );
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABowRogueCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABowRogueCharacter::OnFire);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ABowRogueCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABowRogueCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABowRogueCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABowRogueCharacter::LookUpAtRate);
}

void ABowRogueCharacter::OnFire(){
	
	if (weapon) {
		
		weapon->SetFocus(crossTraceComp->GetHitResult().Location);
		weapon->Fire();
	}

}


void ABowRogueCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ABowRogueCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ABowRogueCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABowRogueCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

