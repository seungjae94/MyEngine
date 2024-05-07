#pragma once
#include <Windows.h>

class EngineCore
{
public:
	static void EngineStart(HINSTANCE _hInstance);

protected:


private:
	static void EngineUpdate();
	static void EngineEnd();

	EngineCore();
	~EngineCore();
};

