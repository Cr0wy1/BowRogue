// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManagerComponent.h"
#include "AdvancedCharacter.h"
#include "HealthComponent.h"

// Sets default values for this component's properties
UItemManagerComponent::UItemManagerComponent(){
	PrimaryComponentTick.bCanEverTick = true;


}


// Called when the game starts
void UItemManagerComponent::BeginPlay(){
	Super::BeginPlay();

	advCharacter = Cast<AAdvancedCharacter>(GetOwner());

	collectedItems.Reset();
}


// Called every frame
void UItemManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UItemManagerComponent::AddItem(FItemData * itemData){
	if (itemData) {
		if (itemData->characterUpdate.attributeUpdates.Num() > 0) {
			for (auto attributeUpdate : itemData->characterUpdate.attributeUpdates) {
				if (attributeUpdate.type == EAttributeType::HEALTH) {
					advCharacter->healthComp->UpdateHealth(attributeUpdate);
				}
				else if (attributeUpdate.type == EAttributeType::STAMINA) {
					advCharacter->healthComp->UpdateStamina(attributeUpdate);
				}
			}
		}

		collectedItems.Add(itemData);
	}
}

