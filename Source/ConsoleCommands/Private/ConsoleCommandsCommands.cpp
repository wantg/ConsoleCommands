// Copyright Epic Games, Inc. All Rights Reserved.

#include "ConsoleCommandsCommands.h"

#define LOCTEXT_NAMESPACE "FConsoleCommandsModule"

void FConsoleCommandsCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "ConsoleCommands", "Bring up ConsoleCommands window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
