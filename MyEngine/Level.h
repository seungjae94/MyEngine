#pragma once

class EngineCore;
class Camera;
class Actor;
class Renderer;

class Level
{
	friend EngineCore;
	friend Actor;
	friend Renderer;
public:
	Level();
	~Level();

	Level(const Level& _Other) = delete;
	Level(Level&& _Other) noexcept = delete;
	Level& operator=(const Level& _Other) = delete;
	Level& operator=(Level&& _Other) noexcept = delete;

	template <typename ActorType, typename EnumType>
	ActorType* SpawnActor(EnumType _Order)
	{
		int Order = static_cast<int>(_Order);
		return SpawnActor<ActorType>(Order);
	}

	template <typename ActorType>
	ActorType* SpawnActor(int _Order)
	{
		std::shared_ptr<ActorType> NewActor = std::make_shared<ActorType>();
		std::shared_ptr<Actor> AsActor = dynamic_pointer_cast<ActorType>(NewActor);
		AsActor->World = this;
		AsActor->BeginPlay();
		Actors[_Order].push_back(AsActor);
		return NewActor.get();
	}

protected:
	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);
	virtual void Render();
	virtual void LevelStart(Level* _PrevLevel);
	virtual void LevelEnd(Level* _NextLevel);
private:
	std::shared_ptr<Camera> MainCamera = nullptr;

	std::map<int, std::list<std::shared_ptr<Actor>>> Actors;
	std::map<int, std::list<std::shared_ptr<Renderer>>> Renderers;
};