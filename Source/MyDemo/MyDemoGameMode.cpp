// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyDemoGameMode.h"
#include "MyDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyDemoGameMode::AMyDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
