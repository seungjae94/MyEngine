#include "PreCompile.h"
#include "EngineTime.h"

EngineTime::EngineTime()
{
}

EngineTime::~EngineTime()
{
}

void EngineTime::Start()
{
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&Counter);
}

void EngineTime::Reset()
{
	QueryPerformanceCounter(&Counter);
}

float EngineTime::Check()
{
	LARGE_INTEGER NewCounter;
	QueryPerformanceCounter(&NewCounter);

	LONGLONG DeltaCount = NewCounter.QuadPart - Counter.QuadPart;
	double DeltaTime = DeltaCount / static_cast<double>(Frequency.QuadPart);
	Counter = NewCounter;

	return static_cast<float>(DeltaTime);
}
