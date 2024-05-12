#pragma once
#include "EngineResource.h"

class EngineDirectDevice;

class EngineDirectResource
{
public:
	// constructor destructor
	EngineDirectResource();
	virtual ~EngineDirectResource();

	// delete Function
	EngineDirectResource(const EngineDirectResource& _Other) = delete;
	EngineDirectResource(EngineDirectResource&& _Other) noexcept = delete;
	EngineDirectResource& operator=(const EngineDirectResource& _Other) = delete;
	EngineDirectResource& operator=(EngineDirectResource&& _Other) noexcept = delete;

protected:
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();
private:
	virtual void SetToPipeline() = 0;
};

