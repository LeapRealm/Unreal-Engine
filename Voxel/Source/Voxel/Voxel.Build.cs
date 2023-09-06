// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Voxel : ModuleRules
{
	public Voxel(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"EnhancedInput",
			"ProceduralMeshComponent",
			"FastNoise",
			"FastNoiseGenerator",
		});
		
		PrivateIncludePaths.AddRange(new string[]
		{
			"Voxel",
		});
	}
}
