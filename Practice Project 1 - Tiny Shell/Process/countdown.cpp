#include <windows.h>
#include <tchar.h>
#include <cstdio>

// To compile: g++ -o countdown countdown.cpp -lgdi32

#define IDT_TIMER1 1

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int counter = 10;
    static HFONT hFont;

    switch (uMsg)
    {
    case WM_CREATE:
        // Set a timer to update the counter every second
        SetTimer(hwnd, IDT_TIMER1, 1000, (TIMERPROC)NULL);
        // Create a font for the text
        hFont = CreateFont(72, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                           OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
                           _T("Arial"));
        break;
    case WM_TIMER:
        if (wParam == IDT_TIMER1)
        {
            // Decrement the counter
            counter--;
            // Invalidate the window to force a redraw
            InvalidateRect(hwnd, NULL, TRUE);
            // Close the window when the counter reaches 0
            if (counter < 0)
            {
                KillTimer(hwnd, IDT_TIMER1);
                PostMessage(hwnd, WM_CLOSE, 0, 0);
            }
        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        // Set the background color
        SetBkColor(hdc, RGB(255, 255, 255));
        // Set the text color
        SetTextColor(hdc, RGB(0, 0, 0));
        // Select the font into the DC
        SelectObject(hdc, hFont);
        // Convert the counter to a string
        TCHAR szCounter[3];
        _stprintf(szCounter, _T("%d"), counter);
        // Get the dimensions of the window
        RECT rect;
        GetClientRect(hwnd, &rect);
        // Draw the text in the center of the window
        DrawText(hdc, szCounter, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hwnd, &ps);
    }
    break;
    case WM_DESTROY:
        DeleteObject(hFont);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    const TCHAR szWindowClass[] = _T("CountdownApp");
    const TCHAR szTitle[] = _T("Countdown Timer");

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = szWindowClass;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (!hwnd)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
