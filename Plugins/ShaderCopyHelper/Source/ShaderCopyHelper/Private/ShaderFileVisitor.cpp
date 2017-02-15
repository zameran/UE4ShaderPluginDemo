#include "ShaderCopyHelper.h" 

FShaderFileVisitor::FShaderFileVisitor()
{
	ShaderFilePaths = TArray<FString>();
}

bool FShaderFileVisitor::Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory)
{
	if (!bIsDirectory)
	{
		ShaderFilePaths.Add(FPaths::GetCleanFilename(FilenameOrDirectory));
	}

	return true;
}

void FShaderFileVisitor::Reset()
{
	ShaderFilePaths.Empty();
}