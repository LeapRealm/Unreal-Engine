using UnrealBuildTool;

public class L1Game : ModuleRules
{
	public L1Game(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"GameplayTags",
			"ModularGameplay",
			"GameFeatures"
		});
		
		PrivateIncludePaths.AddRange(new string[]
		{
			"L1Game"
		});
	}
}
