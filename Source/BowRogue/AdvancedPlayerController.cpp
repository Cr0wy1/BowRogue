// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedPlayerController.h"
#include "AdvancedGameInstance.h"
#include "AdvancedCharacter.h"
#include "CrosshairTraceComponent.h"
#include "Pickup.h"
#include "WidgetAsset.h"
#include "MapWidget.h"
#include "DungeonGenerator.h"
#include "PlayerHUDWidget.h"

void AAdvancedPlayerController::BeginPlay() {
	Super::BeginPlay();

	character = Cast<AAdvancedCharacter>(GetCharacter());
	if (character) {
		UE_LOG(LogTemp, Warning, TEXT("character exists"));

		character->GetCrosshairTraceComp()->OnHitNewActor.AddDynamic(this, &AAdvancedPlayerController::OnCrosshairHitNewActor);
	}

	gameInstance = GetGameInstance<UAdvancedGameInstance>();
	ADungeonGenerator* dungeonGenerator = gameInstance->GetDungeonGenerator();
	UWidgetAsset* widgetAsset_A = gameInstance->GetWidgetAsset();

	//Create Widgets
	mapWidget = CreateAddViewport<UMapWidget>(this, widgetAsset_A->mapWidget_BP);
	if (mapWidget && dungeonGenerator) {
		mapWidget->Update(dungeonGenerator->GetGridPtr());
	}
	
	playerHUDWidget = CreateAddViewport<UPlayerHUDWidget>(this, widgetAsset_A->playerHUDWidget_BP);
}

void AAdvancedPlayerController::SetupInputComponent(){

	Super::SetupInputComponent();

	InputComponent->BindAction("Map", IE_Pressed, this, &AAdvancedPlayerController::OnPressedMap);
	InputComponent->BindAction("Map", IE_Released, this, &AAdvancedPlayerController::OnReleaseMap);

}

void AAdvancedPlayerController::OnCrosshairHitNewActor(AActor * actor){
	UE_LOG(LogTemp, Warning, TEXT("Hit New Actor: %s"), *actor->GetName());
	if (!playerHUDWidget) return;

	APickup* pickup = Cast<APickup>(actor);
	if (pickup) {
		playerHUDWidget->SetInteractText(true);
	}
	else {
		playerHUDWidget->SetInteractText(false);
	}
}

void AAdvancedPlayerController::OnPressedMap(){
	if (mapWidget) {
		mapWidget->OpenMap();
	}
}

void AAdvancedPlayerController::OnReleaseMap(){
	if (mapWidget) {
		mapWidget->CloseMap();
	}
}
