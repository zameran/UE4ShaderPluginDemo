using UnrealBuildTool;

public class ShaderEngineEditor : ModuleRules
{
    public ShaderEngineEditor(TargetInfo Target)
    {

        PublicIncludePaths.AddRange(
            new string[]
            {
                "ShaderEngineEditor/Public"
            }
        );


        PrivateIncludePaths.AddRange(
            new string[]
            {
                "ShaderEngineEditor/Private",
            }
        );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Projects",
                "InputCore",
                "UnrealEd",
                "LevelEditor",
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