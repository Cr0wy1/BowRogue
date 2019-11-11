// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedWidget.h"
#include "GameStructs.h"
#include "MapWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOWROGUE_API UMapWidget : public UAdvancedWidget
{
	GENERATED_BODY()
	
protected:

	bool bIsMapOpen = false;

	class UCanvasRenderTarget2D* canvasRender = nullptr;
	const TArray<TArray<FGridRoom>>* roomGrid = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UImage* mapImage;

public:

	virtual bool Initialize() override;

	void Update(const TArray<TArray<FGridRoom>>* _roomGrid);

	void OpenMap();
	void CloseMap();
	void ToggleMap();

	UFUNCTION()
	void DrawToCanvasRenderTarget(class UCanvas* canvas, int32 width, int32 height);
};
