#pragma once

struct EngineVertex
{
public:
	static std::vector<D3D11_INPUT_ELEMENT_DESC> InputElementDescs;
	float4 Position;
	float2 TexCoord;
};