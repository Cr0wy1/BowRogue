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

protected:

	
	AWeapon* weapon = nullptr;

	//COMPONENTS
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Arm Actor")
	UChildActorComponent* armActorComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Arm Actor")
	UChildActorComponent* weaponActorComp;

	virtual void BeginPlay();


protected:
	
	/** Fires a projectile. */
	void OnFire();
	void OnInteraction();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface


public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFPCameraComp() const { return fpCameraComp; }

};

