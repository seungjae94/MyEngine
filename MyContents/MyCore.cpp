#include "PreCompile.h"
#include "MyCore.h"
#include "TestLevel.h"

MyCore::MyCore()
{
}

MyCore::~MyCore()
{
}

void MyCore::Init()
{
	EngineCore::CreateLevel<TestLevel>("TestLevel");
	EngineCore::ChangeLevel("TestLevel");
}
