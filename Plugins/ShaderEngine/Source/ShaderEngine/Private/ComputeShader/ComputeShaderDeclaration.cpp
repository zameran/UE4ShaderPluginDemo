#include "ShaderEngine.h"
#include "ShaderParameterUtils.h"

#include "RHIStaticStates.h"

// These are needed to actually implement the constant buffers so they are available inside our shader
// They also need to be unique over the entire solution since they can in fact be accessed from any shader
IMPLEMENT_UNIFORM_BUFFER_STRUCT(FComputeShaderConstantParameters, TEXT("CSConstants"))
IMPLEMENT_UNIFORM_BUFFER_STRUCT(FComputeShaderVariableParameters, TEXT("CSVariables"))

FComputeShaderDeclaration::FComputeShaderDeclaration(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FGlobalShader(Initializer)
{
	// This call is what lets the shader system know that the surface OutputSurface is going to be available in the shader. 
	// The second parameter is the name it will be known by in the shader
	OutputSurface.Bind(Initializer.ParameterMap, TEXT("OutputSurface"));
}

void FComputeShaderDeclaration::ModifyCompilationEnvironment(EShaderPlatform Platform, FShaderCompilerEnvironment& OutEnvironment)
{
	FGlobalShader::ModifyCompilationEnvironment(Platform, OutEnvironment);

	OutEnvironment.CompilerFlags.Add(CFLAG_StandardOptimization);
}

void FComputeShaderDeclaration::SetSurfaces(FRHICommandList& RHICmdList, FUnorderedAccessViewRHIRef OutputSurfaceUAV)
{
	FComputeShaderRHIParamRef ComputeShaderRHI = GetComputeShader();

	if (OutputSurface.IsBound())
		RHICmdList.SetUAVParameter(ComputeShaderRHI, OutputSurface.GetBaseIndex(), OutputSurfaceUAV);
}

void FComputeShaderDeclaration::SetUniformBuffers(FRHICommandList& RHICmdList, FComputeShaderConstantParameters& ConstantParameters, FComputeShaderVariableParameters& VariableParameters)
{
	FComputeShaderConstantParametersRef ConstantParametersBuffer;
	FComputeShaderVariableParametersRef VariableParametersBuffer;

	ConstantParametersBuffer = FComputeShaderConstantParametersRef::CreateUniformBufferImmediate(ConstantParameters, UniformBuffer_SingleDraw);
	VariableParametersBuffer = FComputeShaderVariableParametersRef::CreateUniformBufferImmediate(VariableParameters, UniformBuffer_SingleDraw);

	SetUniformBufferParameter(RHICmdList, GetComputeShader(), GetUniformBufferParameter<FComputeShaderConstantParameters>(), ConstantParametersBuffer);
	SetUniformBufferParameter(RHICmdList, GetComputeShader(), GetUniformBufferParameter<FComputeShaderVariableParameters>(), VariableParametersBuffer);
}

void FComputeShaderDeclaration::UnbindBuffers(FRHICommandList& RHICmdList)
{
	FComputeShaderRHIParamRef ComputeShaderRHI = GetComputeShader();

	if (OutputSurface.IsBound())
		RHICmdList.SetUAVParameter(ComputeShaderRHI, OutputSurface.GetBaseIndex(), FUnorderedAccessViewRHIRef());
}

// This is what will instantiate the shader into the engine from the engine/Shaders folder
/*                      ShaderClass                    SourceFilename                FunctionName			   Type   */
IMPLEMENT_SHADER_TYPE(, FComputeShaderDeclaration, TEXT("ComputeShaderExample"), TEXT("MainComputeShader"), SF_Compute);