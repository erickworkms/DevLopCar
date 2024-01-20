//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

using UnrealBuildTool;

public class DevLopCar : ModuleRules
{
	public DevLopCar(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","UMG", "Slate", "SlateCore","NavigationSystem","PhysX","PhysXVehiclesEditor","PhysXCooking","RuntimePhysXCooking","PhysXVehicles","PhysXVehicleLib"});
	}
}
