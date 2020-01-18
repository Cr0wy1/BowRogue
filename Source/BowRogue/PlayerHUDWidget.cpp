// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"
#include "HealthWidget.h"
#include "TextBlock.h"
#include "AttributeComponent.h"



void UPlayerHUDWidget::Init(UAttributeComponent * _attrComp){
	attrComp = _attrComp;
	attrComp->OnAttrChange.AddDynamic(this, &UPlayerHUDWidget::OnAttributeUpdate);
	//attrComp->OnHealthChange.AddDynamic(this, &UPlayerHUDWidget::OnHealthUpdate);
	//attrComp->OnStaminaChange.AddDynamic(this, &UPlayerHUDWidget::OnStaminaUpdate);
	OnHealthUpdate();
	OnStaminaUpdate();

	
}

void UPlayerHUDWidget::OnHealthUpdate() {
	UE_LOG(LogTemp, Warning, TEXT("Widget Health: %s"), *attrComp->health.ToString());

	healthWidget->UpdateHealth(attrComp->health.value, attrComp->health.max);
}
void UPlayerHUDWidget::OnAttributeUpdate(){
	OnHealthUpdate();
	OnStaminaUpdate();
}


void UPlayerHUDWidget::OnStaminaUpdate(){
	healthWidget->UpdateStamina(attrComp->health.value, attrComp->health.max);
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
