// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealBasalEditorTarget : TargetRules
{
	public UnrealBasalEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "UnrealBasal" } );
		ExtraModuleNames.AddRange( new string[] { "UTGame" } );
        ExtraModuleNames.AddRange(new string[] { "UTCombat" });
        ExtraModuleNames.AddRange(new string[] { "UTFirstPerson" });
		// ExtraModuleNames.Add("UTTwinStick");
		ExtraModuleNames.AddRange(new string[] { "UTTwinStick" });
    }
}
