// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StructureAsset.generated.h"

/**
 * 
 */
UCLASS()
class BOWROGUE_API UStructureAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	TSubclassOf<AActor> bossPortal_BP;
};
