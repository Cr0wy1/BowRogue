// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"
#include "Engine/World.h"


UAttributeComponent::UAttributeComponent(){
	PrimaryComponentTick.bCanEverTick = true;

	health.name = "health";
	stamina.name = "stamina";
}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	
	attributesLookup.Add(health.name, &health);
	attributesLookup.Add(stamina.name, &stamina);

	int32 numAttributs = attributes.Num();
	for (int32 i = 0; i < numAttributs; i++){
		AddAttribute(attributes[i]);
	}
}

void UAttributeComponent::EndPlay(const EEndPlayReason::Type EndPlayReason){
	//Clear attribute pointers
	for (auto attr : attributesLookup) {
		if (attr.Value->name == "health" || attr.Value->name == "stamina") continue;
		delete attr.Value;
		attr.Value = nullptr;
	}
	attributesLookup.Reset();

	Super::EndPlay(EndPlayReason);
}



// Called every frame
void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Warning, TEXT("UAttributeComponent: tick"));


	if (stamina.regAmount > 0.0f) {
		
		if (stamina.lastRegTime + stamina.regSpeed < GetWorld()->GetTimeSeconds()) {
			int32 num = OnStaminaChange.GetAllObjects().Num();
			//UE_LOG(LogTemp, Warning, TEXT("stamina: %f delegate num: %i"), stamina.value, num);
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

void UAttributeComponent::AddHealth(float value){
	UE_LOG(LogTemp, Warning, TEXT("AttrComp: AddHealth %f"), value);

	health.value += value;
	OnHealthChange.Broadcast(health);
}

void UAttributeComponent::AddHealthMax(float value){
	health.max += value;
	OnHealthChange.Broadcast(health);
}

void UAttributeComponent::AddStamina(float value){
	
	stamina.value += value;
	OnStaminaChange.Broadcast(stamina);
}

void UAttributeComponent::AddStaminaMax(float value){
	stamina.max += value;
	OnStaminaChange.Broadcast(stamina);
}

const FAttribute* UAttributeComponent::AddAttribute(FAttribute attribute){
	if (DoesAttributeExist(attribute.name)) {
		UE_LOG(LogTemp, Warning, TEXT("AddAttribute: attribute %s already exist"), *attribute.name.ToString());
		return nullptr;
	}

	attributes.Add(attribute);
	return attributesLookup.Add( attribute.name, new FAttribute(attribute));
}

bool UAttributeComponent::UpdateAttribute(const FAttribute &attribute){
	UE_LOG(LogTemp, Warning, TEXT("health update 1"));
	if (attribute.name == "health") {
		UE_LOG(LogTemp, Warning, TEXT("health update 2"));

		health.value += attribute.value;
		health.max += attribute.max;
		OnHealthChange.Broadcast(health);
		return true;
	}
	
	FAttribute** findAttr = attributesLookup.Find(attribute.name);
	if (findAttr) {
		**findAttr += attribute;
		return true;
	}
	

	return false;
}

bool UAttributeComponent::DoesAttributeExist(FName name){
	return attributesLookup.Find(name);
}

const FAttribute* UAttributeComponent::GetAttribute(FName name){
	FAttribute** findAttr = attributesLookup.Find(name);
	return findAttr ? *findAttr : nullptr;
}


