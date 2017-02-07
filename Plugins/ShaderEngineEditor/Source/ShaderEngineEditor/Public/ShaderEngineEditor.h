#pragma once

#include "ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FShaderEngineEditorModule : public IModuleInterface
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