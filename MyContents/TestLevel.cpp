#include "PreCompile.h"
#include "TestLevel.h"

TestLevel::TestLevel()
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::BeginPlay()
{
	Level::BeginPlay();

	int a = 0;
}

void TestLevel::Tick(float _DeltaTime)
{
	Level::Tick(_DeltaTime);

	int a = 0;
}
