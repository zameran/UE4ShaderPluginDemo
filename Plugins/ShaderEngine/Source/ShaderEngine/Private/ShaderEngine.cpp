#include "ShaderEngine.h"

#define LOCTEXT_NAMESPACE "FShaderEngineModule"

void FShaderEngineModule::StartupModule()
{
	UE_LOG(ShaderEngine, Log, TEXT("Shader Engine Plugin loaded!"));
}

void FShaderEngineModule::ShutdownModule()
{
	UE_LOG(ShaderEngine, Log, TEXT("Shader Engine Plugin unloaded!"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FShaderEngineModule, ShaderEngine)