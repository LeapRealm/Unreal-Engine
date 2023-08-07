// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Framework : ModuleRules
{
	public Framework(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"EnhancedInput",
			"GameplayTags",
			"UMG",
			"Niagara",
		});
		
		PrivateIncludePaths.AddRange(new string[]
		{
			"Framework/",
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
