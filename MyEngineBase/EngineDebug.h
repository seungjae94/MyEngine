#pragma once

#define MessageBoxAssert(Message) MessageBoxA(nullptr, std::string(Message).c_str(), "에러 발생", MB_OK); assert(false);

class EngineDebug
{
public:
	EngineDebug();
	~EngineDebug();

	EngineDebug(const EngineDebug& _Other) = delete;
	EngineDebug(EngineDebug&& _Other) noexcept = delete;
	EngineDebug& operator=(const EngineDebug& _Other) = delete;
	EngineDebug& operator=(EngineDebug&& _Other) noexcept = delete;

protected:


private:

};

