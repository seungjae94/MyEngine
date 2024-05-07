#pragma once
class Level
{
public:
	Level();
	~Level();

	Level(const Level& _Other) = delete;
	Level(Level&& _Other) noexcept = delete;
	Level& operator=(const Level& _Other) = delete;
	Level& operator=(Level&& _Other) noexcept = delete;

protected:


private:
	
};

