#pragma once

#include "ModuleManager.h"

class FToolBarBuilder;

class SHADERENGINEEDITOR_API FShaderEngineEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void PluginButtonClicked();

private:
	void AddToolbarExtension(FToolBarBuilder& Builder);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};