#pragma once
#include "EngineResource.h"
#include "EngineShader.h"

class EngineInputLayout;

class EngineVertexShader : public EngineResource<EngineVertexShader>, public EngineShader
{
	friend EngineDirectDevice;
	friend EngineInputLayout;
public:
	// constructor destructor
	EngineVertexShader();
	~EngineVertexShader();

	// delete Function
	EngineVertexShader(const EngineVertexShader& _Other) = delete;
	EngineVertexShader(EngineVertexShader&& _Other) noexcept = delete;
	EngineVertexShader& operator=(const EngineVertexShader& _Other) = delete;
	EngineVertexShader& operator=(EngineVertexShader&& _Other) noexcept = delete;

	static EngineVertexShader* Create(std::string_view _Name, std::string_view _PathString)
	{
		EngineVertexShader* Shader = CreateEngineResource(_Name);
		Shader->CreateDirectResource(_PathString);
		return Shader;
	}

protected:

private:
	ID3D11VertexShader* VertexShader = nullptr;

	void CreateDirectResource(std::string_view _PathString);
	void SetToPipeline() override;
};

