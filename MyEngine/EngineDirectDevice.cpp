#include "PreCompile.h"
#include "EngineDirectDevice.h"
#include "EngineVertex.h"

EngineDirectDevice::EngineDirectDevice()
{
	ViewPort.Width = 1280;
	ViewPort.Height = 720;
	ViewPort.TopLeftX = 0;
	ViewPort.TopLeftY = 0;
	ViewPort.MinDepth = 0;
	ViewPort.MaxDepth = 1;
}

EngineDirectDevice::~EngineDirectDevice()
{
	Device->Release();
	Context->Release();
	SwapChain->Release();
	BackBufferRTV->Release();
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
	SwapChainDesc.BufferCount = 2;	// ���� ���۸� ���
	SwapChainDesc.BufferDesc.Width = 1280;	// ����� �ʺ�
	SwapChainDesc.BufferDesc.Height = 720;	// ����� ����
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// RGBA, 0���� 1������ ��
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;	// �ֻ��� ����
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;	// �ֻ��� �и�
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.OutputWindow = _hWnd;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
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
		MessageBoxAssert("����̽� ������ �����߽��ϴ�.");
		return;
	}

	ID3D11Texture2D* BackBufferTexture = nullptr;
	Result = SwapChain->GetBuffer(0, _uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBufferTexture));

	if (S_OK != Result)
	{
		MessageBoxAssert("����� �ؽ��ĸ� �������� ���߽��ϴ�.");
		return;
	}

	Result = Device->CreateRenderTargetView(BackBufferTexture, nullptr, &BackBufferRTV);
	BackBufferTexture->Release();

	if (S_OK != Result)
	{
		MessageBoxAssert("����� ���� Ÿ�� �� ������ �����߽��ϴ�.");
		return;
	}

	CreateIAResources();
	CreateVertexShaders();
	CreateRasterizerStates();
	CreatePixelShaders();
	CreateInputLayout();
}

void EngineDirectDevice::CreateIAResources()
{
	{
		// �ﰢ�� ���ؽ� ���� ����
		std::vector<EngineVertex> Vertices;
		Vertices.resize(3);
		Vertices[0].Position = { 0.0f, 1.0f, 0.0f, 1.0f };
		Vertices[1].Position = { -0.75f, -0.5f, 0.0f, 1.0f };
		Vertices[2].Position = { 0.75f, -0.5f, 0.0f, 1.0f };

		VertexSize = sizeof(EngineVertex);

		D3D11_SUBRESOURCE_DATA BufferInitialData;
		BufferInitialData.pSysMem = &Vertices[0];

		D3D11_BUFFER_DESC BufferDesc;
		BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		BufferDesc.ByteWidth = VertexSize * Vertices.size();
		BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		BufferDesc.CPUAccessFlags = 0;

		Device->CreateBuffer(&BufferDesc, &BufferInitialData, &TriangleVertexBuffer);
	}

	{
		// �ﰢ�� �ε��� ���� ����
		std::vector<UINT> Indexes = { 0, 1, 2 };

		D3D11_SUBRESOURCE_DATA BufferInitialData;
		BufferInitialData.pSysMem = &Indexes[0];

		D3D11_BUFFER_DESC BufferDesc;
		BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		BufferDesc.ByteWidth = sizeof(UINT) * Indexes.size();
		BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		BufferDesc.CPUAccessFlags = 0;

		Device->CreateBuffer(&BufferDesc, &BufferInitialData, &TriangleIndexBuffer);
	}
}

void EngineDirectDevice::CreateVertexShaders()
{
	UINT Flag0 = D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
	UINT Flag1 = 0;
#ifdef _DEBUG
	Flag0 |= D3D10_SHADER_DEBUG;
#endif

	{
		HRESULT Result = D3DCompileFromFile(
			L"D:/MyEngine/MyEngineShader/ShapeShader.fx",
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"VSmain",
			"vs_5_0",
			Flag0,
			Flag1,
			&VSCodeBlob,
			&VSErrorBlob
		);

		if (S_OK != Result)
		{
			char* ErrorMessage = reinterpret_cast<char*>(VSErrorBlob->GetBufferPointer());
			MessageBoxAssert(ErrorMessage);
			return;
		}

		Result = Device->CreateVertexShader(
			VSCodeBlob->GetBufferPointer(),
			VSCodeBlob->GetBufferSize(),
			nullptr,
			&VertexShader
		);

		if (S_OK != Result)
		{
			MessageBoxAssert("���ؽ� ���̴� ������ �����߽��ϴ�.");
			return;
		}
	}
}

void EngineDirectDevice::CreateRasterizerStates()
{
	D3D11_RASTERIZER_DESC RasterizerDesc = {};
	RasterizerDesc.FillMode = D3D11_FILL_SOLID;
	RasterizerDesc.CullMode = D3D11_CULL_NONE;
	RasterizerDesc.AntialiasedLineEnable = TRUE;
	RasterizerDesc.DepthClipEnable = TRUE;

	Device->CreateRasterizerState(&RasterizerDesc, &RasterizerState);
}

void EngineDirectDevice::CreatePixelShaders()
{
	UINT Flag0 = D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
	UINT Flag1 = 0;
#ifdef _DEBUG
	Flag0 |= D3D10_SHADER_DEBUG;
#endif

	{
		HRESULT Result = D3DCompileFromFile(
			L"D:/MyEngine/MyEngineShader/ShapeShader.fx",
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"PSmain",
			"vs_5_0",
			Flag0,
			Flag1,
			&PSCodeBlob,
			&PSErrorBlob
		);

		if (S_OK != Result)
		{
			char* ErrorMessage = reinterpret_cast<char*>(PSErrorBlob->GetBufferPointer());
			MessageBoxAssert(ErrorMessage);
			return;
		}

		Result = Device->CreatePixelShader(
			PSCodeBlob->GetBufferPointer(),
			PSCodeBlob->GetBufferSize(),
			nullptr,
			&PixelShader
		);

		if (S_OK != Result)
		{
			MessageBoxAssert("�ȼ� ���̴� ������ �����߽��ϴ�.");
			return;
		}
	}
}

void EngineDirectDevice::CreateInputLayout()
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> InputElementDescs = {
		/*TODO*/
	};

	Device->CreateInputLayout(
		&InputElementDescs[0],
		InputElementDescs.size(),
		VSCodeBlob->GetBufferPointer(),
		VSCodeBlob->GetBufferSize(),
		&TriangleInputLayout
	);
}

void EngineDirectDevice::ClearBackBuffer()
{
	float ClearColor[4] = { 0.0f, 0.0f, 1.0f, 0.0f };
	Context->ClearRenderTargetView(BackBufferRTV, ClearColor);
}

void EngineDirectDevice::Present()
{
	HRESULT Result = SwapChain->Present(0, 0);
	if (Result != S_OK)
	{
		MessageBoxAssert("������Ʈ�� �����߽��ϴ�.");
	}
}

void EngineDirectDevice::TestRenderTriangle()
{
	Context->IASetVertexBuffers(0, 1, &TriangleVertexBuffer, &VertexSize, &VertexOffset);
	Context->IASetIndexBuffer(TriangleIndexBuffer, DXGI_FORMAT_R32_UINT, IndexOffset);
	Context->IASetInputLayout(TriangleInputLayout);
	Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Context->VSSetShader(VertexShader, nullptr, 0);
	Context->RSSetState(RasterizerState);
	Context->RSSetViewports(1, &ViewPort);
	Context->PSSetShader(PixelShader, nullptr, 0);
}
