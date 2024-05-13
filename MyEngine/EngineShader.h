#pragma once
#include "EngineDirectResource.h"

enum class ShaderType
{
	VertexShader,
	PixelShader,
};

class EngineShader : public EngineDirectResource
{
public:
	// constructor destructor
	EngineShader();
	~EngineShader();

	// delete Function
	EngineShader(const EngineShader& _Other) = delete;
	EngineShader(EngineShader&& _Other) noexcept = delete;
	EngineShader& operator=(const EngineShader& _Other) = delete;
	EngineShader& operator=(EngineShader&& _Other) noexcept = delete;

protected:
	ID3DBlob* CodeBlob = nullptr;
	ID3DBlob* ErrorBlob = nullptr;
private:
};

