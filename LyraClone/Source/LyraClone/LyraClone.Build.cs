using UnrealBuildTool;

public class LyraClone : ModuleRules
{
	public LyraClone(ReadOnlyTargetRules Target) : base(Target)
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
			"GameFeatures",
			"EnhancedInput",
			"CommonUser",
		});
	}
}
