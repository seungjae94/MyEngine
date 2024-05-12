#include "PreCompile.h"
#include "EngineBuffer.h"

EngineBuffer::EngineBuffer()
{
}

EngineBuffer::~EngineBuffer()
{
    if (nullptr != Buffer)
    {
        Buffer->Release();
    }
}