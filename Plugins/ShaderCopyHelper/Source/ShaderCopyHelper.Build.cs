namespace UnrealBuildTool.Rules
{
    using System.IO;

    public class ShaderCopyHelper : ModuleRules
    {
        public ShaderCopyHelper(TargetInfo Target)
        {
            PublicDependencyModuleNames.AddRange(new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
            });
        }
    }
}