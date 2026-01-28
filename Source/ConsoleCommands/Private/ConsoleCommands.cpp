// Copyright Epic Games, Inc. All Rights Reserved.

#include "ConsoleCommands.h"
#include "ConsoleCommandsStyle.h"
#include "ConsoleCommandsCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Blueprint/UserWidget.h"
#include "ToolMenus.h"

static const FName ConsoleCommandsTabName("ConsoleCommands");

#define LOCTEXT_NAMESPACE "FConsoleCommandsModule"

void FConsoleCommandsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FConsoleCommandsStyle::Initialize();
	FConsoleCommandsStyle::ReloadTextures();

	FConsoleCommandsCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FConsoleCommandsCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FConsoleCommandsModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FConsoleCommandsModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ConsoleCommandsTabName, FOnSpawnTab::CreateRaw(this, &FConsoleCommandsModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FConsoleCommandsTabTitle", "ConsoleCommands"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FConsoleCommandsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FConsoleCommandsStyle::Shutdown();

	FConsoleCommandsCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ConsoleCommandsTabName);
}

TSharedRef<SDockTab> FConsoleCommandsModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	UUserWidget* Widget = CreateWidget<UUserWidget>(World, LoadClass<UUserWidget>(nullptr, TEXT("/ConsoleCommands/UW_ConsoleCommands.UW_ConsoleCommands_C")));
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FConsoleCommandsModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("ConsoleCommands.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
                Widget ? Widget->TakeWidget() : SNew(STextBlock).Text(WidgetText)
			]
		];
}

void FConsoleCommandsModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(ConsoleCommandsTabName);
}

void FConsoleCommandsModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FConsoleCommandsCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FConsoleCommandsCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FConsoleCommandsModule, ConsoleCommands)
