// Copyright Epic Games, Inc. All Rights Reserved.

#include "ConsoleCommandsCommands.h"

#define LOCTEXT_NAMESPACE "FConsoleCommandsModule"

void FConsoleCommandsCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "ConsoleCommands", "Execute ConsoleCommands action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
