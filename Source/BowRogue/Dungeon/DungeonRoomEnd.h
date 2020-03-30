// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonRoom.h"
#include "DungeonRoomEnd.generated.h"



class APortalPlatform;
/**
 * 
 */
UCLASS()
class BOWROGUE_API ADungeonRoomEnd : public ADungeonRoom
{
	GENERATED_BODY()
	
protected:

	APortalPlatform * portal;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APortalPlatform> portalBP;

	virtual void BeginPlay() override;

	void SetupPortal();

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE APortalPlatform* GetPortal() { return portal; }
};
