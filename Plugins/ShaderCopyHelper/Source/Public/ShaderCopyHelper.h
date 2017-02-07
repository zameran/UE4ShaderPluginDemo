#pragma once

#include "ModuleManager.h"

#include "CoreUObject.h"
#include "Engine.h"

#include "ShaderFileVisitor.h"

class FShaderCopyHelperModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void PushShaders();
	void PopShaders();

private:
	FShaderFileVisitor* ShaderFiles;
};