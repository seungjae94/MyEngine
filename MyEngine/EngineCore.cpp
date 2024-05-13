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
		MessageBoxAssert(std::string("생성하지 않은 레벨") + _LevelName.data() + "로 변경하려고 했습니다.");
		return;
	}

	NextLevel = Levels[_LevelName.data()];
}

void EngineCore::EngineStart(HINSTANCE _hInstance)
{
	// 메모리 누수 체크
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 윈도우 띄우기
	EngineWindow::Open(_hInstance);

	// 다이렉트 초기화
	DirectDevice.Init(EngineWindow::hWnd);

	// 유저 코어 초기화 함수 호출
	UserCoreInst->Init();

	// 시간 측정 시작
	MainTimer.Start();

	// 윈도우 메시지 루프
	EngineWindow::MessageLoop(EngineUpdate, EngineEnd);
}

void EngineCore::EngineUpdate()
{
	// 시간 측정
	float DeltaTime = MainTimer.Check();

	// 레벨 변경 로직
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

	// 오브젝트 틱
	CurLevel->Tick(DeltaTime);

	// 렌더링
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