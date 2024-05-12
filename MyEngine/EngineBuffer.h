#pragma once
#include "EngineDirectResource.h"

class EngineBuffer : public EngineDirectResource
{
public:
	// constructor destructor
	EngineBuffer();
	~EngineBuffer();

	// delete Function
	EngineBuffer(const EngineBuffer& _Other) = delete;
	EngineBuffer(EngineBuffer&& _Other) noexcept = delete;
	EngineBuffer& operator=(const EngineBuffer& _Other) = delete;
	EngineBuffer& operator=(EngineBuffer&& _Other) noexcept = delete;

protected:
	ID3D11Buffer* Buffer = nullptr;

	UINT Size = 0;
	UINT Count = 0;
	UINT Offset = 0;
};

