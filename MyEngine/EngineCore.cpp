#include "PreCompile.h"
#include "EngineCore.h"
#include "EngineWindow.h"
#include "EngineTime.h"
#include "EngineDirectDevice.h"
#include "Level.h"

std::shared_ptr<UserCore> EngineCore::UserCoreInst = nullptr;
std::map<std::string, std::shared_ptr<Level>> EngineCore::Levels;
std::shared_ptr<Level> EngineCore::CurLevel = nullptr;
std::shared_ptr<Level> EngineCore::NextLevel = nullptr;
EngineTime EngineCore::MainTimer;
EngineDirectDevice EngineCore::DirectDevice;

EngineCore::EngineCore()
{
}

EngineCore::~EngineCore()
{
}

void EngineCore::ChangeLevel(std::string_view _LevelName)
{
	if (false == Levels.contains(_LevelName.data()))
	{
		MessageBoxAssert(std::string("�������� ���� ����") + _LevelName.data() + "�� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	NextLevel = Levels[_LevelName.data()];
}

void EngineCore::EngineStart(HINSTANCE _hInstance)
{
	// �޸� ���� üũ
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ������ ����
	EngineWindow::Open(_hInstance);

	// ���̷�Ʈ �ʱ�ȭ
	DirectDevice.Init(EngineWindow::hWnd);

	// ���� �ھ� �ʱ�ȭ �Լ� ȣ��
	UserCoreInst->Init();

	// �ð� ���� ����
	MainTimer.Start();

	// ������ �޽��� ����
	EngineWindow::MessageLoop(EngineUpdate, EngineEnd);
}

void EngineCore::EngineUpdate()
{
	// �ð� ����
	float DeltaTime = MainTimer.Check();

	// ���� ���� ����
	if (nullptr != NextLevel)
	{
		if (nullptr != CurLevel)
		{
			CurLevel->LevelEnd(NextLevel.get());
		}
		NextLevel->LevelStart(CurLevel.get());

		CurLevel = NextLevel;
		NextLevel = nullptr;
	}

	// ������Ʈ ƽ
	CurLevel->Tick(DeltaTime);

	// ������
	DirectDevice.ClearBackBuffer();
	CurLevel->Render();
	DirectDevice.Present();
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