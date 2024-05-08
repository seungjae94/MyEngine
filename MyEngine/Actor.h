#pragma once

class Level;

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

protected:
	virtual void Tick(float _DeltaTime);
private:
	Level* World = nullptr;
	bool Activeness = true;
};

