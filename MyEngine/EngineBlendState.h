#pragma once
#include "EngineResource.h"
#include "EngineDirectResource.h"

class Renderer;

class EngineBlendState : public EngineResource<EngineBlendState>, public EngineDirectResource
{
	friend Renderer;
public:
	// constructor destructor
	EngineBlendState();
	~EngineBlendState();

	// delete Function
	EngineBlendState(const EngineBlendState& _Other) = delete;
	EngineBlendState(EngineBlendState&& _Other) noexcept = delete;
	EngineBlendState& operator=(const EngineBlendState& _Other) = delete;
	EngineBlendState& operator=(EngineBlendState&& _Other) noexcept = delete;

	static EngineBlendState* Create(std::string_view _Name, const D3D11_BLEND_DESC& _Desc);

protected:

private:
	ID3D11BlendState* BlendState = nullptr;

	void CreateDirectResource(const D3D11_BLEND_DESC& _Desc);
	void SetToPipeline() override;
};

