#include "ShaderEngineEditor.h"
#include "ShaderEngineEditorUtils.h"

#include "Editor.h"

void UShaderEngineEditorUtils::RecompileShadersConsoleCommand()
{
	GEngine->Exec(GEditor->GetEditorWorldContext().World(), TEXT("RecompileShaders Changed"));

	// NOTE : Alternative way...
	//GEngine->Exec(GEditor->GetWorld(), TEXT("RecompileShaders Changed"));
}