#include "PreCompile.h"
#include "Level.h"
#include "Actor.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::BeginPlay()
{
}

void Level::LevelStart(Level* _PrevLevel)
{

}

void Level::LevelEnd(Level* _NextLevel)
{
}

void Level::Tick(float _DeltaTime)
{
	for (std::pair<const int, std::list<std::shared_ptr<Actor>>>& OrderActorListPair : Actors)
	{
		const int Order = OrderActorListPair.first;
		std::list<std::shared_ptr<Actor>>& ActorList = OrderActorListPair.second;

		for (std::shared_ptr<Actor> Actor : ActorList)
		{
			if (false == Actor->IsActive())
			{
				continue;
			}

			Actor->Tick(_DeltaTime);
		}
	}
}