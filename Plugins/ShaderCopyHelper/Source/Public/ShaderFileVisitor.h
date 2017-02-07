#pragma once

#include "Engine.h"
#include "GenericPlatformFile.h"

class FShaderFileVisitor : public IPlatformFile::FDirectoryVisitor
{
public:
	FShaderFileVisitor();

public:
	virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override;

public:
	void Reset();

	TArray<FString> ShaderFilePaths;
};