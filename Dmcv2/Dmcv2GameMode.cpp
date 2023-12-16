// Copyright Epic Games, Inc. All Rights Reserved.

#include "Dmcv2GameMode.h"
#include "Dmcv2Character.h"
#include "UObject/ConstructorHelpers.h"

ADmcv2GameMode::ADmcv2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
