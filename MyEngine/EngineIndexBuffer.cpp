#include "PreCompile.h"
#include "EngineIndexBuffer.h"

EngineIndexBuffer::EngineIndexBuffer()
{
}

EngineIndexBuffer::~EngineIndexBuffer()
{
}

UINT EngineIndexBuffer::GetCount() const
{
	return Count;
}

void EngineIndexBuffer::CreateDirectResource(void* _IndexesMem)
{
	D3D11_SUBRESOURCE_DATA BufferInitialData;
	BufferInitialData.pSysMem = _IndexesMem;

	D3D11_BUFFER_DESC BufferDesc = {};
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.ByteWidth = Size * Count;
	BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferDesc.CPUAccessFlags = 0;

	HRESULT Result = GetDevice()->CreateBuffer(&BufferDesc, &BufferInitialData, &Buffer);

	if (S_OK != Result)
	{
		MessageBoxAssert("인덱스 버퍼 생성에 실패했습니다.");
		return;
	}
}

void EngineIndexBuffer::SetToPipeline()
{
	GetContext()->IASetIndexBuffer(Buffer, DXGI_FORMAT_R32_UINT, Offset);
	GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
