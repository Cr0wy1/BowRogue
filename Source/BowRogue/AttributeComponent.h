// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameStructs.h"
#include "AttributeComponent.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttrChangeSignature);



USTRUCT(BlueprintType)
struct BOWROGUE_API FAttributeField {
	GENERATED_BODY()

		friend UAttributeObject;

protected:

	class UAttributeObject* attributeObject;

	UPROPERTY()
	float value = 0.0f;

	void NotifyAttribute();

public:

	FAttributeField() {}

	void Init(class UAttributeObject* _attributeObject, float _value);

	void Set(float newValue) {
		value = newValue;
		NotifyAttribute();
	}

	float Get() const { return value; }

	operator float() const {
		return value;
	}

	FAttributeField& operator=(float otherValue) {
		value = otherValue;
		NotifyAttribute();
		return *this;
	}

	FAttributeField& operator+=(float otherValue) {
		value += otherValue;
		NotifyAttribute();
		return *this;
	}

	FAttributeField& operator-=(float otherValue) {
		value -= otherValue;
		NotifyAttribute();
		return *this;
	}

	FAttributeField& operator*=(float otherValue) {
		value *= otherValue;
		NotifyAttribute();
		return *this;
	}

	FAttributeField& operator/=(float otherValue) {
		value /= otherValue;
		NotifyAttribute();
		return *this;
	}
};



UCLASS()
class BOWROGUE_API UAttributeObject : public UObject {
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName name;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttributeField min;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttributeField value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttributeField max;

	void AfterFieldsChanged() {
		if (min.value > max.value) {
			min.value = max.value;
			value.value = min.value;
		}
		else {
			value.value = FMath::Clamp(value.value, min.value, max.value);
		} 

		OnChange.Broadcast();
	}
public:

	FOnAttrChangeSignature OnChange;

	void Init(const FAttribute &attribute) {
		min.value = attribute.min;
		max.value = attribute.max;
		value.value = attribute.value;
		OnChange.Broadcast();
	}

	static UAttributeObject* CreateAttribute(UObject* outer, FName _name, float min, float max, float value) {
		UAttributeObject* attribute = NewObject<UAttributeObject>(outer, _name);
		attribute->min.Init(attribute, min);
		attribute->max.Init(attribute, max);
		attribute->value.Init(attribute, value);
		return attribute;
	}

	FString ToString() const {
		FString string;
		string = name.ToString() + " Attribute(Min:" + FString::SanitizeFloat(min) + ", Max:" + FString::SanitizeFloat(max) + ", Value:" + FString::SanitizeFloat(value) + ")";
		return string;
	}
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOWROGUE_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY()
	UAttributeObject * health;

	UPROPERTY()
	UAttributeObject * stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttribute healthInit;

	//Events
	FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable, Category = "Attribute") 
	FOnAttrChangeSignature OnAttrChange;
	
	// Sets default values for this component's properties
	UAttributeComponent();

protected:

	class AAdvancedCharacter * character = nullptr;

	TArray<UAttributeObject*> attributes;

	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddAttribute(UAttributeObject* attribute);

	//Called from FAttribute struct if min, max or value getting updated
	void OnAttributeUpdate(FAttribute* updatedAttribute);

	UFUNCTION(BlueprintCallable)
	void UpdateAttributes();

	//Debug
	UFUNCTION(BlueprintCallable)
	void PrintDebug();
};
