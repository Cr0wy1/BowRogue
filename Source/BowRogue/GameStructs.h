// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStructs.generated.h"



class AEntity;


USTRUCT(BlueprintType)
struct BOWROGUE_API FEntitySpawnParams {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnParams")
	TSubclassOf<AEntity> templateClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnParams")
	FVector location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnParams")
	FRotator rotation;

	FEntitySpawnParams() {};
	FEntitySpawnParams(TSubclassOf<AEntity> _templateClass, FVector _location, FRotator _rotation = FRotator::ZeroRotator) : templateClass(_templateClass), location(_location), rotation(_rotation){};
};


USTRUCT(BlueprintType)
struct BOWROGUE_API FSpawnPattern {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnParams")
	TArray<FEntitySpawnParams> spawns;

	FEntitySpawnParams& operator[](int32 index) {
		return spawns[index];
	}

	const FEntitySpawnParams& operator[](int32 index) const {
		return spawns[index];
	}
};
/**
 * 
 */
UCLASS()
class BOWROGUE_API UGameStructs : public UObject
{
	GENERATED_BODY()
	
};
