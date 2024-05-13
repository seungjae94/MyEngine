#include "PreCompile.h"
#include "TestCharacter.h"

TestCharacter::TestCharacter()
{
}

TestCharacter::~TestCharacter()
{
}

void TestCharacter::BeginPlay()
{
	Actor::BeginPlay();

	ImageRenderer = CreateDefaultSubobject<Renderer>("Renderer");
	ImageRenderer->SetTexture("TestCharacter.png");
}
