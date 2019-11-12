// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//stamina = FAttribute();
}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Warning, TEXT("UAttributeComponent: tick"));


	//if (stamina.regAmount > 0.0f) {
		
		//if (stamina.lastRegTime + stamina.regSpeed < GetWorld()->GetTimeSeconds()) {
			//int32 num = OnAttrChange.GetAllObjects().Num();
			//UE_LOG(LogTemp, Warning, TEXT("stamina: %f delegate num: %i"), stamina.value, num);
			//OnAttrChange.Broadcast();
			//stamina += stamina.regAmount;
			//stamina.lastRegTime = GetWorld()->GetTimeSeconds();
		//}
	//}
}

void UAttributeComponent::ApplyDamage(float amount){
	health -= amount;
	//OnHealthUpdate.Broadcast(health, amount);
	if (health <= 0.0f) {
		OnDeath.Broadcast();
	}
}

