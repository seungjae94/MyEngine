#include "PreCompile.h"
#include "EngineSamplerState.h"

EngineSamplerState::EngineSamplerState()
{
}

EngineSamplerState::~EngineSamplerState()
{
    if (nullptr != SamplerState)
    {
        SamplerState->Release();
    }
}

EngineSamplerState* EngineSamplerState::Create(std::string_view _Name, const D3D11_SAMPLER_DESC& _Desc)
{
    EngineSamplerState* Resource = CreateEngineResource(_Name);
    Resource->CreateDirectResource(_Desc);
    return Resource;
}

void EngineSamplerState::CreateDirectResource(const D3D11_SAMPLER_DESC& _Desc)
{
    HRESULT Result = GetDevice()->CreateSamplerState(&_Desc, &SamplerState);

    if (S_OK != Result)
    {
        MessageBoxAssert("샘플러 스테이트 생성에 실패했습니다.");
        return;
    }
}

void EngineSamplerState::SetToPipeline()
{
    GetContext()->PSSetSamplers(0, 1, &SamplerState);
}
