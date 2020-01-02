// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameStructs.h"
#include "AttributeComponent.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttrChangeSignature);




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOWROGUE_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FAttribute walkSpeed = FAttribute(this, "WalkSpeed", 300, 1000, 600);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FAttribute walkSpeedMultiplier = FAttribute(this, "WalkSpeedMultiplier", 1.0, 5.0, 1.0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FAttribute sizeMultiplier = FAttribute(this, "SizeMultiplier", 0.5, 2.0, 1.0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FAttribute jumpHeight = FAttribute(this, "JumpHeight", 600, 1000, 860);

	//UPROPERTIES

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FDynamicAttribute health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FDynamicAttribute stamina;

	//Events
	FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable, Category = "Attribute") 
	FOnAttrChangeSignature OnAttrChange;
	

	//UPROPERTY(BlueprintAssignable)
	//FOnAttrChange OnStaminaChange;

	// Sets default values for this component's properties
	UAttributeComponent();

protected:

	class AAdvancedCharacter * character = nullptr;

	TArray<FAttribute*> attributes;

	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ApplyDamage(float amount);

	void AddHealth(float value);
	void AddHealthMax(float value);
	void AddStamina(float value);
	void AddStaminaMax(float value);

	void AddAttribute(FAttribute* attribute);

	//Called from FAttribute struct if min, max or value getting updated
	void OnAttributeUpdate(FAttribute* updatedAttribute);

	UFUNCTION(BlueprintCallable)
	void UpdateAttributes();


	FORCEINLINE float GetHealth() const { return health.value; }
	FORCEINLINE float GetMaxHealth() const { return health.max; } 
	FORCEINLINE FDynamicAttribute GetStamina() const { return stamina; }

	//Debug
	UFUNCTION(BlueprintCallable)
	void PrintDebug();
};
