// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"
#include "Engine/World.h"
#include "Player/AdvancedCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"


void FAttributeField::NotifyAttribute() {
	if (attributeObject) {
		attributeObject->AfterFieldsChanged();
	}
}

void FAttributeField::Init(UAttributeObject * _attributeObject, float _value) {
	attributeObject = _attributeObject;
	value = _value;
}


UAttributeComponent::UAttributeComponent(){
	PrimaryComponentTick.bCanEverTick = true;

	//health = FDynamicAttribute(this, "Healht001", 0, 100, 200);

	health = UAttributeObject::CreateAttribute(this, "Health", 0.0f, 100.0f, 100.0f);
	stamina = UAttributeObject::CreateAttribute(this, "Stamina", 0.0f, 100.0f, 100.0f);
}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	health->Init(healthInit);
	
	character = Cast<AAdvancedCharacter>(GetOwner());

	attributes.Reset(); 
	 
	AddAttribute(health);
	AddAttribute(stamina); 

	//UE_LOG(LogTemp, Warning, TEXT("AttributeComp %s Start Player Health: %s"), *GetName(), *health->ToString());

	//PrintDebug();

	//UpdateAttributes();
}

void UAttributeComponent::EndPlay(const EEndPlayReason::Type EndPlayReason){
	//Clear attribute pointers
	 
	//UE_LOG(LogTemp, Warning, TEXT("End Player Health: %s"), *health->ToString());
	Super::EndPlay(EndPlayReason);
}



// Called every frame
void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Warning, TEXT("UAttributeComponent: tick"));

	//UE_LOG(LogTemp, Warning, TEXT("Tick Player Health: %s"), *health.ToString());
	//if (stamina.regAmount > 0.0f) {
		
		//if (stamina.lastRegTime + stamina.regSpeed < GetWorld()->GetTimeSeconds()) {
			//OnStaminaChange.Broadcast(stamina);
			//stamina += stamina.regAmount;
			//stamina.lastRegTime = GetWorld()->GetTimeSeconds();
		//}
	//}
}


void UAttributeComponent::AddAttribute(UAttributeObject* attribute){
	if (attribute) {
		attributes.Add(attribute);
	}
	
}

void UAttributeComponent::OnAttributeUpdate(FAttribute * updatedAttribute){
	UE_LOG(LogTemp, Warning, TEXT("on Attribute update Health: %s"), *health->ToString());
	OnAttrChange.Broadcast();
}


void UAttributeComponent::UpdateAttributes(){
	if (character) {
		UCharacterMovementComponent* movementComp = character->GetCharacterMovement();

		//movementComp->MaxWalkSpeed = walkSpeed.value * walkSpeedMultiplier.value;
		//character->GetCapsuleComponent()->SetRelativeScale3D(FVector(sizeMultiplier.value));
		//movementComp->JumpZVelocity = jumpHeight.value;
	}
}



//Debug
void UAttributeComponent::PrintDebug(){
	UE_LOG(LogTemp, Warning, TEXT("Attributes: "));
	for (UAttributeObject* elem : attributes){
		//UE_LOG(LogTemp, Warning, TEXT("%s: %f/%f"), *elem->name.ToString(), elem->value, elem->max);
	}
}


