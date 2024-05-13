#include "PreCompile.h"
#include "EngineTexture.h"

EngineTexture::EngineTexture()
{
}

EngineTexture::~EngineTexture()
{
    if (nullptr != SRV)
    {
        SRV->Release();
    }
}

EngineTexture* EngineTexture::Create(const EnginePath& _Path)
{
    std::string FileName = _Path.GetFilename();
    EngineTexture* Resource = CreateEngineResource(FileName);
    Resource->CreateDirectResource(_Path.ToString());
    return Resource;
}

void EngineTexture::CreateDirectResource(std::string_view _PathString)
{
    DirectX::ScratchImage Image;
    DirectX::TexMetadata Metadata;

    HRESULT Result = DirectX::LoadFromWICFile(
        EngineString::StringToWString(_PathString).c_str(), 
        DirectX::WIC_FLAGS_NONE, &Metadata, Image);

    if (S_OK != Result)
    {
        MessageBoxAssert("�̹��� �ε忡 �����߽��ϴ�.");
        return;
    };

    Result = DirectX::CreateShaderResourceView(
        GetDevice(),
        Image.GetImages(),
        Image.GetImageCount(),
        Image.GetMetadata(),
        &SRV
    );

    if (S_OK != Result)
    {
        MessageBoxAssert("�ؽ��� ���̴� ���ҽ� �� ������ �����߽��ϴ�.");
        return;
    }
}

void EngineTexture::SetToPipeline()
{
    GetContext()->PSSetShaderResources(0, 1, &SRV);
}
