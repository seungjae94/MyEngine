#include "PreCompile.h"
#include "EngineDirectDevice.h"
#include "EngineVertex.h"

EngineDirectDevice::EngineDirectDevice()
{
}

EngineDirectDevice::~EngineDirectDevice()
{
	Device->Release();
	Context->Release();
	SwapChain->Release();
	BackBufferRTV->Release();
	VertexBuffer->Release();
	IndexBuffer->Release();
	InputLayout->Release();
	VSCodeBlob->Release();
	if (nullptr != VSErrorBlob)
	{
		VSErrorBlob->Release();
	}
	VertexShader->Release();
	RasterizerState->Release();
	PSCodeBlob->Release();
	if (nullptr != PSErrorBlob)
	{
		PSErrorBlob->Release();
	}
	PixelShader->Release();
	TextureSRV->Release();
	SamplerState->Release();
	BlendState->Release();
}

void EngineDirectDevice::Init(HWND _hWnd)
{
	UINT Flags = 0;
#ifdef _DEBUG
	Flags = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL FeatureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL FeatureLevel;
	DXGI_SWAP_CHAIN_DESC SwapChainDesc = {};
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
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
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
	CreateVSResources();
	CreateRSResources();
	CreatePSResources();
	CreateOMResources();
	CreateInputLayouts();
}

void EngineDirectDevice::CreateIAResources()
{
	{
		// �簢�� ���ؽ� ���� ����
		std::vector<EngineVertex> Vertices;
		Vertices.resize(4);
		Vertices[0].Position = { -0.5f, 0.5f, 0.0f, 1.0f };
		Vertices[0].TexCoord = { 0.0f, 0.0f };
		Vertices[1].Position = { -0.5f, -0.5f, 0.0f, 1.0f };
		Vertices[1].TexCoord = { 0.0f, 1.0f };
		Vertices[2].Position = { 0.5f, -0.5f, 0.0f, 1.0f };
		Vertices[2].TexCoord = { 1.0f, 1.0f };
		Vertices[3].Position = { 0.5f, 0.5f, 0.0f, 1.0f };
		Vertices[3].TexCoord = { 1.0f, 0.0f };

		VertexSize = sizeof(EngineVertex);

		D3D11_SUBRESOURCE_DATA BufferInitialData;
		BufferInitialData.pSysMem = &Vertices[0];

		D3D11_BUFFER_DESC BufferDesc = {};
		BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		BufferDesc.ByteWidth = VertexSize * Vertices.size();
		BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		BufferDesc.CPUAccessFlags = 0;

		HRESULT Result = Device->CreateBuffer(&BufferDesc, &BufferInitialData, &VertexBuffer);

		if (S_OK != Result)
		{
			MessageBoxAssert("���ؽ� ���� ������ �����߽��ϴ�.");
			return;
		}
	}

	{
		// �簢�� �ε��� ���� ����
		std::vector<UINT> Indexes = { 0, 1, 2, 0, 2, 3 };

		IndexCount = Indexes.size();

		D3D11_SUBRESOURCE_DATA BufferInitialData;
		BufferInitialData.pSysMem = &Indexes[0];

		D3D11_BUFFER_DESC BufferDesc = {};
		BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		BufferDesc.ByteWidth = sizeof(UINT) * Indexes.size();
		BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		BufferDesc.CPUAccessFlags = 0;

		HRESULT Result = Device->CreateBuffer(&BufferDesc, &BufferInitialData, &IndexBuffer);

		if (S_OK != Result)
		{
			MessageBoxAssert("�ε��� ���� ������ �����߽��ϴ�.");
			return;
		}
	}
}

void EngineDirectDevice::CreateVSResources()
{
	UINT Flag0 = D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
	UINT Flag1 = 0;
#ifdef _DEBUG
	Flag0 |= D3D10_SHADER_DEBUG;
#endif

	EnginePath AppPath;
	AppPath.MoveToAncestorsChildDirectory("MyEngineShader");
	std::list<EnginePath> ShaderPaths = AppPath.GetChildren({ ".fx" });

	for (EnginePath& ShaderPath : ShaderPaths)
	{
		if ("ShapeShader.fx" == ShaderPath.GetFilename())
		{
			continue;
		}

		std::string ShaderPathString = ShaderPath.ToString();

		HRESULT Result = D3DCompileFromFile(
			EngineString::StringToWString(ShaderPathString).c_str(),
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

void EngineDirectDevice::CreateRSResources()
{
	{
		D3D11_RASTERIZER_DESC RasterizerDesc = {};
		RasterizerDesc.FillMode = D3D11_FILL_SOLID;
		RasterizerDesc.CullMode = D3D11_CULL_NONE;
		RasterizerDesc.AntialiasedLineEnable = TRUE;
		RasterizerDesc.DepthClipEnable = TRUE;

		HRESULT Result = Device->CreateRasterizerState(&RasterizerDesc, &RasterizerState);

		if (S_OK != Result)
		{
			MessageBoxAssert("�����Ͷ����� ������Ʈ ������ �����߽��ϴ�.");
			return;
		}
	}

	{
		// ����Ʈ �ʱ�ȭ
		ViewPort.Width = 1280;
		ViewPort.Height = 720;
		ViewPort.TopLeftX = 0;
		ViewPort.TopLeftY = 0;
		ViewPort.MinDepth = 0;
		ViewPort.MaxDepth = 1;
	}
}

void EngineDirectDevice::CreatePSResources()
{
	// �ȼ� ���̴� ����
	{
		UINT Flag0 = D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
		UINT Flag1 = 0;
#ifdef _DEBUG
		Flag0 |= D3D10_SHADER_DEBUG;
#endif

		EnginePath AppPath;
		AppPath.MoveToAncestorsChildDirectory("MyEngineShader");
		std::list<EnginePath> ShaderPaths = AppPath.GetChildren({ ".fx" });

		for (EnginePath& ShaderPath : ShaderPaths)
		{
			if ("ShapeShader.fx" == ShaderPath.GetFilename())
			{
				continue;
			}

			std::string ShaderPathString = ShaderPath.ToString();

			HRESULT Result = D3DCompileFromFile(
				EngineString::StringToWString(ShaderPathString).c_str(),
				nullptr,
				D3D_COMPILE_STANDARD_FILE_INCLUDE,
				"PSmain",
				"ps_5_0",
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

	// �ؽ��� ����
	{
		EnginePath AppPath;
		AppPath.MoveToAncestorsChildDirectory("MyEngineResources");
		AppPath.MoveToChildDirectory("Image");
		std::list<EnginePath> ImagePaths = AppPath.GetChildren({ ".png" });

		for (EnginePath& ImagePath : ImagePaths)
		{
			std::string ImagePathString = ImagePath.ToString();
			DirectX::ScratchImage Image;
			DirectX::TexMetadata Metadata;

			HRESULT Result = DirectX::LoadFromWICFile(EngineString::StringToWString(ImagePathString).c_str(), DirectX::WIC_FLAGS_NONE, &Metadata, Image);

			if (S_OK != Result)
			{
				MessageBoxAssert("�̹��� �ε忡 �����߽��ϴ�.");
				return;
			};

			Result = DirectX::CreateShaderResourceView(
				Device,
				Image.GetImages(),
				Image.GetImageCount(),
				Image.GetMetadata(),
				&TextureSRV
			);

			if (S_OK != Result)
			{
				MessageBoxAssert("�ؽ��� ���̴� ���ҽ� �� ������ �����߽��ϴ�.");
				return;
			}

			break;
		}
	}

	// ���÷� ������Ʈ ����
	{
		D3D11_SAMPLER_DESC Desc = {};
		Desc.AddressU = Desc.AddressV = Desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;

		HRESULT Result = Device->CreateSamplerState(&Desc, &SamplerState);
		
		if (S_OK != Result)
		{
			MessageBoxAssert("���÷� ������Ʈ ������ �����߽��ϴ�.");
			return;
		}
	}
}

void EngineDirectDevice::CreateOMResources()
{
	{
		D3D11_BLEND_DESC Desc = {};
		Desc.AlphaToCoverageEnable = false;
		Desc.IndependentBlendEnable = false;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		// RGB = SrcRGB * SrcBlend (BlendOp) DestRGB * DestBlend;
		// Alpha = SrcAlpha * SrcBlendAlpha (BlendOpAlpha) DestAlpha  * DestBlendAlpha

		// RGB = SrcRGB * (1 - SrcAlpha) + DestRGB * Alpha
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		// Alpha = SrcAlpha * 1 (BlendOpAlpha) DestAlpha  * 1
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

		HRESULT Result = Device->CreateBlendState(&Desc, &BlendState);
	}
}

void EngineDirectDevice::CreateInputLayouts()
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> InputElementDescs = {
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	HRESULT Result = Device->CreateInputLayout(
		&InputElementDescs[0],
		InputElementDescs.size(),
		VSCodeBlob->GetBufferPointer(),
		VSCodeBlob->GetBufferSize(),
		&InputLayout
	);

	if (S_OK != Result)
	{
		MessageBoxAssert("��ǲ ���̾ƿ� ������ �����߽��ϴ�.");
		return;
	}
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

void EngineDirectDevice::TestRenderImage()
{
	Context->IASetVertexBuffers(0, 1, &VertexBuffer, &VertexSize, &VertexOffset);
	Context->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, IndexOffset);
	Context->IASetInputLayout(InputLayout);
	Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Context->VSSetShader(VertexShader, nullptr, 0);
	Context->RSSetState(RasterizerState);
	Context->RSSetViewports(1, &ViewPort);
	Context->PSSetShader(PixelShader, nullptr, 0);
	Context->PSSetShaderResources(0, 1, &TextureSRV);
	Context->PSSetSamplers(0, 1, &SamplerState);
	Context->OMSetBlendState(BlendState, float4::Zero.arr, 0xFFFFFFFF);
	Context->OMSetRenderTargets(1, &BackBufferRTV, nullptr);
	Context->DrawIndexed(IndexCount, 0, 0);
}
