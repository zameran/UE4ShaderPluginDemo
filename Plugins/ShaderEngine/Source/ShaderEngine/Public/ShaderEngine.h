#pragma once

#include "ModuleManager.h"

#include "CoreUObject.h"
#include "Engine.h"

#include "ComputeShader/ComputeShaderDeclaration.h"
#include "ComputeShader/ComputeShaderUsageExample.h"
#include "CustomPixelShader/CustomPixelShaderDeclaration.h"
#include "CustomPixelShader/CustomPixelShaderUsageExample.h"
#include "PixelShader/PixelShaderDeclaration.h"
#include "PixelShader/PixelShaderUsageExample.h"

class SHADERENGINE_API FShaderEngineModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};