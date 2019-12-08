// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AdvancedGameInstance.generated.h"



class ADungeonGenerator;
/**
 * 
 */
UCLASS()
class BOWROGUE_API UAdvancedGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:

	ADungeonGenerator * dungeonGenerator = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DungeonGenerator")
	TSubclassOf<ADungeonGenerator> dungeonGenerator_BP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structures")
	class UStructureAsset* structureAsset_A;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	class UWidgetAsset* widgetAsset_A;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Datatable")
	class UDataTable* itemDataTable;

public:

	virtual void Init() override;

	UFUNCTION(BlueprintCallable, Category = "DungeonGenerator")
	void SetDungeonGenerator(ADungeonGenerator* _dungeonGenerator);

	FORCEINLINE class UWidgetAsset* GetWidgetAsset() const { return widgetAsset_A; }
	FORCEINLINE class ADungeonGenerator* GetDungeonGenerator() const { return dungeonGenerator; }
	FORCEINLINE class UStructureAsset* GetStructureAsset() const { return structureAsset_A; }
	FORCEINLINE class UDataTable* GetItemDataTable() const { return itemDataTable; }
};
