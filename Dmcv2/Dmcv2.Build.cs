// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Dmcv2 : ModuleRules
{
	public Dmcv2(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "AITestSuite" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara", "NiagaraCore" });
	}
}
