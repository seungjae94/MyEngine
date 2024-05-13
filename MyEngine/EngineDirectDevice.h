#pragma once

class EngineCore;
class EngineDirectResource;
class Level;
class Renderer;

class EngineDirectDevice
{
	friend EngineCore;
	friend EngineDirectResource;
	friend Level;
	friend Renderer;
public:
	EngineDirectDevice();
	~EngineDirectDevice();

	EngineDirectDevice(const EngineDirectDevice& _Other) = delete;
	EngineDirectDevice(EngineDirectDevice&& _Other) noexcept = delete;
	EngineDirectDevice& operator=(const EngineDirectDevice& _Other) = delete;
	EngineDirectDevice& operator=(EngineDirectDevice&& _Other) noexcept = delete;

protected:


private:
	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* Context = nullptr;
	IDXGISwapChain* SwapChain = nullptr;
	ID3D11RenderTargetView* BackBufferRTV = nullptr;

	void Init(HWND _hWnd);
	void CreateIAResources();
	void CreateVSResources();
	void CreateRSResources();
	void CreatePSResources();
	void CreateOMResources();
	void CreateInputLayouts();

	void ClearBackBuffer();
	void SetBackBufferRenderTargets();
	void DrawIndexed(UINT _IndexBufferCount);
	void Present();
};

