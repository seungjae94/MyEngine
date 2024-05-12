#include "PreCompile.h"
#include "EngineBlendState.h"

EngineBlendState::EngineBlendState()
{
}

EngineBlendState::~EngineBlendState()
{
    if (nullptr != BlendState)
    {
        BlendState->Release();
    }
}

EngineBlendState* EngineBlendState::Create(std::string_view _Name, const D3D11_BLEND_DESC& _Desc)
{
    EngineBlendState* Resource = CreateEngineResource(_Name);
    Resource->CreateDirectResource(_Desc);
    return Resource;
}

void EngineBlendState::CreateDirectResource(const D3D11_BLEND_DESC& _Desc)
{
    HRESULT Result = GetDevice()->CreateBlendState(&_Desc, &BlendState);

    if (S_OK != Result)
    {
        MessageBoxAssert("블렌드 스테이트 생성에 실패했습니다.");
        return;
    }
}

void EngineBlendState::SetToPipeline()
{
    GetContext()->OMSetBlendState(BlendState, float4::Zero.arr, 0xFFFFFFFF);
}
