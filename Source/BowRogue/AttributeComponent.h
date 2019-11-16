// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameStructs.h"
#include "AttributeComponent.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttrChange, const FAttribute&, attribute);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOWROGUE_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	//UPROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float walkSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FAttribute health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FAttribute stamina;

	//Events
	FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable)
	FOnAttrChange OnHealthChange;

	UPROPERTY(BlueprintAssignable)
	FOnAttrChange OnStaminaChange;

	// Sets default values for this component's properties
	UAttributeComponent();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ApplyDamage(float amount);
		
	FORCEINLINE float GetHealth() const { return health.value; }
	FORCEINLINE float GetMaxHealth() const { return health.max; }
	FORCEINLINE FAttribute GetStamina() const { return stamina; }
};
