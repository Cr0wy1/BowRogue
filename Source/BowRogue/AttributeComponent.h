// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttrChange);




//USTRUCT(BlueprintType)
//struct BOWROGUE_API FAttribute {
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
//	float value = 100.0f;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
//	float max = 100.0f;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
//	float regAmount = 0.0f;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
//	float regSpeed = 1.0f;
//
//	float lastRegTime = 0.0f;
//
//	void SetValue(float newValue) {
//		value = newValue;
//	}
//
//	FAttribute& operator+=(float addvalue) {
//		value += addvalue;
//		return *this;
//	}
//
//	FAttribute& operator-=(float subvalue) {
//		value -= subvalue;
//		return *this;
//	}
//};




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOWROGUE_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	FOnDeath OnDeath;
	//FOnAttrChange OnAttrChange;

	// Sets default values for this component's properties
	UAttributeComponent();

protected:

	//UPROPERTIES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float maxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float walkSpeed = 100.0f;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	//FAttribute stamina;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ApplyDamage(float amount);
		
	FORCEINLINE float GetHealth() const { return health; }
	FORCEINLINE float GetMaxHealth() const { return maxHealth; }
	//FORCEINLINE FAttribute GetStamina() const { return stamina; }
};
