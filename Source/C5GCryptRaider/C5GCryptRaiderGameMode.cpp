// Copyright Epic Games, Inc. All Rights Reserved.

#include "C5GCryptRaiderGameMode.h"
#include "C5GCryptRaiderCharacter.h"
#include "UObject/ConstructorHelpers.h"

AC5GCryptRaiderGameMode::AC5GCryptRaiderGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
