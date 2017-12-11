#include "ShaderEngine.h"
#include "RHIStaticStates.h"

// It seems to be the convention to expose all vertex declarations as globals, and then reference them as externs in the headers where they are needed.
// It kind of makes sense since they do not contain any parameters that change and are purely used as their names suggest, as declarations :)
TGlobalResource<FCustomTextureVertexDeclaration> GCPSTextureVertexDeclaration;

FCustomPixelShaderUsageExample::FCustomPixelShaderUsageExample(FColor StartColor, ERHIFeatureLevel::Type ShaderFeatureLevel)
{
	FeatureLevel = ShaderFeatureLevel;

	ConstantParameters = FCustomPixelShaderConstantParameters();
	ConstantParameters.StartColor = FVector4(StartColor.R / 255.0, StartColor.G / 255.0, StartColor.B / 255.0, StartColor.A / 255.0);
	
	VariableParameters = FCustomPixelShaderVariableParameters();
	
	bMustRegenerateSRV = false;
	bIsPixelShaderExecuting = false;
	bIsUnloading = false;
	bSave = false;

	CurrentTexture = NULL;
	CurrentRenderTarget = NULL;
	TextureParameterSRV = NULL;
}

FCustomPixelShaderUsageExample::~FCustomPixelShaderUsageExample()
{
	bIsUnloading = true;
}

void FCustomPixelShaderUsageExample::ExecutePixelShader(UTextureRenderTarget2D* RenderTarget, FTexture2DRHIRef InputTexture, FColor EndColor, float TextureParameterBlendFactor)
{
	// Skip this execution round if we are already executing.
	if (bIsUnloading || bIsPixelShaderExecuting)
	{
		return;
	}

	bIsPixelShaderExecuting = true;

	if (TextureParameter != InputTexture)
	{
		bMustRegenerateSRV = true;
	}

	//Now set our runtime parameters!
	VariableParameters.EndColor = FVector4(EndColor.R / 255.0, EndColor.G / 255.0, EndColor.B / 255.0, EndColor.A / 255.0);
	VariableParameters.TextureParameterBlendFactor = TextureParameterBlendFactor;

	CurrentRenderTarget = RenderTarget;
	TextureParameter = InputTexture;

	// This macro sends the function we declare inside to be run on the render thread. 
	// What we do is essentially just send this class and tell the render thread to run the internal render function as soon as it can.
	// I am still not 100% Certain on the thread safety of this, if you are getting crashes, depending on how advanced code you have in the start of the ExecutePixelShader function, 
	// you might have to use a lock :)
	ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(FPixelShaderRunner, FCustomPixelShaderUsageExample*, PixelShader, this,
	{
		PixelShader->ExecutePixelShaderInternal();
	});
}

void FCustomPixelShaderUsageExample::ExecutePixelShaderInternal()
{
	check(IsInRenderingThread());

	// If we are about to unload, so just clean up the SRV :)
	if (bIsUnloading)
	{
		if (NULL != TextureParameterSRV)
		{
			TextureParameterSRV.SafeRelease();
			TextureParameterSRV = NULL;
		}

		return;
	}

	FRHICommandListImmediate& RHICmdList = GRHICommandList.GetImmediateCommandList();

	// If our input texture reference has changed, we need to recreate our SRV
	if (bMustRegenerateSRV)
	{
		bMustRegenerateSRV = false;

		if (NULL != TextureParameterSRV)
		{
			TextureParameterSRV.SafeRelease();
			TextureParameterSRV = NULL;
		}

		TextureParameterSRV = RHICreateShaderResourceView(TextureParameter, 0);
	}

	// This is where the magic happens
	CurrentTexture = CurrentRenderTarget->GetRenderTargetResource()->GetRenderTargetTexture();
	SetRenderTarget(RHICmdList, CurrentTexture, FTextureRHIRef());
	RHICmdList.SetBlendState(TStaticBlendState<>::GetRHI());
	RHICmdList.SetRasterizerState(TStaticRasterizerState<>::GetRHI());
	RHICmdList.SetDepthStencilState(TStaticDepthStencilState<false, CF_Always>::GetRHI());
	
	static FGlobalBoundShaderState BoundShaderState;
	TShaderMapRef<FCustomVertexShaderExample> VertexShader(GetGlobalShaderMap(FeatureLevel));
	TShaderMapRef<FCustomPixelShaderDeclaration> PixelShader(GetGlobalShaderMap(FeatureLevel));

	SetGlobalBoundShaderState(RHICmdList, FeatureLevel, BoundShaderState, GCPSTextureVertexDeclaration.VertexDeclarationRHI, *VertexShader, *PixelShader);

	PixelShader->SetSurfaces(RHICmdList, TextureParameterSRV);
	PixelShader->SetUniformBuffers(RHICmdList, ConstantParameters, VariableParameters);

	// Draw a fullscreen quad that we can run our pixel shader on
	FCustomTextureVertex Vertices[4];
	Vertices[0].Position = FVector4(-1.0f, 1.0f, 0, 1.0f);
	Vertices[1].Position = FVector4(1.0f, 1.0f, 0, 1.0f);
	Vertices[2].Position = FVector4(-1.0f, -1.0f, 0, 1.0f);
	Vertices[3].Position = FVector4(1.0f, -1.0f, 0, 1.0f);
	Vertices[0].UV = FVector2D(0, 0);
	Vertices[1].UV = FVector2D(1, 0);
	Vertices[2].UV = FVector2D(0, 1);
	Vertices[3].UV = FVector2D(1, 1);

	DrawPrimitiveUP(RHICmdList, PT_TriangleStrip, 2, Vertices, sizeof(Vertices[0]));
	
	PixelShader->UnbindBuffers(RHICmdList);
	
	// Save to disk if we have a save request!
	if (bSave)
	{
		bSave = false;

		SaveScreenshot(RHICmdList);
	}

	bIsPixelShaderExecuting = false;
}

void FCustomPixelShaderUsageExample::SaveScreenshot(FRHICommandListImmediate& RHICmdList)
{
	check(IsInRenderingThread());

	TArray<FColor> Bitmap;

	FReadSurfaceDataFlags ReadDataFlags;
	ReadDataFlags.SetLinearToGamma(false);
	ReadDataFlags.SetOutputStencil(false);
	ReadDataFlags.SetMip(0); // No mip supported ofc!

	// This is pretty straight forward. Since we are using a standard format, we can use this convenience function instead of having to lock rect.
	RHICmdList.ReadSurfaceData(CurrentTexture, FIntRect(0, 0, CurrentTexture->GetSizeX(), CurrentTexture->GetSizeY()), Bitmap, ReadDataFlags);

	// If the format and texture type is supported
	if (Bitmap.Num())
	{
		// Create screenshot folder if not already present.
		IFileManager::Get().MakeDirectory(*FPaths::ScreenShotDir(), true);

		const FString ScreenFileName(FPaths::ScreenShotDir() / TEXT("VisualizeTexture"));

		uint32 ExtendXWithMSAA = Bitmap.Num() / CurrentTexture->GetSizeY();

		// Save the contents of the array to a bitmap file. (24bit only so alpha channel is dropped)
		FFileHelper::CreateBitmap(*ScreenFileName, ExtendXWithMSAA, CurrentTexture->GetSizeY(), Bitmap.GetData());

		UE_LOG(LogConsoleResponse, Display, TEXT("Content was saved to \"%s\""), *FPaths::ScreenShotDir());
	}
	else
	{
		UE_LOG(LogConsoleResponse, Error, TEXT("Failed to save BMP, format or texture type is not supported"));
	}
}