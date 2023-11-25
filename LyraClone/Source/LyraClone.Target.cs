using UnrealBuildTool;

public class LyraCloneTarget : TargetRules
{
	public LyraCloneTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("LyraClone");
	}
}
