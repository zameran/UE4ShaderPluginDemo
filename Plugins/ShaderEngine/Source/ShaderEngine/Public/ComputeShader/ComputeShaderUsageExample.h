#pragma once

#include "Private/ComputeShader/ComputeShaderDeclaration.h"

/**
 * This class demonstrates how to use the compute shader we have declared.
 * Most importantly which RHI functions are needed to call and how to get some interesting output.
 */
class SHADERENGINE_API FComputeShaderUsageExample
{
public:
	FComputeShaderUsageExample(float SimulationSpeed, int32 SizeX, int32 SizeY, ERHIFeatureLevel::Type ShaderFeatureLevel);
	~FComputeShaderUsageExample();

	/**
	 * Run this to execute the compute shader once!
	 * @param TotalElapsedTimeSeconds - We use this for simulation state. 
	 */
	void ExecuteComputeShader(float TotalElapsedTimeSeconds);
	/** Only execute this from the render thread! */
	void ExecuteComputeShaderInternal();
	/** Save a screenshot of the target to the project saved folder. */
	void Save()
	{
		bSave = true;
	}

	FTexture2DRHIRef GetTexture() { return Texture; }

private:
	bool bIsComputeShaderExecuting;
	bool bIsUnloading;
	bool bSave;

	FComputeShaderConstantParameters ConstantParameters;
	FComputeShaderVariableParameters VariableParameters;
	ERHIFeatureLevel::Type FeatureLevel;

	/** Main texture */
	FTexture2DRHIRef Texture;

	/** We need a UAV if we want to be able to write to the resource*/
	FUnorderedAccessViewRHIRef TextureUAV;

	void SaveScreenshot(FRHICommandListImmediate& RHICmdList);
};