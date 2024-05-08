#pragma once

class EngineTime
{
public:
	EngineTime();
	~EngineTime();

	EngineTime(const EngineTime& _Other) = delete;
	EngineTime(EngineTime&& _Other) noexcept = delete;
	EngineTime& operator=(const EngineTime& _Other) = delete;
	EngineTime& operator=(EngineTime&& _Other) noexcept = delete;

	void Start();
	void Reset();
	float Check();

protected:


private:
	LARGE_INTEGER Frequency = {};
	LARGE_INTEGER Counter = {};
};

