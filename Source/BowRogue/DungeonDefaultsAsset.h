// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DungeonDefaultsAsset.generated.h"



class ADungeonRoom;
class ADungeonRoomEnd;
/**
 * 
 */
UCLASS()
class BOWROGUE_API UDungeonDefaultsAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DungeonDefaults")
	TSubclassOf<ADungeonRoom> roomDefault;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DungeonDefaults")
	TSubclassOf<ADungeonRoomEnd> roomEndDefault;

};
