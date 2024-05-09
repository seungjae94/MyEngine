#pragma once

union float2
{
	struct
	{
		float x;
		float y;
	};

	struct
	{
		float u;
		float v;
	};
};

union float4
{
	struct
	{
		float x;
		float y;
		float z;
		float w;
	};

	struct
	{
		float r;
		float g;
		float b;
		float a;
	};
};

class EngineMath
{
public:
	EngineMath();
	~EngineMath();

	EngineMath(const EngineMath& _Other) = delete;
	EngineMath(EngineMath&& _Other) noexcept = delete;
	EngineMath& operator=(const EngineMath& _Other) = delete;
	EngineMath& operator=(EngineMath&& _Other) noexcept = delete;

protected:


private:


};

