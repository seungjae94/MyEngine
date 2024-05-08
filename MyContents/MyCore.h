#pragma once

class MyCore : public UserCore
{
public:
	MyCore();
	~MyCore();

	MyCore(const MyCore& _Other) = delete;
	MyCore(MyCore&& _Other) noexcept = delete;
	MyCore& operator=(const MyCore& _Other) = delete;
	MyCore& operator=(MyCore&& _Other) noexcept = delete;

protected:
		
private:
	void Init() override;
};

