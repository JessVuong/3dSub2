#include <Windows.h>
#include <iostream>
#include "WindowHelper.h"
#include "WindowMaker.h"

int WINAPI WinMain(
    _In_        HINSTANCE   hInstance,
    _In_opt_    HINSTANCE   hPrevInstance,
    _In_        LPSTR       lpCmdLine,
    _In_        int         nShowCmd)
{

    WindowInit(hInstance);

    const UINT WIDTH = 1024;
    const UINT HEIGHT = 576;
    HWND window;

    if (!SetupWindow(hInstance, WIDTH, HEIGHT, nShowCmd, window))
    {
        std::cerr << "Failed to setup window!" << std::endl;
        return -1;
    }

    return 0;
}
