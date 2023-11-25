using UnrealBuildTool;

public class LyraCloneEditorTarget : TargetRules
{
	public LyraCloneEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("LyraClone");
	}
}
