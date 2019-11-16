// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"
#include "Engine/World.h"

UAttributeComponent::UAttributeComponent(){
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Warning, TEXT("UAttributeComponent: tick"));


	if (stamina.regAmount > 0.0f) {
		
		if (stamina.lastRegTime + stamina.regSpeed < GetWorld()->GetTimeSeconds()) {
			int32 num = OnStaminaChange.GetAllObjects().Num();
			UE_LOG(LogTemp, Warning, TEXT("stamina: %f delegate num: %i"), stamina.value, num);
			OnStaminaChange.Broadcast(stamina);
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

