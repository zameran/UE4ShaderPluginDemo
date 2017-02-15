#include "ShaderEngineEditor.h"

#include "SlateBasics.h"
#include "SlateExtras.h"

#include "ShaderCopyHelper.h"

#include "ShaderEngineEditorUtils.h"
#include "ShaderEngineEditorStyle.h"
#include "ShaderEngineEditorCommands.h"

#include "LevelEditor.h"

static const FName ShaderEngineEditorTabName("ShaderEngineEditor");

#define LOCTEXT_NAMESPACE "FShaderEngineEditorModule"

void FShaderEngineEditorModule::StartupModule()
{
	FShaderEngineEditorStyle::Initialize();
	FShaderEngineEditorStyle::ReloadTextures();

	FShaderEngineEditorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);
	PluginCommands->MapAction(FShaderEngineEditorCommands::Get().PluginAction, FExecuteAction::CreateRaw(this, &FShaderEngineEditorModule::PluginButtonClicked));

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);

		ToolbarExtender->AddToolBarExtension("Compile", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FShaderEngineEditorModule::AddToolbarExtension));

		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
		LevelEditorModule.GetGlobalLevelEditorActions()->Append(PluginCommands.ToSharedRef());
	}

	UE_LOG(ShaderEngineEditor, Log, TEXT("Shader Engine Editor Plugin loaded!"));
}

void FShaderEngineEditorModule::ShutdownModule()
{
	FShaderEngineEditorStyle::Shutdown();

	FShaderEngineEditorCommands::Unregister();

	UE_LOG(ShaderEngineEditor, Log, TEXT("Shader Engine Editor Plugin unloaded!"));
}

void FShaderEngineEditorModule::PluginButtonClicked()
{
	FShaderCopyHelperModule& ShaderCopyHelperModule = FModuleManager::GetModuleChecked<FShaderCopyHelperModule>("ShaderCopyHelper");
	{
		ShaderCopyHelperModule.PopShaders();
		ShaderCopyHelperModule.PushShaders();

		UShaderEngineEditorUtils::RecompileShadersConsoleCommand();
	}
}

void FShaderEngineEditorModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FShaderEngineEditorCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FShaderEngineEditorModule, ShaderEngineEditor)