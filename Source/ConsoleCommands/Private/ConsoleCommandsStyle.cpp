// Copyright Epic Games, Inc. All Rights Reserved.

#include "ConsoleCommandsStyle.h"
#include "ConsoleCommands.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FConsoleCommandsStyle::StyleInstance = nullptr;

void FConsoleCommandsStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FConsoleCommandsStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FConsoleCommandsStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("ConsoleCommandsStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FConsoleCommandsStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("ConsoleCommandsStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("ConsoleCommands")->GetBaseDir() / TEXT("Resources"));

	Style->Set("ConsoleCommands.PluginAction", new IMAGE_BRUSH_SVG(TEXT("ConsoleCommandsButton"), Icon20x20));
	return Style;
}

void FConsoleCommandsStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FConsoleCommandsStyle::Get()
{
	return *StyleInstance;
}
