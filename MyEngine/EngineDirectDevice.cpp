#include "PreCompile.h"
#include "EngineDirectDevice.h"

EngineDirectDevice::EngineDirectDevice()
{
}

EngineDirectDevice::~EngineDirectDevice()
{
	Device->Release();
	Context->Release();
	SwapChain->Release();
}

void EngineDirectDevice::Init(HWND _hWnd)
{
	UINT Flags = 0;
#ifdef _DEBUG
	Flags = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL FeatureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL FeatureLevel;
	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	ZeroMemory(&SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	SwapChainDesc.BufferCount = 2;	// 더블 버퍼링 사용
	SwapChainDesc.BufferDesc.Width = 1280;	// 백버퍼 너비
	SwapChainDesc.BufferDesc.Height = 720;	// 백버퍼 높이
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// RGBA, 0에서 1사이의 값
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;	// 주사율 분자
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;	// 주사율 분모
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.OutputWindow = _hWnd;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	SwapChainDesc.Windowed = TRUE;

	HRESULT Result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		Flags,
		&FeatureLevels,
		1,
		D3D11_SDK_VERSION,
		&SwapChainDesc,
		&SwapChain,
		&Device,
		&FeatureLevel,
		&Context);

	if (S_OK != Result)
	{
		MessageBoxAssert("디바이스 생성에 실패했습니다.");
		return;
	}

	ID3D11Texture2D* BackBufferTexture = nullptr;
	Result = SwapChain->GetBuffer(0, _uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBufferTexture));

	if (S_OK != Result)
	{
		MessageBoxAssert("백버퍼 텍스쳐를 가져오지 못했습니다.");
		return;
	}

	D3D11_TEXTURE2D_DESC BackBufferTextureDesc;
	BackBufferTexture->GetDesc(&BackBufferTextureDesc);

	ID3D11RenderTargetView* RTV = nullptr;
	Result = Device->CreateRenderTargetView(BackBufferTexture, nullptr, &RTV);

	float ClearColor[4];
	ClearColor[2] = 1.0f;
	Context->ClearRenderTargetView(RTV, ClearColor);

	SwapChain->Present(0, 0);

	BackBufferTexture->Release();
	RTV->Release();
}
