#pragma once

class EngineCore;

class EngineDirectDevice
{
	friend EngineCore;
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
	void ClearBackBuffer();
	void Present();

private:
	ID3D11Buffer* TriangleVertexBuffer = nullptr;
	ID3D11Buffer* TriangleIndexBuffer = nullptr;
	UINT VertexSize = 0;
	UINT VertexOffset = 0;
	UINT IndexOffset = 0;
	void TestRenderTriangle();
};

