#pragma once
#include "EngineResource.h"
#include "EngineDirectResource.h"

class EngineSamplerState : public EngineResource<EngineSamplerState>, public EngineDirectResource
{
	friend EngineDirectDevice;
public:
	// constructor destructor
	EngineSamplerState();
	~EngineSamplerState();

	// delete Function
	EngineSamplerState(const EngineSamplerState& _Other) = delete;
	EngineSamplerState(EngineSamplerState&& _Other) noexcept = delete;
	EngineSamplerState& operator=(const EngineSamplerState& _Other) = delete;
	EngineSamplerState& operator=(EngineSamplerState&& _Other) noexcept = delete;

	static EngineSamplerState* Create(std::string_view _Name, const D3D11_SAMPLER_DESC& _Desc);

protected:

private:
	ID3D11SamplerState* SamplerState = nullptr;

	void CreateDirectResource(const D3D11_SAMPLER_DESC& _Desc);
	void SetToPipeline() override;
};

