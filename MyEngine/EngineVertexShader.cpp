#include "PreCompile.h"
#include "EngineVertexShader.h"

EngineVertexShader::EngineVertexShader()
{
}

EngineVertexShader::~EngineVertexShader()
{
	if (nullptr != VertexShader)
	{
		VertexShader->Release();
	}
}

void EngineVertexShader::CreateDirectResource(std::string_view _PathString)
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
		"VSmain",
		"vs_5_0",
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

	Result = GetDevice()->CreateVertexShader(
		CodeBlob->GetBufferPointer(),
		CodeBlob->GetBufferSize(),
		nullptr,
		&VertexShader
	);

	if (S_OK != Result)
	{
		MessageBoxAssert("버텍스 셰이더 생성에 실패했습니다.");
		return;
	}
}

void EngineVertexShader::SetToPipeline()
{
	GetContext()->VSSetShader(VertexShader, nullptr, 0);
}
