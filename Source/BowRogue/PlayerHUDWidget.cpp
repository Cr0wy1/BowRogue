// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"
#include "TextBlock.h"

void UPlayerHUDWidget::SetInteractText(bool visible, FText text){
	if (visible) {
		interactText->SetText(text);
		interactText->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else {
		interactText->SetVisibility(ESlateVisibility::Collapsed);
	}
	
}
