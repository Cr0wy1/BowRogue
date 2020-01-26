// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent(){
	PrimaryComponentTick.bCanEverTick = true;

	health.SetName("Health");
	stamina.SetName("Stamina");
}


// Called when the game starts
void UHealthComponent::BeginPlay(){
	Super::BeginPlay();

}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (stamina.regAmount > 0.0f) {
		if (stamina.lastRegTime + stamina.regSpeed < GetWorld()->GetTimeSeconds()) {
			stamina.value += stamina.regAmount;
			stamina.ClampValue();
			stamina.lastRegTime = GetWorld()->GetTimeSeconds();
		}
	}
}

void UHealthComponent::UpdateHealth(const FPlayerAttributeUpdate & attributeUpdate){
	health.min += attributeUpdate.min;
	health.value += attributeUpdate.value;
	health.max += attributeUpdate.max;
	health.ClampValue();
}

void UHealthComponent::UpdateStamina(const FPlayerAttributeUpdate & attributeUpdate){
	stamina.min += attributeUpdate.min;
	stamina.value += attributeUpdate.value;
	stamina.max += attributeUpdate.max;
	stamina.ClampValue();
}

void UHealthComponent::ApplyDamage(float damageAmount){
	health.value -= damageAmount;
	health.ClampValue();
}

void UHealthComponent::ConsumeStamina(float amount){
	stamina.value -= amount;
	stamina.ClampValue();
}

