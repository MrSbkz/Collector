// Copyrights Plejady Team

using UnrealBuildTool;
using System.Collections.Generic;

public class CollectorTarget : TargetRules
{
	public CollectorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Collector" } );
	}
}
