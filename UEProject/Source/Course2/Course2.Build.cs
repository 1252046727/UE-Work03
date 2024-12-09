// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Course2 : ModuleRules
{
	public Course2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "HeadMountedDisplay", "UMG", "Slate", "SlateCore" });
	}
}
