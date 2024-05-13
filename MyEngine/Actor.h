#pragma once
#include "Component.h"

class Level;
class Component;

class Actor
{
	friend Level;
public:
	Actor();
	~Actor();

	Actor(const Actor& _Other) = delete;
	Actor(Actor&& _Other) noexcept = delete;
	Actor& operator=(const Actor& _Other) = delete;
	Actor& operator=(Actor&& _Other) noexcept = delete;

	Level* GetWorld();
	bool IsActive() const;
	void SetActive(bool _Activeness);

	template<typename ComponentType>
	ComponentType* CreateDefaultSubobject(std::string_view _Name)
	{
		std::shared_ptr<ComponentType> NewComponent = std::make_shared<ComponentType>();
		std::shared_ptr<Component> AsComponent = dynamic_pointer_cast<Component>(NewComponent);
		AsComponent->Name = _Name;
		AsComponent->Owner = this;
		AsComponent->BeginPlay();
		Components.push_back(NewComponent);
		return NewComponent.get();
	}

protected:
	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);
private:
	Level* World = nullptr;
	bool Activeness = true;

	std::list<std::shared_ptr<Component>> Components;
};

