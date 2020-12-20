// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class DemoBlack : ModuleRules
{
	public DemoBlack(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
                Path.Combine( ModuleDirectory, "..", "..", "..", "..", "Source", "unreal_basal", "Public"),
                Path.Combine( ModuleDirectory, "..", "..", "..", "..", "Source", "unreal_basal"),
                Path.Combine( ModuleDirectory, "..", "..", "..", "DemoThirdPartyLibrary", "Source", "ThirdParty", "DemoThirdPartyLibraryLibrary" ),
            }
			);

        // PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "..", "..", "..", "..", "Intermediate", "Build", "Win64", "UE4Editor", "Development", "unreal_basal", "UE4Editor-unreal_basal.lib"));


        PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
            }
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
                "unreal_basal",
                "DemoThirdPartyLibraryLibrary"
            }
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...
            }
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
            }
			);
	}
}
