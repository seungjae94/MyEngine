#include "PreCompile.h"
#include "EngineWindow.h"

HINSTANCE EngineWindow::hInstance = nullptr;
bool EngineWindow::WindowOn = true;

EngineWindow::EngineWindow()
{
}

EngineWindow::~EngineWindow()
{
}

void EngineWindow::Off()
{
    WindowOn = false;
}

LRESULT EngineWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        WindowOn = false;
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void EngineWindow::Open(HINSTANCE _hInstance)
{
    // MyRegisterClass
    WNDCLASSEXA wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInstance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hCursor = nullptr;
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "WindowClass";
    wcex.hIconSm = nullptr;

    RegisterClassExA(&wcex);

    // InitInstance
    hInstance = _hInstance;

    HWND hWnd = CreateWindowA(wcex.lpszClassName, "Title", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        assert(false);
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
}

int EngineWindow::MessageLoop(std::function<void()> _UpdateFunc, std::function<void()> _EndFunc)
{
    MSG msg = {};

    while (WindowOn)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (nullptr != _UpdateFunc)
        {
            _UpdateFunc();
        }
    }

    _EndFunc();

    return (int)msg.wParam;
}