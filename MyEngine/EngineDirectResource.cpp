#include "PreCompile.h"
#include "EngineDirectResource.h"
#include "EngineCore.h"
#include "EngineDirectDevice.h"

EngineDirectResource::EngineDirectResource()
{
}

EngineDirectResource::~EngineDirectResource()
{
}

ID3D11Device* EngineDirectResource::GetDevice()
{
    return EngineCore::DirectDevice.Device;
}

ID3D11DeviceContext* EngineDirectResource::GetContext()
{
    return EngineCore::DirectDevice.Context;
}
