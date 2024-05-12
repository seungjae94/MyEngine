#pragma once

class EngineVertexBuffer;
class EngineIndexBuffer;
class EngineInputLayout;
class EngineVertexShader;
class EnginePixelShader;

class Renderer
{
public:
	// constructor destructor
	Renderer();
	~Renderer();

	// delete Function
	Renderer(const Renderer& _Other) = delete;
	Renderer(Renderer&& _Other) noexcept = delete;
	Renderer& operator=(const Renderer& _Other) = delete;
	Renderer& operator=(Renderer&& _Other) noexcept = delete;

protected:
	virtual void Render();
private:
	EngineVertexBuffer* VertexBuffer = nullptr;
	EngineIndexBuffer* IndexBuffer = nullptr;
	EngineInputLayout* InputLayout = nullptr;


};

