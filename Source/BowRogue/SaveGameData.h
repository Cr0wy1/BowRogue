// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
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
	FTransform characterTransform;
	float health;
	float stamina;
	//attributes
	//collectet
};
