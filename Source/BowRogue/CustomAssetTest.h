// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CustomAssetTest.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, hidecategories = Object)
class BOWROGUE_API UCustomAssetTest : public UObject{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TextAsset")
	FText text;  

	
};
 