// Copyrights Plejady Team

using UnrealBuildTool;
using System.Collections.Generic;

public class CollectorEditorTarget : TargetRules
{
	public CollectorEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Collector" } );
	}
}
