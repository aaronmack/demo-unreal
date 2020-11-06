// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class terrain_example : ModuleRules
{
	public terrain_example(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
