namespace UnrealBuildTool.Rules
{
	public class CustomPixelShader : ModuleRules
	{
		public CustomPixelShader(TargetInfo Target)
        {
            PrivateIncludePaths.AddRange(
                new string[] {
					"CustomPixelShader/Private"
				}
                );

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
                    "Engine",
                    "RenderCore",
                    "ShaderCore",
                    "RHI"
				}
				);
		}
	}
}