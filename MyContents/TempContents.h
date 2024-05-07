#pragma once
class TempContents
{
public:
	TempContents();
	~TempContents();

	TempContents(const TempContents& _Other) = delete;
	TempContents(TempContents&& _Other) noexcept = delete;
	TempContents& operator=(const TempContents& _Other) = delete;
	TempContents& operator=(TempContents&& _Other) noexcept = delete;

protected:


private:


};

