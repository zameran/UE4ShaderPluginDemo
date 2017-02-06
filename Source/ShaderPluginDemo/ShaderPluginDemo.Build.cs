using UnrealBuildTool;

public class ShaderPluginDemo : ModuleRules
{
    public ShaderPluginDemo(TargetInfo Target)
    {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "RHI" });

        PublicDependencyModuleNames.AddRange(new string[] { "ShaderEngine" });
    }
}