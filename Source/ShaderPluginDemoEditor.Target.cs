using UnrealBuildTool;

using System.Collections.Generic;

public class ShaderPluginDemoEditorTarget : TargetRules
{
    public ShaderPluginDemoEditorTarget(TargetInfo Target)
    {
        Type = TargetType.Editor;
    }

    public override void SetupBinaries(TargetInfo Target, ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations, ref List<string> OutExtraModuleNames)
    {
        OutExtraModuleNames.Add("ShaderPluginDemo");
    }
}