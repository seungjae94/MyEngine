#pragma once

class TestCharacter : public Actor
{
public:
	TestCharacter();
	~TestCharacter();

	TestCharacter(const TestCharacter& _Other) = delete;
	TestCharacter(TestCharacter&& _Other) noexcept = delete;
	TestCharacter& operator=(const TestCharacter& _Other) = delete;
	TestCharacter& operator=(TestCharacter&& _Other) noexcept = delete;

protected:


private:
	Renderer* ImageRenderer = nullptr;

	void BeginPlay() override;
};

