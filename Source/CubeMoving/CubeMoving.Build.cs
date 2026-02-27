// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CubeMoving : ModuleRules
{
	public CubeMoving(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"NavigationSystem",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"Niagara",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"CubeMoving",
			"CubeMoving/Variant_Strategy",
			"CubeMoving/Variant_Strategy/UI",
			"CubeMoving/Variant_TwinStick",
			"CubeMoving/Variant_TwinStick/AI",
			"CubeMoving/Variant_TwinStick/Gameplay",
			"CubeMoving/Variant_TwinStick/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
