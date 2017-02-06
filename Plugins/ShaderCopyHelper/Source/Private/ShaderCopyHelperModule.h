#pragma once

#include "ModuleManager.h"
#include "ShaderFileVisitor.h"

class FShaderCopyHelperModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	FShaderFileVisitor* ShaderFiles;
};