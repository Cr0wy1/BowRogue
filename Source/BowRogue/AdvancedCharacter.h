// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameStructs.h"
#include "AdvancedCharacter.generated.h"



class AAdvancedPlayerController;
class UCrosshairTraceComponent;
class UAttributeComponent;
struct FCrosshairResult;



UCLASS()
class BOWROGUE_API AAdvancedCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	const FCrosshairResult* crosshairResult = nullptr;

	//UPROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float walkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float sprintSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float sprintStaminaConsume = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float crouchWalkSwitchSpeed = 10.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera") 
	float BaseTurnRate; /** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpRate; /** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */

	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* fpCameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CrosshairTrace")
	UCrosshairTraceComponent* crossTraceComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	UAttributeComponent* attrComp;

	// Sets default values for this character's properties
	AAdvancedCharacter();

protected:

	bool bIsSprinting = false;


	AAdvancedPlayerController* controllerAdv = nullptr;
	UCharacterMovementComponent * movementComp = nullptr;

	float capsuleBaseHeight;
	FVector cameraBaseLocation;
	float cRelativeCameraZOffset;
	FCollisionShape standingCapsuleShape;

	//COMPONENTS
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* meshFP;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnPickupTake(FItemData* itemData);

	void OnInteraction();
	void ActivateSprint();
	void DeactivateSprint();

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

	void AdjustCameraToCapsuleHeight(float deltaSeconds);

	UFUNCTION()
	void OnMovementUpdate(float DeltaSeconds, FVector OldLocation, FVector OldVelocity);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//On Take Damage Event
	UFUNCTION()
	virtual void ReceiveDamageAny(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FVector GetGroundLocation() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float TraceGroundDistance() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool OverlapStandingCheck() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void StartJump();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void StopJump();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void StartCrouch();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void StopCrouch();
	
	FORCEINLINE AAdvancedPlayerController* GetController() const { return controllerAdv; }
	FORCEINLINE class UCrosshairTraceComponent* GetCrosshairTraceComp() const { return crossTraceComp; }
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return meshFP; }
	FORCEINLINE class UCameraComponent* GetFPCameraComp() const { return fpCameraComp; }
	FORCEINLINE class UAttributeComponent* GetAttrComp() const { return attrComp; }
	FORCEINLINE bool IsSprinting() const { return bIsSprinting; }
};
