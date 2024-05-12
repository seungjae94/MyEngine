#include "PreCompile.h"
#include "EngineInputLayout.h"
#include "EngineVertexBuffer.h"
#include "EngineVertexShader.h"

EngineInputLayout::EngineInputLayout()
{
}

EngineInputLayout::~EngineInputLayout()
{
    if (nullptr != InputLayout)
    {
        InputLayout->Release();
    }
}

EngineInputLayout* EngineInputLayout::Create(EngineVertexBuffer* _VertexBuffer, EngineVertexShader* _VertexShader)
{
    EngineInputLayout* Resource = CreateEngineResource();
    Resource->VSCodeBlob = _VertexShader->CodeBlob;
    Resource->CreateDirectResource(_VertexBuffer->InputElementDescs);
    return Resource;
}

void EngineInputLayout::CreateDirectResource(std::vector<D3D11_INPUT_ELEMENT_DESC>* _Descs)
{
    HRESULT Result = GetDevice()->CreateInputLayout(
        &(*_Descs)[0],
        static_cast<UINT>(_Descs->size()),
        VSCodeBlob->GetBufferPointer(),
        VSCodeBlob->GetBufferSize(),
        &InputLayout
    );

    if (S_OK != Result)
    {
        MessageBoxAssert("인풋 레이아웃 생성에 실패했습니다.");
        return;
    }
}

void EngineInputLayout::SetToPipeline()
{
    GetContext()->IASetInputLayout(InputLayout);
}
