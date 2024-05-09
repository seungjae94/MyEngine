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
	void CreateVertexShaders();
	void CreateRasterizerStates();
	void CreatePixelShaders();
	void CreateInputLayout();

	void ClearBackBuffer();
	void Present();

private:
	// IA 府家胶
	ID3D11Buffer* TriangleVertexBuffer = nullptr;
	ID3D11Buffer* TriangleIndexBuffer = nullptr;
	ID3D11InputLayout* TriangleInputLayout = nullptr;
	UINT VertexSize = 0;
	UINT VertexOffset = 0;
	UINT IndexOffset = 0;

	// VS 府家胶
	ID3DBlob* VSCodeBlob = nullptr;
	ID3DBlob* VSErrorBlob = nullptr;
	ID3D11VertexShader* VertexShader = nullptr;

	// RS 府家胶
	ID3D11RasterizerState* RasterizerState = nullptr;
	D3D11_VIEWPORT ViewPort;

	// PS 府家胶
	ID3DBlob* PSCodeBlob = nullptr;
	ID3DBlob* PSErrorBlob = nullptr;
	ID3D11PixelShader* PixelShader = nullptr;

	void TestRenderTriangle();
};

