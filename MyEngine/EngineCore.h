#pragma once
#include <Windows.h>

#define MyEngineStart \
class EngineCoreStarter \
{ \
friend int APIENTRY wWinMain(_In_ HINSTANCE hInstance, \
	_In_opt_ HINSTANCE hPrevInstance, \
	_In_ LPWSTR    lpCmdLine, \
	_In_ int       nCmdShow);\
private: \
	EngineCoreStarter(HINSTANCE hInstance) \
	{ \
		EngineCore::EngineStart(hInstance); \
	} \
}; \
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, \
	_In_opt_ HINSTANCE hPrevInstance, \
	_In_ LPWSTR    lpCmdLine, \
	_In_ int       nCmdShow) \
{ \
	EngineCoreStarter Starter(hInstance); \
} \

class EngineCoreStarter;

class EngineCore
{
	friend EngineCoreStarter;
private:
	static void EngineStart(HINSTANCE _hInstance);
	static void EngineUpdate();
	static void EngineEnd();

	EngineCore();
	~EngineCore();
};

