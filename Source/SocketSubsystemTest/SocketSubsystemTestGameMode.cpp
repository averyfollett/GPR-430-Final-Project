// Copyright Epic Games, Inc. All Rights Reserved.

#include "SocketSubsystemTestGameMode.h"
#include "SocketSubsystemTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASocketSubsystemTestGameMode::ASocketSubsystemTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
