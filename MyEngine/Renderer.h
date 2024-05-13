#pragma once
#include "Component.h"

class Level;
class EngineVertexBuffer;
class EngineIndexBuffer;
class EngineInputLayout;
class EngineVertexShader;
class EngineRasterizerState;
class EnginePixelShader;
class EngineTexture;
class EngineSamplerState;
class EngineBlendState;
class EngineConstantBuffer;
enum class ShaderType;

class Renderer : public Component, public std::enable_shared_from_this<Renderer>
{
	friend Level;
public:
	// constructor destructor
	Renderer();
	~Renderer();

	// delete Function
	Renderer(const Renderer& _Other) = delete;
	Renderer(Renderer&& _Other) noexcept = delete;
	Renderer& operator=(const Renderer& _Other) = delete;
	Renderer& operator=(Renderer&& _Other) noexcept = delete;

	void SetTexture(std::string_view _Name);

protected:
	void BeginPlay() override;
	virtual void Render();
private:
	EngineVertexBuffer* VertexBuffer = nullptr;
	EngineIndexBuffer* IndexBuffer = nullptr;
	EngineInputLayout* InputLayout = nullptr;
	EngineVertexShader* VertexShader = nullptr;
	EngineRasterizerState* RasterizerState = nullptr;
	EnginePixelShader* PixelShader = nullptr;
	EngineTexture* Texture = nullptr;
	EngineSamplerState* SamplerState = nullptr;
	EngineBlendState* BlendState = nullptr;

	//std::map<ShaderType, std::map<std::string, EngineConstantBuffer>> ConstantBuffers;
};

