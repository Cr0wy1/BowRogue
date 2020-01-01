// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameStructs.h"
#include "SortedMap.h"
#include "AttributeComponent.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttrChange, const FAttribute&, attribute);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOWROGUE_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FAttribute walkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FAttribute walkSpeedMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FAttribute sizeMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FAttribute jumpHeight;

	//UPROPERTIES

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FDynamicAttribute health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FDynamicAttribute stamina;

	//Events
	FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable)
	FOnAttrChange OnHealthChange;

	UPROPERTY(BlueprintAssignable)
	FOnAttrChange OnStaminaChange;

	// Sets default values for this component's properties
	UAttributeComponent();

protected:

	class AAdvancedCharacter * character = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	TArray<FAttribute> attributes;

	TSortedMap<FName, FAttribute*, FDefaultAllocator, FNameFastLess> attributesLookup;

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

	UFUNCTION(BlueprintCallable)
	void AddAttribute(FAttribute attribute);

	
	void AddAttribute(FName name, float max, float value);

	UFUNCTION(BlueprintCallable)
	void UpdateAttributes();

	//return true if attribute found, else false
	bool UpdateAttribute(const FAttribute &attribute);
	FORCEINLINE bool DoesAttributeExist(FName name);
	FORCEINLINE const FAttribute* GetAttribute(FName name);

	FORCEINLINE float GetHealth() const { return health.value; }
	FORCEINLINE float GetMaxHealth() const { return health.max; } 
	FORCEINLINE FDynamicAttribute GetStamina() const { return stamina; }

	//Debug
	UFUNCTION(BlueprintCallable)
	void PrintDebug();
};
