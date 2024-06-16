// Copyright Epic Games, Inc. All Rights Reserved.

#include "Online/DeathmatchUltimaGameMode.h"
#include "Player/DeathmatchUltimaCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADeathmatchUltimaGameMode::ADeathmatchUltimaGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
