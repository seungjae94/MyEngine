#include "PreCompile.h"
#include "EngineCore.h"
#include "Renderer.h"
#include "Actor.h"
#include "EngineDirectDevice.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"
#include "EngineTexture.h"
#include "EngineSamplerState.h"
#include "EngineRasterizerState.h"
#include "EngineBlendState.h"
#include "EngineInputLayout.h"


Renderer::Renderer()
{
    VertexBuffer = EngineVertexBuffer::Find("Rect");
    IndexBuffer = EngineIndexBuffer::Find("Rect");
    VertexShader = EngineVertexShader::Find("ImageShader.fx");
    RasterizerState = EngineRasterizerState::Find("Default");
    PixelShader = EnginePixelShader::Find("ImageShader.fx");
    SamplerState = EngineSamplerState::Find("Point");
    BlendState = EngineBlendState::Find("Default");
    InputLayout = EngineInputLayout::Create(VertexBuffer, VertexShader);
}

Renderer::~Renderer()
{
}

void Renderer::SetTexture(std::string_view _Name)
{
    Texture = EngineTexture::Find(_Name);

    if (nullptr == Texture)
    {
        MessageBoxAssert(std::string("�������� �ʴ� �ؽ��� ") + _Name.data() + "�� �������� �����Ϸ��� �߽��ϴ�.");
        return;
    }
}

void Renderer::BeginPlay()
{
    Owner->GetWorld()->Renderers[Order].push_back(shared_from_this());
}

void Renderer::Render()
{
    if (nullptr == Texture)
    {
        MessageBoxAssert("�������� �ؽ��ĸ� �������� �ʾҽ��ϴ�.");
        return;
    }

    VertexBuffer->SetToPipeline();
    IndexBuffer->SetToPipeline();
    InputLayout->SetToPipeline();
    VertexShader->SetToPipeline();
    RasterizerState->SetToPipeline();
    PixelShader->SetToPipeline();
    Texture->SetToPipeline();
    SamplerState->SetToPipeline();
    BlendState->SetToPipeline();

    EngineCore::DirectDevice.DrawIndexed(IndexBuffer->Count);
}
