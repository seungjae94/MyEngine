#pragma once
class EngineString
{
public:
	EngineString(const EngineString& _Other) = delete;
	EngineString(EngineString&& _Other) noexcept = delete;
	EngineString& operator=(const EngineString& _Other) = delete;
	EngineString& operator=(EngineString&& _Other) noexcept = delete;

	static std::wstring StringToWString(std::string_view _String);
	static std::string WStringToString(std::wstring_view _WString);

protected:


private:
	EngineString();
	~EngineString();
};

