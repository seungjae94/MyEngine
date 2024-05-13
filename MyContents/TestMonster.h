#pragma once

class TestMonster : public Actor
{
public:
	TestMonster();
	~TestMonster();

	TestMonster(const TestMonster& _Other) = delete;
	TestMonster(TestMonster&& _Other) noexcept = delete;
	TestMonster& operator=(const TestMonster& _Other) = delete;
	TestMonster& operator=(TestMonster&& _Other) noexcept = delete;

protected:


private:
	Renderer* ImageRenderer = nullptr;

	void BeginPlay() override;
};

