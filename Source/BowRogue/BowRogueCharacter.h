// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedCharacter.h"
#include "BowRogueCharacter.generated.h"



class UInputComponent;
class AWeapon;



UCLASS(config=Game)
class ABowRogueCharacter : public AAdvancedCharacter
{
	GENERATED_BODY()

		 

public:
	ABowRogueCharacter();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE AWeapon* GetWeapon() const { return weapon; }

protected:

	
	AWeapon* weapon = nullptr;

	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Arm Actor")
	UChildActorComponent* armActorComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Arm Actor")
	UChildActorComponent* weaponActorComp;

	virtual void BeginPlay();


protected:
	
	virtual void OnPickupTake(FItemData* itemData) override;

	/** Fires a projectile. */
	void PrimaryPressed();
	void PrimaryReleased();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

};

