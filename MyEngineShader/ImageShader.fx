struct EngineVertex
{
	float4 POSITION : POSITION;
	float2 TEXCOORD : TEXCOORD;
};

struct VSOutput
{
	float4 POSITION : SV_POSITION;
	float2 TEXCOORD : TEXCOORD;
};

struct PSOutput
{
	float4 COLOR : SV_TARGET;
};

VSOutput VSmain(EngineVertex _Input)
{
	VSOutput Output = (VSOutput) 0;
	Output.POSITION = _Input.POSITION;
	Output.TEXCOORD = _Input.TEXCOORD;
	return Output;
}

Texture2D Image : register(t0);
SamplerState Sampler : register(s0);

PSOutput PSmain(VSOutput _Input)
{
	PSOutput Output = (PSOutput) 0;
	Output.COLOR = Image.Sample(Sampler, _Input.TEXCOORD);
	return Output;
}