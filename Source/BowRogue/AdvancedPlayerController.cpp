// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedPlayerController.h"
#include "AdvancedGameInstance.h"
#include "WidgetAsset.h"
#include "MapWidget.h"
#include "DungeonGenerator.h"

void AAdvancedPlayerController::BeginPlay() {
	Super::BeginPlay();

	gameInstance = GetGameInstance<UAdvancedGameInstance>();
	ADungeonGenerator* dungeonGenerator = gameInstance->GetDungeonGenerator();
	UWidgetAsset* widgetAsset_A = gameInstance->GetWidgetAsset();
	
	if (widgetAsset_A->mapWidget_BP) {
		mapWidget = CreateWidget<UMapWidget>(this, widgetAsset_A->mapWidget_BP);
		mapWidget->AddToPlayerScreen();

		if (dungeonGenerator) {
			mapWidget->Update(dungeonGenerator->GetGridPtr());
		}
	}
}

void AAdvancedPlayerController::SetupInputComponent(){

	Super::SetupInputComponent();

	InputComponent->BindAction("Map", IE_Pressed, this, &AAdvancedPlayerController::OnPressedMap);
	InputComponent->BindAction("Map", IE_Released, this, &AAdvancedPlayerController::OnReleaseMap);

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
