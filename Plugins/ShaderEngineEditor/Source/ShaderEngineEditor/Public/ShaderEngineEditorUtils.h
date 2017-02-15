#pragma once

#include "UObject/NoExportTypes.h"

#include "ShaderEngineEditorUtils.generated.h"

UCLASS()
class SHADERENGINEEDITOR_API UShaderEngineEditorUtils : public UObject
{
	GENERATED_BODY()

public:
	static void RecompileShadersConsoleCommand();
};