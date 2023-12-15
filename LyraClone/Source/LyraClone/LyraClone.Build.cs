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
			"EnhancedInput",
			"CommonUser",
			"GameFeatures",
			"ModularGameplay",
			"ModularGameplayActors",
		});
	}
}
