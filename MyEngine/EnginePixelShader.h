#pragma once
#include "EngineResource.h"
#include "EngineShader.h"

class Renderer;

class EnginePixelShader : public EngineResource<EnginePixelShader>, public EngineShader
{
	friend Renderer;
public:
	// constructor destructor
	EnginePixelShader();
	~EnginePixelShader();

	// delete Function
	EnginePixelShader(const EnginePixelShader& _Other) = delete;
	EnginePixelShader(EnginePixelShader&& _Other) noexcept = delete;
	EnginePixelShader& operator=(const EnginePixelShader& _Other) = delete;
	EnginePixelShader& operator=(EnginePixelShader&& _Other) noexcept = delete;

	static EnginePixelShader* Create(std::string_view _Name, std::string_view _PathString)
	{
		EnginePixelShader* Shader = CreateEngineResource(_Name);
		Shader->CreateDirectResource(_PathString);
		return Shader;
	}

protected:

private:
	ID3D11PixelShader* PixelShader = nullptr;

	void CreateDirectResource(std::string_view _PathString);
	void SetToPipeline() override;
};

