#pragma once

#include "SlateBasics.h"

#include "ShaderEngineEditorStyle.h"

class FShaderEngineEditorCommands : public TCommands<FShaderEngineEditorCommands>
{
public:

	FShaderEngineEditorCommands() : TCommands<FShaderEngineEditorCommands>(TEXT("ShaderEngineEditor"), NSLOCTEXT("Contexts", "ShaderEngineEditor", "ShaderEngineEditor Plugin"), NAME_None, FShaderEngineEditorStyle::GetStyleSetName())
	{

	}

	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};