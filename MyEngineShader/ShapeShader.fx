struct EngineVertex
{
	float4 POSITION : POSITION;
};

struct VSOutput
{
	float4 POSITION : SV_POSITION;
};

struct PSOutput
{
	float4 COLOR : SV_TARGET0;
};

VSOutput VSmain(EngineVertex _Input)
{
	VSOutput Output = (VSOutput) 0;
	Output.POSITION = _Input.POSITION;
	return Output;
}

PSOutput PSmain(VSOutput _Input)
{
	PSOutput Output = (PSOutput) 0;
	Output.COLOR = float4(1.0f, 0.0f, 0.0f, 1.0f);
	return Output;
}