// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AdvancedCharacter.generated.h"



class UCrosshairTraceComponent;
struct FCrosshairResult;



UCLASS()
class BOWROGUE_API AAdvancedCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	const FCrosshairResult* crosshairResult = nullptr;

	//UPROPERTIES
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera) 
	float BaseTurnRate; /** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate; /** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */

	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* fpCameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CrosshairTrace")
	UCrosshairTraceComponent* crossTraceComp;

	// Sets default values for this character's properties
	AAdvancedCharacter();

protected:

	UCharacterMovementComponent * movementComp = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
