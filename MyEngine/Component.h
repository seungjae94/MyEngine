#pragma once

class Actor;

class Component
{
	friend Actor;
public:
	Component();
	~Component();

	Component(const Component& _Other) = delete;
	Component(Component&& _Other) noexcept = delete;
	Component& operator=(const Component& _Other) = delete;
	Component& operator=(Component&& _Other) noexcept = delete;

protected:
	int Order = 0;
	std::string Name = "";
	Actor* Owner = nullptr;

	virtual void BeginPlay() {};
private:
};

