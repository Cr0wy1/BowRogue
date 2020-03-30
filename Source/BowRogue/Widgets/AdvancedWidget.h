// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AdvancedWidget.generated.h"

/**
 * 
 */
class AAdvancedCharacter;
class AAdvancedPlayerController;



UCLASS()
class BOWROGUE_API UAdvancedWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
};

//Creates a Widget and adds it to player Screen, returns nullptr if widgetBP is not set
template<typename T, typename TOwner = UObject>
T* CreateAddViewport(TOwner* owner, TSubclassOf<class UUserWidget> widgetBP) {
	if (widgetBP) {
		T* widget = CreateWidget<T>(owner, widgetBP);
		widget->AddToPlayerScreen();
		return widget;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("CreateAddViewport: WidgetBP is NULL"));
	}
	return nullptr;
}