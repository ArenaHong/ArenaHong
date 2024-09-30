// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArenaHongGameMode.h"
#include "ArenaHongCharacter.h"
#include "UObject/ConstructorHelpers.h"

AArenaHongGameMode::AArenaHongGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
