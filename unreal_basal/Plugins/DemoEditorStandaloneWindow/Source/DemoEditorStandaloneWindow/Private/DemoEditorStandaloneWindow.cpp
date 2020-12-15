// Copyright Epic Games, Inc. All Rights Reserved.

#include "DemoEditorStandaloneWindow.h"
#include "DemoEditorStandaloneWindowStyle.h"
#include "DemoEditorStandaloneWindowCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName DemoEditorStandaloneWindowTabName("DemoEditorStandaloneWindow");

#define LOCTEXT_NAMESPACE "FDemoEditorStandaloneWindowModule"

void FDemoEditorStandaloneWindowModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FDemoEditorStandaloneWindowStyle::Initialize();
	FDemoEditorStandaloneWindowStyle::ReloadTextures();

	FDemoEditorStandaloneWindowCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FDemoEditorStandaloneWindowCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FDemoEditorStandaloneWindowModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FDemoEditorStandaloneWindowModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(DemoEditorStandaloneWindowTabName, FOnSpawnTab::CreateRaw(this, &FDemoEditorStandaloneWindowModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FDemoEditorStandaloneWindowTabTitle", "DemoEditorStandaloneWindow"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FDemoEditorStandaloneWindowModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FDemoEditorStandaloneWindowStyle::Shutdown();

	FDemoEditorStandaloneWindowCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(DemoEditorStandaloneWindowTabName);
}

TSharedRef<SDockTab> FDemoEditorStandaloneWindowModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FDemoEditorStandaloneWindowModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("DemoEditorStandaloneWindow.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FDemoEditorStandaloneWindowModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(DemoEditorStandaloneWindowTabName);
}

void FDemoEditorStandaloneWindowModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FDemoEditorStandaloneWindowCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FDemoEditorStandaloneWindowCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDemoEditorStandaloneWindowModule, DemoEditorStandaloneWindow)