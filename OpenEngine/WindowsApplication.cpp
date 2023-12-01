#include "WindowsApplication.h"
#include<windowsx.h>
using namespace My;

My::WindowsApplication::WindowsApplication() {
    
}
static LRESULT CALLBACK TmpWndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uiMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, uiMsg, wParam, lParam);
    }

    return 0;
}
LRESULT My::WindowsApplication::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    
    // sort through and find what code to run for the message given
    switch (message)
    {

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        RECT rec = { 20, 20, 60, 80 };
        HBRUSH brush = (HBRUSH)GetStockObject(BLACK_BRUSH);

        FillRect(hdc, &rec, brush);

        EndPaint(hWnd, &ps);
    } break;
    // this message is read when the window is closed
    case WM_DESTROY:
    {
        // close the application entirely
        PostQuitMessage(0);
        return 0;
    } break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc(hWnd, message, wParam, lParam);
}
int WindowsApplication::GetName() {
    return 10;
}
int WindowsApplication::Initialize() {
    BaseApplication::Initialize();
    
    CreateMainWindow();
    return 0;
}
void WindowsApplication::Tick() {
    MSG msg;

    // wait for the next message in the queue, store the result in 'msg'
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

        // translate keystroke messages into the right format
        TranslateMessage(&msg);

        // send the message to the WindowProc function
        DispatchMessage(&msg);
    }

    // return this part of the WM_QUIT message to Windows
    
}

void WindowsApplication::Finalize() {

}
HWND WindowsApplication::GetWindowsHandler() {
    return mHWND;
}

void WindowsApplication::CreateMainWindow() {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    HWND hWnd;

    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = _T("MyG");

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(0,
        _T("MyG"),    // name of the window class
        _T("Hello, Engine!"),   // title of the window
        WS_OVERLAPPEDWINDOW,    // window style
        300,    // x-position of the window
        300,    // y-position of the window
        500,    // width of the window
        400,    // height of the window
        NULL,    // we have no parent window, NULL
        NULL,    // we aren't using menus, NULL
        hInstance,    // application handle
        this);    // used with multiple windows, NULL

    // display the window on the screen
    ShowWindow(hWnd, 5);
    
}