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
	UFUNCTION()
	void OnPressedMap();
	void OnReleaseMap();

public:

	UFUNCTION()
		void OnCrosshairHitNewActor(AActor* actor);

	void CreateWidgets();

	UFUNCTION(BlueprintCallable)
	void SetUIOnlyMode(class UWidget* inWidgetToFocus = nullptr, bool bShowCursor = true);

	//if widgetToRemove is nullptr, its remove this Widget
	UFUNCTION(BlueprintCallable)
	void SetGameOnlyMode(UUserWidget* widgetToRemove = nullptr);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE class AAdvancedCharacter* GetAdvancedCharacter() const;
		 
};
