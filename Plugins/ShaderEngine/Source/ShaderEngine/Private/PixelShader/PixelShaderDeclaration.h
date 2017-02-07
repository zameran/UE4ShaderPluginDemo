#pragma once

#include "GlobalShader.h"
#include "UniformBuffer.h"
#include "RHICommandList.h"

// This buffer should contain variables that never, or rarely change
BEGIN_UNIFORM_BUFFER_STRUCT(FPixelShaderConstantParameters, )
DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FVector4, StartColor)
END_UNIFORM_BUFFER_STRUCT(FPixelShaderConstantParameters)

// This buffer is for variables that change very often (each frame for example)
BEGIN_UNIFORM_BUFFER_STRUCT(FPixelShaderVariableParameters, )
DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(float, TextureParameterBlendFactor)
DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FVector4, EndColor)
END_UNIFORM_BUFFER_STRUCT(FPixelShaderVariableParameters)

typedef TUniformBufferRef<FPixelShaderConstantParameters> FPixelShaderConstantParametersRef;
typedef TUniformBufferRef<FPixelShaderVariableParameters> FPixelShaderVariableParametersRef;

/**
 * This is the type we use as vertices for our fullscreen quad.
 */
struct FTextureVertex
{
	FVector4 Position;
	FVector2D UV;
};

/**
 * We define our vertex declaration to let us get our UV coords into the shader.
 */
class FTextureVertexDeclaration : public FRenderResource
{
public:
	FVertexDeclarationRHIRef VertexDeclarationRHI;

	virtual void InitRHI() override
	{
		FVertexDeclarationElementList Elements;

		uint32 Stride = sizeof(FTextureVertex);

		Elements.Add(FVertexElement(0, STRUCT_OFFSET(FTextureVertex, Position), VET_Float4, 0, Stride));
		Elements.Add(FVertexElement(0, STRUCT_OFFSET(FTextureVertex, UV), VET_Float2, 1, Stride));

		VertexDeclarationRHI = RHICreateVertexDeclaration(Elements);
	}

	virtual void ReleaseRHI() override
	{
		VertexDeclarationRHI.SafeRelease();
	}
};

/** A simple passthrough vertexshader that we will use. */
class FVertexShaderExample : public FGlobalShader
{
	DECLARE_SHADER_TYPE(FVertexShaderExample, Global)

public:
	static bool ShouldCache(EShaderPlatform Platform) { return true; }

	FVertexShaderExample(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FGlobalShader(Initializer)	{}
	FVertexShaderExample() {}
};


/**
 * This class is what encapsulates the shader in the engine.
 * It is the main bridge between the HLSL located in the engine directory and the engine itself.
 */
class FPixelShaderDeclaration : public FGlobalShader
{
	DECLARE_SHADER_TYPE(FPixelShaderDeclaration, Global)

public:
	FPixelShaderDeclaration() {}

	explicit FPixelShaderDeclaration(const ShaderMetaType::CompiledShaderInitializerType& Initializer);

	static bool ShouldCache(EShaderPlatform Platform) { return IsFeatureLevelSupported(Platform, ERHIFeatureLevel::SM5); }

	virtual bool Serialize(FArchive& Ar) override
	{
		bool bShaderHasOutdatedParams = FGlobalShader::Serialize(Ar);

		Ar << TextureParameter;

		return bShaderHasOutdatedParams;
	}

	/** This function is required to let us bind our runtime surface to the shader using an SRV. */
	void SetSurfaces(FRHICommandList& RHICmdList, FShaderResourceViewRHIRef TextureParameterSRV);
	/** This function is required to bind our constant / uniform buffers to the shader. */
	void SetUniformBuffers(FRHICommandList& RHICmdList, FPixelShaderConstantParameters& ConstantParameters, FPixelShaderVariableParameters& VariableParameters);
	/** This is used to clean up the buffer binds after each invocation to let them be changed and used elsewhere if needed. */
	void UnbindBuffers(FRHICommandList& RHICmdList);

private:
	/** This is how you declare resources that are going to be made available in the HLSL. */
	FShaderResourceParameter TextureParameter;
};