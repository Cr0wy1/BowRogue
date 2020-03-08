// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStructs.h"
#include "ItemObject.generated.h"



class ABowRogueCharacter;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BOWROGUE_API UItemObject : public UObject{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly)
	FItemData itemData;


public:

	UFUNCTION(BlueprintImplementableEvent)
	void OnAddItem(ABowRogueCharacter* bowCharacter);

	UFUNCTION(BlueprintImplementableEvent)
	void OnRemoveItem();

	static UItemObject* Construct(UObject* owner, FItemData _itemData);
};
