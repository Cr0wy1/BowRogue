// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AdvancedCharacter.h"
#include "Player/AdvancedPlayerController.h"
#include "AdvancedGameInstance.h"
#include "UserWidget.h"



UWidget * UAdvancedFunctionLibrary::CreateAddViewport(APlayerController * ownerController, TSubclassOf<UUserWidget> widgetClass) {
	UUserWidget* createdWidget = CreateWidget(ownerController, widgetClass);
	createdWidget->AddToViewport();
	return createdWidget;
} 

UAdvancedGameInstance* UAdvancedFunctionLibrary::GetAdvancedGameInstance(const UObject* worldContextObject) {
	return Cast<UAdvancedGameInstance>(UGameplayStatics::GetGameInstance(worldContextObject));
}

AAdvancedCharacter* UAdvancedFunctionLibrary::GetAdvancedCharacter(const UObject* worldContextObject, int32 playerIndex) {
	return Cast<AAdvancedCharacter>(UGameplayStatics::GetPlayerCharacter(worldContextObject, 0));
}

AAdvancedPlayerController * UAdvancedFunctionLibrary::GetAdvancedPlayerController(const UObject* worldContextObject, int32 playerIndex) {
	return Cast<AAdvancedPlayerController>(UGameplayStatics::GetPlayerController(worldContextObject, 0));
}  