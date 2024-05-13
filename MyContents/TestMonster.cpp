#include "PreCompile.h"
#include "TestMonster.h"

TestMonster::TestMonster()
{
}

TestMonster::~TestMonster()
{
}

void TestMonster::BeginPlay()
{
	Actor::BeginPlay();

	ImageRenderer = CreateDefaultSubobject<Renderer>("Renderer");
	ImageRenderer->SetTexture("TestMonster.png");
}
