// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyFirstPersonalGameGameMode.h"
#include "MyFirstPersonalGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyFirstPersonalGameGameMode::AMyFirstPersonalGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
