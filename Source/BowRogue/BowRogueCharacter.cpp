// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BowRogueCharacter.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Weapon.h"
#include "Pickup.h"
#include "CrosshairTraceComponent.h"


ABowRogueCharacter::ABowRogueCharacter(){

	armActorComp = CreateDefaultSubobject<UChildActorComponent>("Arm Actor");
	armActorComp->SetupAttachment(meshFP, FName("arm_socket"));

	weaponActorComp = CreateDefaultSubobject<UChildActorComponent>("Weapon Actor");
	weaponActorComp->SetupAttachment(armActorComp);
	
}

void ABowRogueCharacter::BeginPlay(){
	Super::BeginPlay();

	weapon = Cast<AWeapon>(weaponActorComp->GetChildActor() );
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABowRogueCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent){

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind fire event
	PlayerInputComponent->BindAction("Primary", IE_Pressed, this, &ABowRogueCharacter::PrimaryPressed);
	PlayerInputComponent->BindAction("Primary", IE_Released, this, &ABowRogueCharacter::PrimaryReleased);

}

void ABowRogueCharacter::OnPickupTake(FItemData * itemData){
	weapon->AttachItem(itemData);
}

void ABowRogueCharacter::PrimaryPressed(){
	
	if (weapon) {
		weapon->StartShooting(crosshairResult);
	}

}

void ABowRogueCharacter::PrimaryReleased(){
	if (weapon) {
		weapon->StopShooting();
	}
}


