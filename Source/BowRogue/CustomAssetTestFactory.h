// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "CustomAssetTestFactory.generated.h"

/**
 * 
 */
UCLASS()
class BOWROGUE_API UCustomAssetTestFactory : public UFactory{
	GENERATED_BODY()

public:

	UCustomAssetTestFactory(const FObjectInitializer& ObjectInitializer);

	virtual UObject* FactoryCreateNew(UClass* inClass, UObject* inParent, FName inName, EObjectFlags flags, UObject* context, FFeedbackContext* warn) override;
	//virtual UObject* FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn) override;

	virtual bool ShouldShowInNewMenu() const override;
	
};
