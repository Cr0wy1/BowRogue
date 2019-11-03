// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BowRogueGameMode.h"
#include "BowRogueHUD.h"
#include "BowRogueCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "AdvancedPlayerController.h"

ABowRogueGameMode::ABowRogueGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Character/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	//Set default player controller class
	PlayerControllerClass = AAdvancedPlayerController::StaticClass();

	// use our custom HUD class
	HUDClass = ABowRogueHUD::StaticClass();
}
