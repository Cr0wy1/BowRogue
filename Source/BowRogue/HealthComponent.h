// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameStructs.h"
#include "HealthComponent.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOWROGUE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:

	UPROPERTY(EditAnywhere, Category = "Health")
	FAttribute health;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	FDynamicAttribute stamina;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UPROPERTY(BlueprintAssignable)
	FOnDeathSignature OnDeath;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void UpdateHealth(const FPlayerAttributeUpdate &attributeUpdate);
	void UpdateStamina(const FPlayerAttributeUpdate &attributeUpdate);

	void ApplyDamage(float damageAmount);
	void ConsumeStamina(float amount);

	void SetHealth(FAttribute& attribute) { health = attribute; }
	void SetStamina(FDynamicAttribute& attribute) { stamina = attribute; }
	FORCEINLINE FAttribute GetHealth() const { return health; }
	FORCEINLINE FDynamicAttribute GetStamina() const { return stamina; }
};
