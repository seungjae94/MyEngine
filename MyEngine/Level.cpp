#include "PreCompile.h"
#include "Level.h"
#include "Actor.h"
#include "Renderer.h"
#include "EngineCore.h"
#include "EngineDirectDevice.h"

Level::Level()
{
	// 뷰포트 초기화
	ViewPort.Width = 1280;
	ViewPort.Height = 720;
	ViewPort.TopLeftX = 0;
	ViewPort.TopLeftY = 0;
	ViewPort.MinDepth = 0;
	ViewPort.MaxDepth = 1;
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

void Level::Render()
{
	EngineCore::DirectDevice.Context->RSSetViewports(1, &ViewPort);
	EngineCore::DirectDevice.SetBackBufferRenderTargets();

	for (std::pair<const int, std::list<std::shared_ptr<Renderer>>>& OrderRendererListPair : Renderers)

	{
		const int Order = OrderRendererListPair.first;
		std::list<std::shared_ptr<Renderer>>& RendererList = OrderRendererListPair.second;

		for (std::shared_ptr<Renderer> Renderer : RendererList)
		{
			Renderer->Render();
		}
	}
}
