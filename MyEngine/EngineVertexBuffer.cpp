#include "PreCompile.h"
#include "EngineVertexBuffer.h"
#include "EngineDirectDevice.h"

EngineVertexBuffer::EngineVertexBuffer()
{
}

EngineVertexBuffer::~EngineVertexBuffer()
{
}

void EngineVertexBuffer::CreateDirectResource(void* _VerticesMem)
{
	D3D11_SUBRESOURCE_DATA InitialData;
	InitialData.pSysMem = _VerticesMem;

	D3D11_BUFFER_DESC Desc = {};
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.ByteWidth = Size * Count;
	Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Desc.CPUAccessFlags = 0;

	HRESULT Result = GetDevice()->CreateBuffer(&Desc, &InitialData, &Buffer);

	if (S_OK != Result)
	{
		MessageBoxAssert("버텍스 버퍼 생성에 실패했습니다.");
		return;
	}
}

void EngineVertexBuffer::SetToPipeline()
{
	GetContext()->IASetVertexBuffers(0, 1, &Buffer, &Size, &Offset);
}
