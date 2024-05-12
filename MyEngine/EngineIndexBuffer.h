#pragma once
#include "EngineBuffer.h"

class EngineIndexBuffer : public EngineResource<EngineIndexBuffer>, public EngineBuffer
{
	friend EngineDirectDevice;
public:
	// constructor destructor
	EngineIndexBuffer();
	~EngineIndexBuffer();

	// delete Function
	EngineIndexBuffer(const EngineIndexBuffer& _Other) = delete;
	EngineIndexBuffer(EngineIndexBuffer&& _Other) noexcept = delete;
	EngineIndexBuffer& operator=(const EngineIndexBuffer& _Other) = delete;
	EngineIndexBuffer& operator=(EngineIndexBuffer&& _Other) noexcept = delete;

	template<typename IndexType>
	static EngineIndexBuffer* Create(std::string_view _Name, std::vector<IndexType>& _Indexes)
	{
		EngineIndexBuffer* Resource = CreateEngineResource(_Name);
		Resource->Count = static_cast<UINT>(_Indexes.size());
		Resource->Size = sizeof(IndexType);
		Resource->Offset = 0;
		Resource->CreateDirectResource(&_Indexes[0]);
		return Resource;
	}

	UINT GetCount() const;

protected:

private:
	void CreateDirectResource(void* _IndexesMem);
	void SetToPipeline() override;
};

