// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"
#include "HealthWidget.h"
#include "TextBlock.h"
#include "AttributeComponent.h"



void UPlayerHUDWidget::Init(UAttributeComponent * _attrComp){
	attrComp = _attrComp;
	attrComp->OnHealthChange.AddDynamic(this, &UPlayerHUDWidget::OnHealthUpdate);
	attrComp->OnStaminaChange.AddDynamic(this, &UPlayerHUDWidget::OnStaminaUpdate);
	OnHealthUpdate(attrComp->health);
	OnStaminaUpdate(attrComp->stamina);

	
}

void UPlayerHUDWidget::OnHealthUpdate(const FAttribute& attribute) {
	healthWidget->UpdateHealth(attribute.value, attribute.max);
}

void UPlayerHUDWidget::OnStaminaUpdate(const FAttribute& attribute){
	healthWidget->UpdateStamina(attribute.value, attribute.max);
}

void UPlayerHUDWidget::SetInteractText(bool visible, FText text){
	if (visible) {
		interactText->SetText(text);
		interactText->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else {
		interactText->SetVisibility(ESlateVisibility::Collapsed);
	}
	
}
