#pragma once

#include "ModuleManager.h"

#include "CoreUObject.h"
#include "Engine.h"

#include "ShaderFileVisitor.h"

class SHADERCOPYHELPER_API FShaderCopyHelperModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void PushShaders();
	void PopShaders();

	DECLARE_EVENT(FShaderCopyHelperModule, FShadersPushed)
	FShadersPushed& OnShadersPushed() { return OnShadersPushedEvent; }

	DECLARE_EVENT(FShaderCopyHelperModule, FShadersPoped)
	FShadersPoped& OnShadersPoped() { return OnShadersPopedEvent; }

private:
	FShaderFileVisitor* ShaderFiles;
	FShadersPushed OnShadersPushedEvent;
	FShadersPoped OnShadersPopedEvent;
};