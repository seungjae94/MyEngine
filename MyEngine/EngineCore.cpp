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
	// �޸� ���� üũ
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ������ ����
	EngineWindow::Open(_hInstance);

	// ������ �޽��� ����
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