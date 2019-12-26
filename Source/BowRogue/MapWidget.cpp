// Fill out your copyright notice in the Description page of Project Settings.


#include "MapWidget.h"
#include "CanvasPanel.h"
#include "Engine/Canvas.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "Image.h"
#include "Components/SceneCaptureComponent2D.h"

bool UMapWidget::Initialize(){

	bool bReturn = Super::Initialize();

	SetVisibility(ESlateVisibility::Collapsed);

	canvasRender = UCanvasRenderTarget2D::CreateCanvasRenderTarget2D(this, UCanvasRenderTarget2D::StaticClass());
	canvasRender->OnCanvasRenderTargetUpdate.AddDynamic(this, &UMapWidget::DrawToCanvasRenderTarget);
	mapImage->SetBrushResourceObject(canvasRender);

	

	return bReturn;
}

void UMapWidget::Update(const TArray<TArray<FGridRoom>>* _roomGrid){
	roomGrid = _roomGrid;
	if (canvasRender && roomGrid) {
		canvasRender->UpdateResource();
	}
	
}


void UMapWidget::OpenMap(){
	SetVisibility(ESlateVisibility::HitTestInvisible);
	bIsMapOpen = true;
}

void UMapWidget::CloseMap(){
	SetVisibility(ESlateVisibility::Collapsed);
	bIsMapOpen = false;
}

void UMapWidget::ToggleMap(){
	bIsMapOpen ? CloseMap() : OpenMap();
}

void UMapWidget::DrawToCanvasRenderTarget(UCanvas * canvas, int32 width, int32 height){
	if (roomGrid->Num() < 1 && (*roomGrid)[0].Num() < 1) return;

	float cellSpace = 10.0f;

	int32 gridSizeX = roomGrid->Num();
	int32 gridSizeY = (*roomGrid)[0].Num();

	float boxSize = gridSizeX > gridSizeY ? (float)width / gridSizeX : (float)height / gridSizeY;
	float boxCenter = boxSize * 0.5f;

	FVector2D canvasCenter = FVector2D(width, height) * 0.5f;

	
	//canvas->K2_DrawBox(boxPos, FVector2D(boxSize, boxSize), 5.0f);
	//boxPos.Y -= boxSize + cellSpace;
	

	FVector2D boxPos = FVector2D(0, height); //Starting at bottem left corner
	FLinearColor boxColor = FLinearColor::White;
	FLinearColor iconColor = FLinearColor::Blue;
	for (int32 x = 0; x < gridSizeX; x++){
		for (int32 y = 0; y < gridSizeY; y++) {
			if ((*roomGrid)[x][y].gridtype != EGridRoomType::EMPTY) {
				ERoomType roomType = (*roomGrid)[x][y].roomtype;
				if (roomType == ERoomType::SPAWN) {
					canvas->K2_DrawBox(boxPos + boxSize*0.25f, FVector2D(boxSize, boxSize)*0.5f, 10.0f, iconColor);
					//boxColor = FLinearColor::Blue;
				}
				else if(roomType == ERoomType::BOSS){
					canvas->K2_DrawBox(boxPos + boxSize * 0.25f, FVector2D(boxSize, boxSize)*0.5f, 10.0f, FLinearColor::Red);
					//boxColor = FLinearColor::White;
				}

				canvas->K2_DrawBox(boxPos, FVector2D(boxSize, boxSize), 5.0f, boxColor);

			}
			boxPos.X += boxSize; //X and Y Axe is changed because of translation
		}
		boxPos.Y -= boxSize;
		boxPos.X = 0;
	}
}

 