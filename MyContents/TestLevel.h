#pragma once

class TestLevel : public Level
{
public:
	TestLevel();
	~TestLevel();

	TestLevel(const TestLevel& _Other) = delete;
	TestLevel(TestLevel&& _Other) noexcept = delete;
	TestLevel& operator=(const TestLevel& _Other) = delete;
	TestLevel& operator=(TestLevel&& _Other) noexcept = delete;

protected:


private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

