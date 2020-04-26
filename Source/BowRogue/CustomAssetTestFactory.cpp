// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetTestFactory.h"
#include "CustomAssetTest.h"



UCustomAssetTestFactory::UCustomAssetTestFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	//Formats.Add(FString(TEXT("txt;")) + NSLOCTEXT("UTextAssetFactory", "FormatTxt", "Text File").ToString());
	SupportedClass = UCustomAssetTest::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}


UObject* UCustomAssetTestFactory::FactoryCreateNew(UClass* inClass, UObject* inParent, FName inName, EObjectFlags flags, UObject* context, FFeedbackContext* warn) {

	return NewObject<UCustomAssetTest>(inParent, inClass, inName, flags);
}

//UObject * UCustomAssetTestFactory::FactoryCreateBinary(UClass * Class, UObject * InParent, FName Name, EObjectFlags Flags, UObject * Context, const TCHAR * Type, const uint8 *& Buffer, const uint8 * BufferEnd, FFeedbackContext * Warn){

	//return NewObject<UCustomAssetTest>(InParent, Class, Name, Flags);
//}

bool UCustomAssetTestFactory::ShouldShowInNewMenu() const{

	return true;
}
