#include "WindowMaker.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

HWND WindowInit(_In_ HINSTANCE hInstance, UINT width, UINT height)
{
    const auto pClassName = L"3DSub2";
    //register window class
    WNDCLASSEX wc = { 0 };
    //important descriptors
    wc.cbSize = sizeof(wc);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WindowProc;
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
    HWND hWnd = CreateWindowEx(0, pClassName, L"Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, hInstance, nullptr);

    //show window
    ShowWindow(hWnd, SW_SHOW);

    return hWnd;
}