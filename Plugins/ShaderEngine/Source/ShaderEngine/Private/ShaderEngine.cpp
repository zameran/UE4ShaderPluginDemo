#include "ShaderEngine.h"

#define LOCTEXT_NAMESPACE "FShaderEngineModule"

DEFINE_LOG_CATEGORY_STATIC(ShaderEngine, Log, All)

void FShaderEngineModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(ShaderEngine, Log, TEXT("Shader Engine Plugin loaded!"));
}

void FShaderEngineModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UE_LOG(ShaderEngine, Log, TEXT("Shader Engine Plugin unloaded!"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FShaderEngineModule, ShaderEngine)