// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameData.h"
#include "Kismet/GameplayStatics.h"
#include "FunctionLibrary\AdvancedFunctionLibrary.h"
#include "Player/AdvancedCharacter.h"
#include "Components/HealthComponent.h"

void USaveGameData::SaveAll(const UObject* worldContextObject){

	AAdvancedCharacter* character = UAdvancedFunctionLibrary::GetAdvancedCharacter(worldContextObject);

	if (character) {
		characterTransform = character->GetTransform();
		health = character->GetHealthComp()->GetHealth();
		stamina = character->GetHealthComp()->GetStamina();
	}


	UGameplayStatics::SaveGameToSlot(this, "test", 0);
}

void USaveGameData::LoadAll(const UObject* worldContextObject){
	AAdvancedCharacter* character = UAdvancedFunctionLibrary::GetAdvancedCharacter(worldContextObject);

	if (character) {
		character->SetActorTransform(characterTransform);
		character->GetHealthComp()->SetHealth(health);
		character->GetHealthComp()->SetStamina(stamina);
	}

}
