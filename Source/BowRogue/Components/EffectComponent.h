// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EffectComponent.generated.h"



class AAdvancedCharacter;



USTRUCT(BlueprintType)
struct BOWROGUE_API FEffectData {
	GENERATED_BODY()


protected:
	AAdvancedCharacter * character;

public:

	FEffectData() {};
	FEffectData(AAdvancedCharacter *_character) : character(_character){}

	float duration = 2.0f;

	//storing original value from actor
	float tempValue = 0.0f;

	void Init(AAdvancedCharacter* _character);

	virtual void Start();
	virtual void End();
};

USTRUCT(BlueprintType)
struct BOWROGUE_API FEffectDataFreeze : public FEffectData {
	GENERATED_BODY()

protected:
	float baseWalkSpeed = 0.0f;

public:

	FEffectDataFreeze(){}
	FEffectDataFreeze(AAdvancedCharacter *_character) : FEffectData(_character) {}

	virtual void Start() override;
	virtual void End() override;
};

USTRUCT(BlueprintType)
struct BOWROGUE_API FEffectHandle {
	GENERATED_BODY()

public:
	FEffectHandle(){}
	FEffectHandle(FEffectData* _data) : data(_data){}

	FEffectData* data;

	
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOWROGUE_API UEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEffectComponent();

protected:

	FTimerHandle timer;

	AAdvancedCharacter * character;
	class FTimerManager* timeManager;

	TArray<FEffectHandle> effectHandles;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddEffect(FEffectData* effectData);

	UFUNCTION()
	void EndEffect(FEffectHandle effectHandle);
};
