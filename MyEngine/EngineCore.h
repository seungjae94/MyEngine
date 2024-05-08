#pragma once
#include "Level.h"

#define MyEngineStart(UserCoreType) \
class EngineCoreStarter \
{ \
friend int APIENTRY wWinMain(_In_ HINSTANCE hInstance, \
	_In_opt_ HINSTANCE hPrevInstance, \
	_In_ LPWSTR    lpCmdLine, \
	_In_ int       nCmdShow);\
private: \
	EngineCoreStarter(HINSTANCE hInstance) \
	{ \
		{ \
			std::shared_ptr<UserCoreType> NewUserCore = std::make_shared<UserCoreType>(); \
			EngineCore::UserCoreInst = NewUserCore; \
		} \
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
class EngineTime;

class UserCore
{
public:
	virtual void Init() = 0;
};

class EngineCore
{
	friend EngineCoreStarter;
public:
	template <typename LevelType>
	static void CreateLevel(std::string_view _LevelName)
	{
		std::shared_ptr<LevelType> NewLevel = std::make_shared<LevelType>();
		std::shared_ptr<Level> AsLevel = dynamic_pointer_cast<Level>(NewLevel);
		AsLevel->BeginPlay();
		Levels[_LevelName.data()] = AsLevel;
	}

	static void ChangeLevel(std::string_view _LevelName);
private:
	static std::shared_ptr<UserCore> UserCoreInst;
	static std::map<std::string, std::shared_ptr<Level>> Levels;
	static std::shared_ptr<Level> CurLevel;
	static std::shared_ptr<Level> NextLevel;
	static EngineTime MainTimer;

	static void EngineStart(HINSTANCE _hInstance);
	static void EngineUpdate();
	static void EngineEnd();

	EngineCore();
	~EngineCore();
};

