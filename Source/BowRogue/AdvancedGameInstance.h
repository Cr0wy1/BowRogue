// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AdvancedGameInstance.generated.h"



/**
 * 
 */
UCLASS()
class BOWROGUE_API UAdvancedGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structures")
	class UStructureAsset* structureAsset_A;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	class UWidgetAsset* widgetAsset_A;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Datatable")
	class UDataTable* itemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Defaults")
	class UDungeonDefaultsAsset* dungeonDefaults_A;
	 
public:

	virtual void Init() override;

	FORCEINLINE class UWidgetAsset* GetWidgetAsset() const { return widgetAsset_A; }
	FORCEINLINE class UStructureAsset* GetStructureAsset() const { return structureAsset_A; }
	FORCEINLINE class UDataTable* GetItemDataTable() const { return itemDataTable; }
	FORCEINLINE class UDungeonDefaultsAsset* GetDungeonDefaultsAsset() const { return dungeonDefaults_A; }
};
