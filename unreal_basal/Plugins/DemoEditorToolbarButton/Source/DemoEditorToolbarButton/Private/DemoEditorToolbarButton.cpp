// Copyright Epic Games, Inc. All Rights Reserved.

#include "DemoEditorToolbarButton.h"
#include "DemoEditorToolbarButtonStyle.h"
#include "DemoEditorToolbarButtonCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName DemoEditorToolbarButtonTabName("DemoEditorToolbarButton");

#define LOCTEXT_NAMESPACE "FDemoEditorToolbarButtonModule"

void FDemoEditorToolbarButtonModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FDemoEditorToolbarButtonStyle::Initialize();
	FDemoEditorToolbarButtonStyle::ReloadTextures();

	FDemoEditorToolbarButtonCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FDemoEditorToolbarButtonCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FDemoEditorToolbarButtonModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FDemoEditorToolbarButtonModule::RegisterMenus));
}

void FDemoEditorToolbarButtonModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FDemoEditorToolbarButtonStyle::Shutdown();

	FDemoEditorToolbarButtonCommands::Unregister();
}

void FDemoEditorToolbarButtonModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FDemoEditorToolbarButtonModule::PluginButtonClicked()")),
							FText::FromString(TEXT("DemoEditorToolbarButton.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FDemoEditorToolbarButtonModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FDemoEditorToolbarButtonCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FDemoEditorToolbarButtonCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDemoEditorToolbarButtonModule, DemoEditorToolbarButton)