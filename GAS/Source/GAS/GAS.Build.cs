// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class GAS : ModuleRules
{
	public GAS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"EnhancedInput",
		});
		
		PrivateIncludePaths.AddRange(new string[]
		{
			"GAS/",
			"GAS/Controller/",
			"GAS/Creature/",
			"GAS/Game/",
			"GAS/Interface/"
		});
	}
}
