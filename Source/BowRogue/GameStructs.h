// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Items/ItemUpdateStructs.h"
#include "GameStructs.generated.h"



class AEntity;
class ADungeonRoom;
class APlaceableActor;



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
	END,
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
struct BOWROGUE_API FConnectedRooms {
	GENERATED_BODY()

	ADungeonRoom* front = nullptr;
	ADungeonRoom* right = nullptr;
	ADungeonRoom* back = nullptr;
	ADungeonRoom* left = nullptr;
	ADungeonRoom* top = nullptr;
	ADungeonRoom* bottom = nullptr;
};



//DungeonRoom
USTRUCT(BlueprintType)
struct BOWROGUE_API FDungeonGridCell {
	GENERATED_BODY()

	FIntVector gridLoc;
	bool bSpawnEntities = true;
	EGridRoomType gridtype = EGridRoomType::EMPTY;
	ERoomType roomtype = ERoomType::FIGHT;
	TSubclassOf<ADungeonRoom> roomBP;
	ADungeonRoom* spawnedRoom = nullptr;

	FDungeonGridCell* front = nullptr;
	FDungeonGridCell* right = nullptr;
	FDungeonGridCell* back = nullptr;
	FDungeonGridCell* left = nullptr;
};



USTRUCT()
struct BOWROGUE_API FGridRoom : public FDungeonGridCell {
	GENERATED_BODY()

		int32 pathDistance = 0;
};


USTRUCT()
struct BOWROGUE_API FDungeonGrid {
	GENERATED_BODY()

protected:
	int32 xSize = 0;
	int32 ySize = 0;
	TArray<TArray<FGridRoom>> grid;

public:
	void Init(int32 _xSize, int32 _ySize) {
		xSize = _xSize;
		ySize = _ySize;
		grid.Init(TArray<FGridRoom>(), xSize);
		for (int32 i = 0; i < xSize; i++) {
			grid[i].Init(FGridRoom(), ySize);
		}

		for (int32 x = 0; x < xSize; x++){
			for (int32 y = 0; y < ySize; y++) {
				grid[x][y].front = grid.IsValidIndex(x + 1) ? &grid[x + 1][y] : nullptr;
				grid[x][y].right = grid[x].IsValidIndex(y + 1) ? &grid[x][y + 1] : nullptr;
				grid[x][y].back = grid.IsValidIndex(x - 1) ? &grid[x - 1][y] : nullptr;
				grid[x][y].left = grid[x].IsValidIndex(y - 1) ? &grid[x][y - 1] : nullptr; 
			}
		}
	}

	void Reset() {
		for (int32 i = 0; i < xSize; i++) {
			grid[i].Reset();
		}
		grid.Reset();

		xSize = 0;
		ySize = 0;
	}

	int32 GetSizeX() const { return xSize; }
	int32 GetSizeY() const { return ySize; }
	int32 GetSizeTotel() const { return xSize * ySize; }

	bool IsValidIndex(int32 x, int32 y) const {
		return grid.IsValidIndex(x) && grid[x].IsValidIndex(y);
	}

	TArray<FGridRoom>& operator[](int32 x) {return grid[x];}
	const TArray<FGridRoom>& operator[](int32 x) const { return grid[x]; }
	FGridRoom& operator[](FIntVector xyVec) { return grid[xyVec.X][xyVec.Y]; }
	const FGridRoom& operator[](FIntVector xyVec) const { return grid[xyVec.X][xyVec.Y]; }

	void Log() {
		if (GetSizeTotel() < 1) return;

		for (int32 x = xSize - 1; x >= 0; x--) {
			FString row = "";
			for (int32 y = 0; y < ySize; y++) {
				if (grid[x][y].gridtype != EGridRoomType::EMPTY) {
					row += FString::FromInt(grid[x][y].pathDistance);
				}
				else {
					row += "#";
				}
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *row);
		}
	}
};




USTRUCT(BlueprintType)
struct BOWROGUE_API FAttribute {
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FName name = "ATTRIBUTE_NAME";

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float min = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float max = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	float value = 100.0f;


	FAttribute(){}

	void ClampValue() {
		if (min > max) {
			min = max;
			value = min;
		}
		else {
			value = FMath::Clamp(value, min, max);
		}
	}


	void SetName(FName newName) { name = newName; }
	void SetMin(float newMin) { min = newMin; }
	void SetMax(float newMax) { max = newMax; }
	void SetValue(float newValue) { value = newValue; }

	FORCEINLINE float GetMin() const { return min; }
	FORCEINLINE float GetMax() const { return max; }
	FORCEINLINE float GetValue() const { return value; }
};

USTRUCT(BlueprintType)
struct BOWROGUE_API FDynamicAttribute : public FAttribute {
	GENERATED_BODY()
	
	FDynamicAttribute(){}

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
	UTexture2D* texture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UItemObject> itemObjectBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCharacterUpdate characterUpdate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeaponUpdate weaponUpdate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FProjectileUpdate projectileUpdate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FArrowUpdate arrowUpdate;



	static FItemData* FromId(UDataTable* datatable, FName id);
};

USTRUCT(BlueprintType)
struct BOWROGUE_API FPlaceableData : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 id = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName name = "NAME";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fireRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float range = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* texture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APlaceableActor> placeableActorBP;

};

/**
 * 
 */
UCLASS()
class BOWROGUE_API UGameStructs : public UObject
{
	GENERATED_BODY()
	
};
