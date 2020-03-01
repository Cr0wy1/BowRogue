// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameStructs.h"
#include "SaveGameData.generated.h"

/**
 * 
 */
UCLASS()
class BOWROGUE_API USaveGameData : public USaveGame{
	GENERATED_BODY()
	
public:

	//Absolute SaveGame


	//Save for current Run
	bool bIsInRun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform characterTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttribute health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDynamicAttribute stamina;
	//attributes
	//collectet


	UFUNCTION(BlueprintCallable, meta = (WorldContext = "worldContextObject"))
	void SaveAll(const UObject* worldContextObject);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "worldContextObject"))
	void LoadAll(const UObject* worldContextObject);
};
