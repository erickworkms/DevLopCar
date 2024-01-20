//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

using UnrealBuildTool;
using System.Collections.Generic;

public class DevLopCarEditorTarget : TargetRules
{
	public DevLopCarEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("DevLopCar");
	}
}
