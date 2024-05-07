#pragma once
#include <Windows.h>
#include <functional>

class EngineCore;

class EngineWindow
{
	friend EngineCore;
public:

protected:

private:
	static HINSTANCE hInstance;
	static bool WindowOn;

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static void Open(HINSTANCE _hInstance);
	static int MessageLoop(std::function<void()> _UpdateFunc, std::function<void()> _EndFunc);

	EngineWindow();
	~EngineWindow();
};

