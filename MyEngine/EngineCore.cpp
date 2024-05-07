#include "EngineCore.h"
#include <assert.h>
#include <crtdbg.h>
#include "EngineWindow.h"

EngineCore::EngineCore()
{
}

EngineCore::~EngineCore()
{
}

void EngineCore::EngineStart(HINSTANCE _hInstance)
{
	// 메모리 누수 체크
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 윈도우 띄우기
	EngineWindow::Open(_hInstance);

	// 윈도우 메시지 루프
	EngineWindow::MessageLoop(EngineUpdate, EngineEnd);
}

void EngineCore::EngineUpdate()
{
	int a = 0;
}

void EngineCore::EngineEnd()
{
	int a = 0;
}

class EngineCoreStarter
{
public:
	EngineCoreStarter(HINSTANCE hInstance)
	{
		EngineCore::EngineStart(hInstance);
	}
};