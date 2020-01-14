// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
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



UENUM()
enum class EItemType : uint8 {
	PASSIVE,
	ACTIVE,
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



USTRUCT(BlueprintType)
struct BOWROGUE_API FAttribute {
	GENERATED_BODY()

	class UAttributeComponent* attrComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FName name = "ATTRIBUTE_NAME";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float min = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float max = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float value = 100.0f;

	FAttribute() {}
	FAttribute(class UAttributeComponent* _attrComp, FName _name, float _min, float _max, float _value);


	void SetValue(float newValue);
	void SetMin(float newMin, bool updateValue = false);
	void SetMax(float newMax, bool updateValue = false);

protected:

	void NotifyAttributeComponent();


public:
	FAttribute& operator+=(float addvalue) {
		value += addvalue;
		return *this;
	}

	FAttribute& operator-=(float subvalue) {
		value -= subvalue;
		return *this;
	}

	FAttribute& operator+=(const FAttribute &other) {
		value += other.value;
		max += other.max;
		return *this;
	}

	FAttribute& operator-=(const FAttribute &other) {
		value -= other.value;
		max -= other.max;
		return *this;
	}

	//Boolean operators
	bool operator==(float other) const { return value == other; }
	bool operator!=(float other) const { return value != other; }
	bool operator<(float other) const { return value < other; }
	bool operator>(float other) const { return value > other; }
	bool operator>=(float other) const { return value >= other; }
	bool operator<=(float other) const { return value <= other; }

};

USTRUCT(BlueprintType)
struct BOWROGUE_API FDynamicAttribute : public FAttribute {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float regAmount = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float regSpeed = 1.0f;

	float lastRegTime = 0.0f;

};



USTRUCT(BlueprintType)
struct BOWROGUE_API FItemData : public FTableRowBase {
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 id = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EItemType type = EItemType::PASSIVE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AItem> itemBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FAttribute> updateAttributes;

	static FItemData* FromId(UDataTable* datatable, FName id);
};

/**
 * 
 */
UCLASS()
class BOWROGUE_API UGameStructs : public UObject
{
	GENERATED_BODY()
	
};
