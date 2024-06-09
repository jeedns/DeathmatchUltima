// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DeathmatchUltima : ModuleRules
{
	public DeathmatchUltima(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
