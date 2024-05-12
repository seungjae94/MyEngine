#pragma once
#include "EngineResource.h"
#include "EngineDirectResource.h"

class EngineDirectDevice;
class EngineVertexBuffer;
class EngineVertexShader;

class EngineInputLayout : public EngineResource<EngineInputLayout>, public EngineDirectResource
{
	friend EngineDirectDevice;
public:
	// constructor destructor
	EngineInputLayout();
	~EngineInputLayout();

	// delete Function
	EngineInputLayout(const EngineInputLayout& _Other) = delete;
	EngineInputLayout(EngineInputLayout&& _Other) noexcept = delete;
	EngineInputLayout& operator=(const EngineInputLayout& _Other) = delete;
	EngineInputLayout& operator=(EngineInputLayout&& _Other) noexcept = delete;

	static EngineInputLayout* Create(EngineVertexBuffer* _VertexBuffer, EngineVertexShader* _VertexShader);

protected:

private:
	ID3D11InputLayout* InputLayout = nullptr;
	ID3DBlob* VSCodeBlob = nullptr;

	void CreateDirectResource(std::vector<D3D11_INPUT_ELEMENT_DESC>* _Descs);
	void SetToPipeline() override;
};

