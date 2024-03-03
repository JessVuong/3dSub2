#include <Windows.h>
#include <iostream>
#include "WindowMaker.h"

#include "GraphicHandler.cpp"

int WINAPI WinMain(
    _In_        HINSTANCE   hInstance,
    _In_opt_    HINSTANCE   hPrevInstance,
    _In_        LPSTR       lpCmdLine,
    _In_        int         nShowCmd)
{

    const UINT WIDTH = 1024;
    const UINT HEIGHT = 576;
    HWND window = WindowInit(hInstance, WIDTH, HEIGHT);

    window = WindowInit(hInstance, WIDTH, HEIGHT);

    /*if (!SetupWindow(hInstance, WIDTH, HEIGHT, nShowCmd, window))
    {
        std::cerr << "Failed to setup window!" << std::endl;
        return -1;
    }*/
    //Copy this and make it work maybe?

    if (!window)
    {
        std::cerr << "Failed to create window!" << std::endl;
        return -1;
    }

    //Use the directX class, GRaphicHelper
    GraphicHandler graphicHandler(window, WIDTH, HEIGHT);

    //Hav not changed
    //The message pump or loop
    MSG message;

    while (true)
    {
        while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);

            if (message.message == WM_QUIT)
            {
                return 0;
            }
        }

        // Code
        // Add the graphichandler shit
        graphicHandler.RenderFrame();
    }

    return 0;
}
