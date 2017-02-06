using UnrealBuildTool;

using System.Collections.Generic;

public class ShaderPluginDemoTarget : TargetRules
{
    public ShaderPluginDemoTarget(TargetInfo Target)
    {
        Type = TargetType.Game;
    }
    public override void SetupBinaries(TargetInfo Target, ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations, ref List<string> OutExtraModuleNames)
    {
        OutExtraModuleNames.Add("ShaderPluginDemo");
    }
}