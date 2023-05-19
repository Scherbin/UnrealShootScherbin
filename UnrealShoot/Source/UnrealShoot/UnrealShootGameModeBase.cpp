// Copyright Epic Games, Inc. All Rights Reserved.


#include "UnrealShootGameModeBase.h"
#include "Player/UEBaSECharacter.h"
#include "Player/UEPlayerController.h"

AUnrealShootGameModeBase::AUnrealShootGameModeBase()
{
	DefaultPawnClass = AUEBaSECharacter::StaticClass();
	PlayerControllerClass = AUEPlayerController::StaticClass();
}