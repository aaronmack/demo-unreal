// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealBasalTarget : TargetRules
{
	public UnrealBasalTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "UnrealBasal" } );
		ExtraModuleNames.AddRange( new string[] { "UTGame" } );
        ExtraModuleNames.AddRange(new string[] { "UTCombat" });
        ExtraModuleNames.AddRange(new string[] { "UTFirstPerson" });

    }
}
