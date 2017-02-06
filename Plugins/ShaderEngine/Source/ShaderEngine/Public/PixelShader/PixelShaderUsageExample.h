#pragma once

#include "Private/PixelShader/PixelShaderDeclaration.h"

/**
 * This class demonstrates how to use the pixel shader we have declared.
 * Most importantly which RHI functions are needed to call and how to get some interesting output.
 */
class SHADERENGINE_API FPixelShaderUsageExample
{
public:
	FPixelShaderUsageExample(FColor StartColor, ERHIFeatureLevel::Type ShaderFeatureLevel);
	~FPixelShaderUsageExample();

	/**
	 * Let the user change rendertarget during runtime if they want to.
	 * @param RenderTarget - This is the output rendertarget!
	 * @param InputTexture - This is a rendertarget that's used as a texture parameter to the shader :)
	 * @param EndColor - This will be set to the dynamic parameter buffer each frame
	 * @param TextureParameterBlendFactor - The scalar weight that decides how much of the texture to blend
	 */
	void ExecutePixelShader(UTextureRenderTarget2D* RenderTarget, FTexture2DRHIRef InputTexture, FColor EndColor, float TextureParameterBlendFactor);

	/** Only execute this from the render thread! */
	void ExecutePixelShaderInternal();

	/** Save a screenshot of the target to the project saved folder. */
	void Save()
	{
		bSave = true;
	}

private:
	bool bIsPixelShaderExecuting;
	bool bMustRegenerateSRV;
	bool bIsUnloading;
	bool bSave;

	FPixelShaderConstantParameters ConstantParameters;
	FPixelShaderVariableParameters VariableParameters;
	ERHIFeatureLevel::Type FeatureLevel;

	/** Main texture */
	FTexture2DRHIRef CurrentTexture;
	FTexture2DRHIRef TextureParameter;
	UTextureRenderTarget2D* CurrentRenderTarget;

	/** Since we are only reading from the resource, we do not need a UAV; an SRV is sufficient */
	FShaderResourceViewRHIRef TextureParameterSRV;

	void SaveScreenshot(FRHICommandListImmediate& RHICmdList);
};