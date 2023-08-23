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
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"ProceduralMeshComponent",
		});
		
		PrivateIncludePaths.AddRange(new string[]
		{
			"Voxel",
		});
	}
}
