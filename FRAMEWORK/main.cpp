#include <windows.h>
#include "framework.h"

framework fw;
HWND hwnd;
bool mouseclick = false;

LRESULT APIENTRY WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_CREATE:

        break;
    case WM_SIZE: 
        {
        UINT width = LOWORD(lParam);
        UINT height = HIWORD(lParam);
        
        fw.onResize(width, height);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_PAINT:
        fw.draw(hWnd);
        break;
    case WM_RBUTTONDOWN:
        fw.onRightMouseClick(LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_LBUTTONDOWN:
        fw.onLeftMouseClick(LOWORD(lParam), HIWORD(lParam));
        mouseclick = true;
        break;
    case WM_LBUTTONUP:
        mouseclick = false;
        break;
    case WM_MOUSEMOVE:
        if (mouseclick) {
            fw.onMouseEvent(LOWORD(lParam), HIWORD(lParam));
        }
        break;
    }



    return DefWindowProc(hWnd, message, wParam, lParam);
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    srand(time(0));
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"mainWindowClass";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"ROSCOFF FRAMEWORK WITH GDI",  // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);  
    fw.init();
    // Run the message loop.
    MSG msg = { };
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            fw.update();
            InvalidateRect(hwnd, NULL, TRUE); // send WM_PAINT msg each frame
        }
    }

    return 0;
}
