// Copyright Epic Games, Inc. All Rights Reserved.

#include "Course2GameMode.h"
#include "Course2Character.h"
#include "UObject/ConstructorHelpers.h"

ACourse2GameMode::ACourse2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

