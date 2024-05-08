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

	void Init(HWND _hWnd);

};

