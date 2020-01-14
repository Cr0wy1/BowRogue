// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "EffectBase.generated.h"

/**
 * 
 */
UCLASS()
class BOWROGUE_API UEffectBase : public UObject{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly)
	FName nameId = "NONE";

public:

	virtual void BeginDestroy() override {
		UE_LOG(LogTemp, Warning, TEXT("I am getting destroyed!"));
		Super::BeginDestroy();
	}

	FORCEINLINE FName GetNameId() const { return nameId; }

	//Campare effect names
	bool HasEqualName(const UEffectBase* otherEffect) const {
		return nameId == otherEffect->nameId;
	}

	//Campare effect name
	bool HasEqualName(const FName& otherNameId) const {
		return nameId == otherNameId;
	}
};




UCLASS(Blueprintable, BlueprintType)
class BOWROGUE_API UProjectileEffectBase : public UEffectBase {
	GENERATED_BODY()


protected:
	UPROPERTY(BlueprintReadOnly)
	class AProjectile * projectile;

public:

	virtual void Init(class AProjectile * _projectile);

	virtual void OnTick(float deltaTime) {
		OnTickEvent(deltaTime);
	}

	virtual void OnHit(const FHitResult& hitResult) {
		OnHitEvent(hitResult);
	}

	virtual void OnSpawn() {
		OnSpawnEvent();
	}

	//Blueprintevents
	UFUNCTION(BlueprintImplementableEvent)
	void OnHitEvent(const FHitResult& hitResult);

	UFUNCTION(BlueprintImplementableEvent)
	void OnTickEvent(float deltaTime);

	UFUNCTION(BlueprintImplementableEvent)
	void OnSpawnEvent();


	
};


USTRUCT()
struct BOWROGUE_API FProjectileEffectManager {
	GENERATED_BODY()

	UPROPERTY() 
	TArray<UProjectileEffectBase*> effects;

public:

	void CallAllOnHit(const FHitResult& hitResult);
	void CallAllOnTick(float deltaTime);
	void CallAllOnSpawn();
	//UProjectileEffectBase * AddEffect(UProjectileEffectBase* newEffect);

	bool HasEffect(const FName& effectName) const;
	bool HasEffect(const UProjectileEffectBase* checkEffect) const;
};
