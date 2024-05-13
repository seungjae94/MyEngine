#pragma once
#include "EngineResource.h"
#include "EngineDirectResource.h"

class Renderer;

class EngineTexture : public EngineResource<EngineTexture>, public EngineDirectResource
{
	friend Renderer;
public:
	// constructor destructor
	EngineTexture();
	~EngineTexture();

	// delete Function
	EngineTexture(const EngineTexture& _Other) = delete;
	EngineTexture(EngineTexture&& _Other) noexcept = delete;
	EngineTexture& operator=(const EngineTexture& _Other) = delete;
	EngineTexture& operator=(EngineTexture&& _Other) noexcept = delete;

	static EngineTexture* Create(const EnginePath& _Path);
protected:

private:
	ID3D11ShaderResourceView* SRV = nullptr;

	void CreateDirectResource(std::string_view _PathString);
	void SetToPipeline() override;
};

