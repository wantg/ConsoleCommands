// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "ConsoleCommandsStyle.h"

class FConsoleCommandsCommands : public TCommands<FConsoleCommandsCommands>
{
public:

	FConsoleCommandsCommands()
		: TCommands<FConsoleCommandsCommands>(TEXT("ConsoleCommands"), NSLOCTEXT("Contexts", "ConsoleCommands", "ConsoleCommands Plugin"), NAME_None, FConsoleCommandsStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};