#pragma once

#include "Engine.h"

#include "GenericPlatformFile.h"

class SHADERCOPYHELPER_API FShaderFileVisitor : public IPlatformFile::FDirectoryVisitor
{
public:
	FShaderFileVisitor();

public:
	virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override;

public:
	void Reset();

	TArray<FString> ShaderFilePaths;
};