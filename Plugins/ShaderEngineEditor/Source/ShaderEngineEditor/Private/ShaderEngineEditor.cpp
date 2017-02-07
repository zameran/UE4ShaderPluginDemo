#include "ShaderEngineEditor.h"

#include "SlateBasics.h"
#include "SlateExtras.h"

#include "ShaderEngineEditorStyle.h"
#include "ShaderEngineEditorCommands.h"

#include "LevelEditor.h"

static const FName ShaderEngineEditorTabName("ShaderEngineEditor");

#define LOCTEXT_NAMESPACE "FShaderEngineEditorModule"

DEFINE_LOG_CATEGORY_STATIC(ShaderEngineEditor, Log, All)

void FShaderEngineEditorModule::StartupModule()
{
	FShaderEngineEditorStyle::Initialize();
	FShaderEngineEditorStyle::ReloadTextures();

	FShaderEngineEditorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);
	PluginCommands->MapAction(FShaderEngineEditorCommands::Get().PluginAction, FExecuteAction::CreateRaw(this, &FShaderEngineEditorModule::PluginButtonClicked), FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);

		ToolbarExtender->AddToolBarExtension("Compile", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FShaderEngineEditorModule::AddToolbarExtension));

		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
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
	FText DialogText = FText::Format(LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
					   FText::FromString(TEXT("FShaderEngineEditorModule::PluginButtonClicked()")),
					   FText::FromString(TEXT("ShaderEngineEditor.cpp")));

	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FShaderEngineEditorModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FShaderEngineEditorCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FShaderEngineEditorModule, ShaderEngineEditor)