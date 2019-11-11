// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"
#include "HealthWidget.h"
#include "TextBlock.h"
#include "AttributeComponent.h"



void UPlayerHUDWidget::Init(UAttributeComponent * _attrComp){
	attrComp = _attrComp;
	//attrComp->OnHealthUpdate.AddDynamic(this, &UPlayerHUDWidget::OnHealthUpdate);
	//attrComp->stamina.OnAttrChange.AddDynamic(this, &UPlayerHUDWidget::OnStaminaUpdate);
}

void UPlayerHUDWidget::OnHealthUpdate(float currentHealth, float updateAmount) {
	healthWidget->UpdateHealth(currentHealth, attrComp->GetMaxHealth());
}

void UPlayerHUDWidget::OnStaminaUpdate(){
	UE_LOG(LogTemp, Warning, TEXT("%s"), "Hallo");
	healthWidget->UpdateStamina(attrComp->stamina.value, attrComp->stamina.max);
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
