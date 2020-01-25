// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedWidget.h"
#include "AdvancedCharacter.h"


AAdvancedCharacter* UAdvancedWidget::GetAdvancedCharacter() const{
	return Cast<AAdvancedCharacter>(GetOwningPlayerPawn());
}