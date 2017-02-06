#include "ShaderCopyHelperPrivatePCH.h" 
#include "Developer/DesktopPlatform/public/DesktopPlatformModule.h"
#include "GenericPlatformFile.h"
#include "PlatformFilemanager.h"

DEFINE_LOG_CATEGORY_STATIC(ShaderCopyHelper, Log, All)

void FShaderCopyHelperModule::StartupModule()
{
	UE_LOG(ShaderCopyHelper, Log, TEXT("Shader Copy Helper Plugin loaded!"));

	FString GameShadersDirectory = FPaths::Combine(*FPaths::GameDir(), TEXT("Shaders"));
	FString EngineShadersDirectory = FPaths::Combine(*FPaths::EngineDir(), TEXT("Shaders"));

	ShaderFiles = new FShaderFileVisitor();
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	PlatformFile.IterateDirectoryRecursively(*GameShadersDirectory, *ShaderFiles);
	
	UE_LOG(ShaderCopyHelper, Log, TEXT("Copying project shader files to Engine/Shaders/"));
	for (int32 ShaderFileIndex = 0; ShaderFileIndex < ShaderFiles->ShaderFilePaths.Num(); ShaderFileIndex++)
	{
		FString CurrentShaderFile = ShaderFiles->ShaderFilePaths[ShaderFileIndex];
		FString GameShaderFullPath = FPaths::Combine(*GameShadersDirectory, *CurrentShaderFile);
		FString EngineShaderFullPath = FPaths::Combine(*EngineShadersDirectory, *CurrentShaderFile);

		if (PlatformFile.CopyFile(*EngineShaderFullPath, *GameShaderFullPath))
		{
			UE_LOG(ShaderCopyHelper, Log, TEXT("Shader file %s copied to %s."), *GameShaderFullPath, *EngineShaderFullPath);
		}
		else
		{
			UE_LOG(ShaderCopyHelper, Warning, TEXT("Could not copy %s to %s!"), *GameShaderFullPath, *EngineShaderFullPath);
		}
	}
}

void FShaderCopyHelperModule::ShutdownModule()
{
	FString EngineShadersDirectory = FPaths::Combine(*FPaths::EngineDir(), TEXT("Shaders"));
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	UE_LOG(ShaderCopyHelper, Log, TEXT("Deleting project shaders from Engine/Shaders/"));
	for (int32 ShaderFileIndex = 0; ShaderFileIndex < ShaderFiles->ShaderFilePaths.Num(); ShaderFileIndex++)
	{
		FString EngineShaderFullPath = FPaths::Combine(*EngineShadersDirectory, *ShaderFiles->ShaderFilePaths[ShaderFileIndex]);

		if (PlatformFile.DeleteFile(*EngineShaderFullPath))
		{
			UE_LOG(ShaderCopyHelper, Log, TEXT("Shader file %s deleted."), *EngineShaderFullPath);
		}
		else
		{
			UE_LOG(ShaderCopyHelper, Warning, TEXT("Could not delete %s!"), *EngineShaderFullPath);
		}
	}

	delete ShaderFiles;

	UE_LOG(ShaderCopyHelper, Log, TEXT("Shader Copy Helper Plugin unloaded!"));
}

IMPLEMENT_MODULE(FShaderCopyHelperModule, ShaderCopyHelper)