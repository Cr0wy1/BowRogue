// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemUpdateStructs.generated.h"




UENUM(BlueprintType)
enum class EAttributeType : uint8 {
	NONE,
	HEALTH,
	STAMINA
};


UENUM(BlueprintType)
enum class EProjectileAttributeType : uint8 {
	NONE,
	DAMAGE,
	KNOCKBACK,
	WEIGHT,
	SPEED
	
}; 


UENUM(BlueprintType)
enum class EArrowMeshType : uint8 {
	NONE,
	HEAD,
	BODY,
	FLETCHING
};


USTRUCT(BlueprintType)
struct BOWROGUE_API FAttributeUpdateBase {
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Update")
		float value = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Update")
		float min = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Update")
		float max = 0.0f;
};



USTRUCT(BlueprintType)
struct BOWROGUE_API FPlayerAttributeUpdate : public FAttributeUpdateBase {
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Update")
		EAttributeType type = EAttributeType::NONE;

};


USTRUCT(BlueprintType)
struct BOWROGUE_API FWeaponAttachmentUpdate {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName socketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* meshAttachment;
};


USTRUCT(BlueprintType)
struct BOWROGUE_API FProjectileAttributeUpdate : public FAttributeUpdateBase {
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Update")
		EProjectileAttributeType type = EProjectileAttributeType::NONE;

};



USTRUCT(BlueprintType)
struct BOWROGUE_API FArrowMeshUpdate {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EArrowMeshType meshType = EArrowMeshType::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh* newMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bOverrideColor = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bOverrideColor"))
	FColor newColor = FColor::White;
};



USTRUCT(BlueprintType)
struct BOWROGUE_API FCharacterUpdate {
	GENERATED_BODY()
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPlayerAttributeUpdate> attributeUpdates;


};


USTRUCT(BlueprintType)
struct BOWROGUE_API FWeaponUpdate {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FWeaponAttachmentUpdate> attachmentUpdates;
};


USTRUCT(BlueprintType)
struct BOWROGUE_API FProjectileUpdate {
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FProjectileAttributeUpdate> attributeUpdates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<class UProjectileEffectBase>> addEffects;
};



USTRUCT(BlueprintType)
struct BOWROGUE_API FArrowUpdate {
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FArrowMeshUpdate> meshUpdates;
};

/**
 * 
 */
UCLASS()
class BOWROGUE_API UItemUpdateStructs : public UObject
{
	GENERATED_BODY()
	
};
