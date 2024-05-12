#include "PreCompile.h"
#include "EnginePixelShader.h"

EnginePixelShader::EnginePixelShader()
{
}

EnginePixelShader::~EnginePixelShader()
{
	if (nullptr != PixelShader)
	{
		PixelShader->Release();
	}
}

void EnginePixelShader::CreateDirectResource(std::string_view _PathString)
{
	UINT Flag0 = D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
	UINT Flag1 = 0;
#ifdef _DEBUG
	Flag0 |= D3D10_SHADER_DEBUG;
#endif

	HRESULT Result = D3DCompileFromFile(
		EngineString::StringToWString(_PathString).c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PSmain",
		"ps_5_0",
		Flag0,
		Flag1,
		&CodeBlob,
		&ErrorBlob
	);

	if (S_OK != Result)
	{
		char* ErrorMessage = reinterpret_cast<char*>(ErrorBlob->GetBufferPointer());
		MessageBoxAssert(ErrorMessage);
		return;
	}

	Result = GetDevice()->CreatePixelShader(
		CodeBlob->GetBufferPointer(),
		CodeBlob->GetBufferSize(),
		nullptr,
		&PixelShader
	);

	if (S_OK != Result)
	{
		MessageBoxAssert("픽셀 셰이더 생성에 실패했습니다.");
		return;
	}
}

void EnginePixelShader::SetToPipeline()
{
	GetContext()->PSSetShader(PixelShader, nullptr, 0);
}
