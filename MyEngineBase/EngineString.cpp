#include "PreCompile.h"
#include "EngineString.h"
#include "EngineDebug.h"

std::wstring EngineString::StringToWString(std::string_view _String)
{
	int Size = MultiByteToWideChar(CP_ACP, 0, _String.data(), _String.size(), nullptr, 0);
	if (0 == Size)
	{
		MessageBoxAssert("���ڿ� ��ȯ�� �����߽��ϴ�.");
		return L"";
	}
	std::wstring Result;
	Result.resize(Size);
	Size = MultiByteToWideChar(CP_ACP, 0, _String.data(), Size, &Result[0], Size);
	if (0 == Size)
	{
		MessageBoxAssert("���ڿ� ��ȯ�� �����߽��ϴ�.");
		return L"";
	}
	return Result;
}

std::string EngineString::WStringToString(std::wstring_view _WString)
{
	int Size = WideCharToMultiByte(CP_ACP, 0, _WString.data(), _WString.size(), nullptr, 0, 0, 0);
	if (0 == Size)
	{
		MessageBoxAssert("���ڿ� ��ȯ�� �����߽��ϴ�.");
		return "";
	}
	std::string Result;
	Result.resize(Size);
	Size = WideCharToMultiByte(CP_ACP, 0, _WString.data(), Size, &Result[0], Size, 0, 0);
	if (0 == Size)
	{
		MessageBoxAssert("���ڿ� ��ȯ�� �����߽��ϴ�.");
		return "";
	}
	return Result;
}

EngineString::EngineString()
{
}

EngineString::~EngineString()
{
}
