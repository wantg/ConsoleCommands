// Copyright Epic Games, Inc. All Rights Reserved.

#include "ConsoleCommands.h"
#include "ConsoleCommandsStyle.h"
#include "ConsoleCommandsCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"

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
		FConsoleCommandsCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FConsoleCommandsModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FConsoleCommandsModule::RegisterMenus));
}

void FConsoleCommandsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FConsoleCommandsStyle::Shutdown();

	FConsoleCommandsCommands::Unregister();
}

void FConsoleCommandsModule::PluginButtonClicked()
{
    if (UEditorUtilityWidgetBlueprint* EUWBlueprint = LoadObject<UEditorUtilityWidgetBlueprint>(nullptr, TEXT("/ConsoleCommands/EUW_ConsoleCommands.EUW_ConsoleCommands"))) {
		if (FProperty* Property = EUWBlueprint->GetClass()->FindPropertyByName("bIsEnabledInPIE")) {
			if (bool* EnabledInPIEPtr = Property->ContainerPtrToValuePtr<bool>(EUWBlueprint)) {
				*EnabledInPIEPtr = true;
			}
		}
        if (UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>()) {
            EditorUtilitySubsystem->SpawnAndRegisterTab(EUWBlueprint);
			return;
        }
    }
	
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FConsoleCommandsModule::PluginButtonClicked()")),
							FText::FromString(TEXT("ConsoleCommands.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FConsoleCommandsModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FConsoleCommandsCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FConsoleCommandsCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FConsoleCommandsModule, ConsoleCommands)
