#include "PreCompile.h"
#include "EngineRasterizerState.h"

EngineRasterizerState::EngineRasterizerState()
{
}

EngineRasterizerState::~EngineRasterizerState()
{
    if (nullptr != RasterizerState)
    {
        RasterizerState->Release();
    }
}

EngineRasterizerState* EngineRasterizerState::Create(std::string_view _Name, D3D11_RASTERIZER_DESC _Desc)
{
    EngineRasterizerState* Resource = CreateEngineResource(_Name);
    Resource->CreateDirectResource(_Desc);
    return Resource;
}

void EngineRasterizerState::CreateDirectResource(D3D11_RASTERIZER_DESC _Desc)
{
    HRESULT Result = GetDevice()->CreateRasterizerState(&_Desc, &RasterizerState);

    if (S_OK != Result)
    {
        MessageBoxAssert("래스터라이저 스테이트 생성에 실패했습니다.");
        return;
    }
}

void EngineRasterizerState::SetToPipeline()
{
    GetContext()->RSSetState(RasterizerState);
}
