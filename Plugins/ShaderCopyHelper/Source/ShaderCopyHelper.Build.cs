namespace UnrealBuildTool.Rules
{
    using System.IO;

    public class ShaderCopyHelper : ModuleRules
    {
        public ShaderCopyHelper(TargetInfo Target)
        {
            PublicIncludePaths.AddRange(
                new string[]
                {
                    "ShaderCopyHelper/Public"
                }
            );


            PrivateIncludePaths.AddRange(
                new string[]
                {
                    "ShaderCopyHelper/Private",
                }
            );

            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "InputCore",
                }
            );


            PrivateDependencyModuleNames.AddRange(
                new string[]
                {

                }
            );

            DynamicallyLoadedModuleNames.AddRange(
                new string[]
                {

                }
            );
        }
    }
}