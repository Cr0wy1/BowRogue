// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AdvancedPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BOWROGUE_API AAdvancedPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	class AAdvancedCharacter* character = nullptr;
	class UAdvancedGameInstance * gameInstance = nullptr;

	//Widgets
	class UMapWidget* mapWidget = nullptr;
	class UPlayerHUDWidget* playerHUDWidget = nullptr;

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;



	//Key Events
	void OnPressedMap();
	void OnReleaseMap();

public:

	UFUNCTION()
		void OnCrosshairHitNewActor(AActor* actor);
};
