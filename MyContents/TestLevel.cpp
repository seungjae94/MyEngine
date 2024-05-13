#include "PreCompile.h"
#include "TestLevel.h"
#include "TestCharacter.h"
#include "TestMonster.h"

TestLevel::TestLevel()
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::BeginPlay()
{
	Level::BeginPlay();

	TestCharacter* Character = SpawnActor<TestCharacter>(0);
	TestMonster* Monster = SpawnActor<TestMonster>(0);
}

void TestLevel::Tick(float _DeltaTime)
{
	Level::Tick(_DeltaTime);

	int a = 0;
}
