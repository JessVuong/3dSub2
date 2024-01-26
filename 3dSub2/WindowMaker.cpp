#include "WindowMaker.h"

int WindowInit(_In_ HINSTANCE hInstance)
{
    const auto pClassName = L"3DSub2";
    //register window class
    WNDCLASSEX wc = { 0 };
    //important descriptors
    wc.cbSize = sizeof(wc);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = DefWindowProc; 
    wc.hInstance = hInstance;
    wc.lpszClassName = pClassName;

    // less important, set to null
    wc.cbClsExtra = 0;
    wc.hIcon = nullptr;
    wc.hIconSm = nullptr;
    wc.hCursor = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;

    RegisterClassEx(&wc);

    //create window
    HWND hWnd = CreateWindowEx(0, pClassName, L"Window", WS_CAPTION , 200, 200, 640, 480, nullptr, nullptr, hInstance, nullptr);

    //show window
    ShowWindow(hWnd, SW_SHOW);

    while (true);
    return 0;
}