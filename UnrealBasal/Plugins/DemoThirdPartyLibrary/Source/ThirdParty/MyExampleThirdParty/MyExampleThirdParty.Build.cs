// Fill out your copyright notice in the Description page of Project Settings.

using System;
using System.IO;
using UnrealBuildTool;

public class MyExampleThirdParty : ModuleRules
{
	public MyExampleThirdParty(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		// Add any macros that need to be set
		// https://docs.unrealengine.com/4.27/en-US/ProductionPipelines/BuildTools/UnrealBuildTool/ThirdPartyLibraries/
		PublicDefinitions.Add("WITH_MYTHIRDPARTYLIBRARY=1");
		
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "x64", "Release", "ExampleLibrary.lib"));

			Console.Write("MyExampleThirdParty.Build ModuleDirectory: ");
			Console.WriteLine(ModuleDirectory);			
			Console.Write("MyExampleThirdParty.Build PluginDirectory: ");
			Console.WriteLine(PluginDirectory);

			// Delay-load the DLL, so we can load it from the right place first
			PublicDelayLoadDLLs.Add("ExampleLibrary.dll");

			// Ensure that the DLL is staged along with the executable
			RuntimeDependencies.Add(Path.Combine(PluginDirectory, "Binaries", "ThirdParty", "MyExampleThirdParty", "Win64", "ExampleLibrary.dll"));
		}
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "Release", "libExampleLibrary.dylib"));
            RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/MyExampleThirdParty/Mac/Release/libExampleLibrary.dylib");
        }
	}
}
