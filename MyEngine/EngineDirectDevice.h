#pragma once

class EngineCore;
class EngineDirectResource;
class EngineInputLayout;

class EngineDirectDevice
{
	friend EngineCore;
	friend EngineDirectResource;
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
	void Present();

private:
	// IA 府家胶
	EngineInputLayout* CharacterInputLayout = nullptr;
	EngineInputLayout* MonsterInputLayout = nullptr;

	// RS 府家胶
	D3D11_VIEWPORT ViewPort = {};

	// PS 府家胶
	ID3D11ShaderResourceView* CharacterTextureSRV = nullptr;
	ID3D11ShaderResourceView* MonsterTextureSRV = nullptr;

	void TestRenderCharacter();
	void TestRenderMonster();
};

