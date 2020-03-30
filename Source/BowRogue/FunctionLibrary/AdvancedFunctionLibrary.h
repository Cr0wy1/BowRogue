// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AdvancedFunctionLibrary.generated.h"



class AAdvancedCharacter;
class AAdvancedPlayerController;
class UAdvancedGameInstance;
class UWidget;
class UUserWidget;
/**
 * 
 */
UCLASS()
class BOWROGUE_API UAdvancedFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	 
public:


	UFUNCTION(BlueprintCallable, Category = "AdvancedLibrary", meta = (DeterminesOutputType = "widgetClass"))
	static UWidget* CreateAddViewport(APlayerController* ownerController, TSubclassOf<UUserWidget> widgetClass);

	UFUNCTION(BlueprintPure, Category = "AdvancedLibrary", meta = (WorldContext = "worldContextObject", UnsafeDuringActorConstruction = "true"))
	static UAdvancedGameInstance* GetAdvancedGameInstance(const UObject* worldContextObject);

	UFUNCTION(BlueprintPure, Category = "AdvancedLibrary", meta = (WorldContext = "worldContextObject", UnsafeDuringActorConstruction = "true"))
	static AAdvancedCharacter* GetAdvancedCharacter(const UObject* worldContextObject, int32 playerIndex = 0);

	UFUNCTION(BlueprintPure, Category = "AdvancedLibrary", meta = (WorldContext = "worldContextObject", UnsafeDuringActorConstruction = "true"))
	static AAdvancedPlayerController* GetAdvancedPlayerController(const UObject* worldContextObject, int32 playerIndex = 0);

};
