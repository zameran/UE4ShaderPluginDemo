#include "ShaderEngineEditor.h"
#include "ShaderEngineEditorCommands.h"

#define LOCTEXT_NAMESPACE "FShaderEngineEditorModule"

void FShaderEngineEditorCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "Push Shaders", "Copy shaders from project directory to the engine directory.", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE