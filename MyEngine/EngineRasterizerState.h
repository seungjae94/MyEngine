#pragma once
#include "EngineResource.h"
#include "EngineDirectResource.h"

class EngineRasterizerState : public EngineResource<EngineRasterizerState>, public EngineDirectResource
{
	friend EngineDirectDevice;
public:
	// constructor destructor
	EngineRasterizerState();
	~EngineRasterizerState();

	// delete Function
	EngineRasterizerState(const EngineRasterizerState& _Other) = delete;
	EngineRasterizerState(EngineRasterizerState&& _Other) noexcept = delete;
	EngineRasterizerState& operator=(const EngineRasterizerState& _Other) = delete;
	EngineRasterizerState& operator=(EngineRasterizerState&& _Other) noexcept = delete;

	static EngineRasterizerState* Create(std::string_view _Name, D3D11_RASTERIZER_DESC _Desc);

protected:

private:
	ID3D11RasterizerState* RasterizerState = nullptr;

	void CreateDirectResource(D3D11_RASTERIZER_DESC _Desc);
	void SetToPipeline() override;
};

