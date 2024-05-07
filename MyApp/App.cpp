#include <Windows.h>
#include <MyEngine/EngineCore.h>
#pragma comment(lib, "MyEngine.lib")
#pragma comment(lib, "MyContents.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    EngineCore::EngineStart(hInstance);
}