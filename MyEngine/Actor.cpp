#include "PreCompile.h"
#include "Actor.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

Level* Actor::GetWorld()
{
	return World;
}

bool Actor::IsActive() const
{
	return Activeness;
}

void Actor::SetActive(bool _Activeness)
{
	Activeness = _Activeness;
}

void Actor::Tick(float _DeltaTime)
{
}
