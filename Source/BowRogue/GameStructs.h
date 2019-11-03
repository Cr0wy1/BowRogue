// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStructs.generated.h"



class AEntity;



UENUM()
enum class EGridRoomType : uint8 {

	EMPTY, //Room can be placed
	DUMMY, //Room without door connection
	ROOM //Room with door connection

};



UENUM()
enum class EGridDir : uint8 {
	FRONT,
	RIGHT,
	BACK,
	LEFT,
};



UENUM()
enum class ERoomType : uint8 {
	EMPTY,
	FIGHT,
	SPAWN,
	RIDDLE,
	TREASURE,
	BOSS,
};



USTRUCT()
struct BOWROGUE_API FGridDir {
	GENERATED_BODY()

protected:
	FIntVector vec;
	EGridDir type;

public:
	FGridDir();
	FGridDir(EGridDir griddir);

	FGridDir RotateLeft();
	FGridDir RotateRight();
	FGridDir Flip();

	void SetDir(EGridDir griddir);

	FORCEINLINE FIntVector GetVec() const { return vec; }
	FORCEINLINE EGridDir GetType() const { return type; }

	bool operator==(const FGridDir &other) const;

	//Statics
	static FIntVector FRONT_VEC;
	static FIntVector RIGHT_VEC;
	static FIntVector BACK_VEC;
	static FIntVector LEFT_VEC;
	static FGridDir FRONT;
	static FGridDir RIGHT;
	static FGridDir BACK;
	static FGridDir LEFT;

	static TArray<FGridDir> DIRS;

	FORCEINLINE static FGridDir GetRandDir() { return DIRS[FMath::Rand() % DIRS.Num()]; }
};

//For using this struct in TMap as key
FORCEINLINE uint32 GetTypeHash(const FGridDir& gridir) {
	return FCrc::MemCrc_DEPRECATED(&gridir, sizeof(FGridDir));
}

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


//DungeonRoom
USTRUCT(BlueprintType)
struct BOWROGUE_API FDungeonRoomParams {
	GENERATED_BODY()

	bool bSpawnEntities = true;
	EGridRoomType gridtype = EGridRoomType::EMPTY;
	ERoomType roomtype = ERoomType::FIGHT;
};



USTRUCT()
struct BOWROGUE_API FGridRoom : public FDungeonRoomParams {
	GENERATED_BODY()

		int32 pathDistance = 0;
};
/**
 * 
 */
UCLASS()
class BOWROGUE_API UGameStructs : public UObject
{
	GENERATED_BODY()
	
};
