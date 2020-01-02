// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"
#include "Engine/World.h"
#include "AdvancedCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"


UAttributeComponent::UAttributeComponent(){
	PrimaryComponentTick.bCanEverTick = true;

	health.name = "health"; 
	stamina.name = "stamina";

	
}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	
	character = Cast<AAdvancedCharacter>(GetOwner());

	AddAttribute(&health);
	AddAttribute(&stamina);
	AddAttribute(&walkSpeed);


	PrintDebug();
	
	//UpdateAttributes();
}

void UAttributeComponent::EndPlay(const EEndPlayReason::Type EndPlayReason){
	//Clear attribute pointers


	Super::EndPlay(EndPlayReason);
}



// Called every frame
void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Warning, TEXT("UAttributeComponent: tick"));


	if (stamina.regAmount > 0.0f) {
		
		if (stamina.lastRegTime + stamina.regSpeed < GetWorld()->GetTimeSeconds()) {
			//OnStaminaChange.Broadcast(stamina);
			stamina += stamina.regAmount;
			stamina.lastRegTime = GetWorld()->GetTimeSeconds();
		}
	}
}

void UAttributeComponent::ApplyDamage(float amount){
	health -= amount; 
	//OnHealthUpdate.Broadcast(health, amount);
	if (health <= 0.0f) { 
		OnDeath.Broadcast();
	}
}

void UAttributeComponent::AddHealth(float value){
	UE_LOG(LogTemp, Warning, TEXT("AttrComp: AddHealth %f"), value);

	health.value += value;
	//OnHealthChange.Broadcast(); 
}

void UAttributeComponent::AddHealthMax(float value){
	health.max += value;
	//OnHealthChange.Broadcast(health);
}

void UAttributeComponent::AddStamina(float value){
	
	stamina.value += value;
	//OnStaminaChange.Broadcast(stamina);
}

void UAttributeComponent::AddStaminaMax(float value){
	stamina.max += value;
	//OnStaminaChange.Broadcast(stamina);
}

void UAttributeComponent::AddAttribute(FAttribute* attribute){
	if (attribute) {
		attributes.Add(attribute);
	}
	
}

void UAttributeComponent::OnAttributeUpdate(FAttribute * updatedAttribute){

}


void UAttributeComponent::UpdateAttributes(){
	if (character) {
		UCharacterMovementComponent* movementComp = character->GetCharacterMovement();

		movementComp->MaxWalkSpeed = walkSpeed.value * walkSpeedMultiplier.value;
		character->GetCapsuleComponent()->SetRelativeScale3D(FVector(sizeMultiplier.value));
		movementComp->JumpZVelocity = jumpHeight.value;
	}
}



//Debug
void UAttributeComponent::PrintDebug(){
	UE_LOG(LogTemp, Warning, TEXT("Attributes: "));
	for (FAttribute* elem : attributes){
		UE_LOG(LogTemp, Warning, TEXT("%s: %f/%f"), *elem->name.ToString(), elem->value, elem->max);
	}
}


