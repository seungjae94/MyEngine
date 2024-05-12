#pragma once
#include "EngineBuffer.h"

class EngineInputLayout;

class EngineVertexBuffer : public EngineResource<EngineVertexBuffer>, public EngineBuffer
{
    friend EngineDirectDevice;
    friend EngineInputLayout;
public:
    // constructor destructor
    EngineVertexBuffer();
    ~EngineVertexBuffer();

    // delete Function
    EngineVertexBuffer(const EngineVertexBuffer& _Other) = delete;
    EngineVertexBuffer(EngineVertexBuffer&& _Other) noexcept = delete;
    EngineVertexBuffer& operator=(const EngineVertexBuffer& _Other) = delete;
    EngineVertexBuffer& operator=(EngineVertexBuffer&& _Other) noexcept = delete;

    template<typename VertexType>
    static EngineVertexBuffer* Create(std::string_view _Name, std::vector<VertexType>& _Vertices)
    {
        EngineVertexBuffer* Resource = CreateEngineResource(_Name);
        Resource->Count = static_cast<UINT>(_Vertices.size());
        Resource->Size = sizeof(VertexType);
        Resource->Offset = 0;
        Resource->InputElementDescs = &VertexType::InputElementDescs;
        Resource->CreateDirectResource(&_Vertices[0]);
        return Resource;
    }

protected:

private:
    std::vector<D3D11_INPUT_ELEMENT_DESC>* InputElementDescs = nullptr;

    void CreateDirectResource(void* _VerticesMem);
    void SetToPipeline() override;
};

