// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealBasalTarget : TargetRules
{
	public UnrealBasalTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		//LaunchModuleName = "UnrealBasal";
		
		ExtraModuleNames.AddRange( new string[] { "UnrealBasal" } );
		ExtraModuleNames.AddRange( new string[] { "UTGame" } );
        ExtraModuleNames.AddRange(new string[] { "UTCombat" });
        ExtraModuleNames.AddRange(new string[] { "UTFirstPerson" });
		// ExtraModuleNames.Add("UTTwinStick");
		ExtraModuleNames.AddRange(new string[] { "UTTwinStick" });
		
		//GlobalDefinitions.Add("UE_LIBRARY_ENABLED=1");
		//LinkType = TargetLinkType.Monolithic;
		//bShouldCompileAsDLL = true;
		//ExtraModuleNames.AddRange(new string[] { "UELibrary" });
    }
}
