// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedPlayerController.h"
#include "AdvancedGameInstance.h"
#include "Player/AdvancedCharacter.h"
#include "Components/CrosshairTraceComponent.h"
#include "Actors/Pickup.h"
#include "Assets/WidgetAsset.h"
#include "Widgets/MapWidget.h"
#include "Widgets/PlayerHUDWidget.h"
#include "Components/AttributeComponent.h"

void AAdvancedPlayerController::BeginPlay() {
	Super::BeginPlay();

	character = GetAdvancedCharacter();
	//ensureMsgf(character, TEXT("character is nullptr"));

	if (character) {
		UE_LOG(LogTemp, Warning, TEXT("character exists"));
		if (character->GetCrosshairTraceComp()) {
			UE_LOG(LogTemp, Warning, TEXT("GetCrosshairTraceComp exists"));
		}
		character->GetCrosshairTraceComp()->OnHitNewActor.AddDynamic(this, &AAdvancedPlayerController::OnCrosshairHitNewActor);
	}

}

void AAdvancedPlayerController::SetupInputComponent(){

	Super::SetupInputComponent();

	InputComponent->BindAction("Map", IE_Pressed, this, &AAdvancedPlayerController::OnPressedMap); 
	InputComponent->BindAction("Map", IE_Released, this, &AAdvancedPlayerController::OnReleaseMap);

}

void AAdvancedPlayerController::OnCrosshairHitNewActor(AActor * actor){
	//UE_LOG(LogTemp, Warning, TEXT("Hit New Actor: %s"), *actor->GetName());
	if (!playerHUDWidget) return;

	APickup* pickup = Cast<APickup>(actor);
	if (pickup) {
		playerHUDWidget->SetInteractText(true);
	}
	else {
		playerHUDWidget->SetInteractText(false);
	}
}

void AAdvancedPlayerController::CreateWidgets(){
	UAdvancedGameInstance* gameInstance = GetGameInstance<UAdvancedGameInstance>();
	//ADungeonGenerator* dungeonGenerator = gameInstance->GetDungeonGenerator();
	UWidgetAsset* widgetAsset_A = gameInstance->GetWidgetAsset();

	//Create Widgets
	mapWidget = CreateAddViewport<UMapWidget>(this, widgetAsset_A->mapWidget_BP);
	//if (mapWidget && dungeonGenerator) {
		//mapWidget->Update(dungeonGenerator->GetGridPtr());
	//}

	//playerHUDWidget = CreateAddViewport<UPlayerHUDWidget>(this, widgetAsset_A->playerHUDWidget_BP);

	//if (playerHUDWidget && character && character->GetAttrComp()) {
		//playerHUDWidget->Init(character->GetAttrComp());
	//}
}

AAdvancedCharacter * AAdvancedPlayerController::GetAdvancedCharacter() const{
	return Cast<AAdvancedCharacter>(GetCharacter());
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

void AAdvancedPlayerController::SetUIOnlyMode(UWidget* inWidgetToFocus, bool bShowCursor) {
	FInputModeUIOnly inputMode;

	if (inWidgetToFocus) {
		inputMode.SetWidgetToFocus(inWidgetToFocus->TakeWidget());
	}

	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	SetInputMode(inputMode);
	bShowMouseCursor = bShowCursor;
}


void AAdvancedPlayerController::SetGameOnlyMode(UUserWidget* widgetToRemove) {
	FInputModeGameOnly inputMode;

	if (widgetToRemove) {
		widgetToRemove->RemoveFromParent();
	}

	SetInputMode(inputMode);
	bShowMouseCursor = false;
}

