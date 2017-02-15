using UnrealBuildTool;

public class ShaderEngine : ModuleRules
{
	public ShaderEngine(TargetInfo Target)
	{
		PublicIncludePaths.AddRange(
			new string[] 
			{
				"ShaderEngine/Public"
			}
		);


		PrivateIncludePaths.AddRange(
			new string[] 
			{
				"ShaderEngine/Private",
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"RenderCore",
				"ShaderCore",
				"RHI"
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			}
		);

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{

			}
		);
	}
}