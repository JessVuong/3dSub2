#include <Windows.h>


int WINAPI WinMain(
    _In_        HINSTANCE   hInstance,
    _In_opt_    HINSTANCE   hPrevInstance,
    _In_        LPSTR       lpCmdLine,
    _In_        int         nShowCmd)
{
    const auto pClassName = "3DSub2";
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



    return 0;
}