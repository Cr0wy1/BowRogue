// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManagerComponent.h"
#include "BowRogueCharacter.h"
#include "HealthComponent.h"
#include "Bow.h"
#include "Arrow.h"

// Sets default values for this component's properties
UItemManagerComponent::UItemManagerComponent(){
	PrimaryComponentTick.bCanEverTick = true;


}


// Called when the game starts
void UItemManagerComponent::BeginPlay(){
	Super::BeginPlay();

	bowCharacter = Cast<ABowRogueCharacter>(GetOwner());

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
					bowCharacter->healthComp->UpdateHealth(attributeUpdate);
				}
				else if (attributeUpdate.type == EAttributeType::STAMINA) {
					bowCharacter->healthComp->UpdateStamina(attributeUpdate);
				}

				
			}
		}

		bowCharacter->GetWeapon()->UpdateWeapon(itemData->weaponUpdate);

		AArrow* arrowTemplate = Cast<AArrow>(bowCharacter->GetWeapon()->GetProjectileTemplate());
		if (arrowTemplate) {
			arrowTemplate->UpdateArrow(itemData->arrowUpdate);
			arrowTemplate->UpdateProjectile(itemData->projectileUpdate);
		}

		collectedItems.Add(itemData);
	}
}

