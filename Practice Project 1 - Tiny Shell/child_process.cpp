#include <windows.h>
#include <string>
#include <thread>
#include <chrono>

// Global variables
HINSTANCE hInst;
const wchar_t CLASS_NAME[] = L"CountdownWindowClass";
HWND hWnd;
int countdown = 10;

// Function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void UpdateCountdown();

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    hInst = hInstance;

    // Register the window class
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = CLASS_NAME;
    wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    if (!RegisterClassExW(&wcex))
    {
        MessageBoxW(nullptr, L"Call to RegisterClassEx failed!", L"Win32 Guided Tour", 0);
        return 1;
    }

    // Create the window
    hWnd = CreateWindowW(
        CLASS_NAME,
        L"Countdown",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        300, 200,
        nullptr, nullptr,
        hInstance, nullptr);

    if (!hWnd)
    {
        MessageBoxW(nullptr, L"Call to CreateWindow failed!", L"Win32 Guided Tour", 0);
        return 1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Start the countdown in a separate thread
    std::thread countdownThread(UpdateCountdown);
    countdownThread.detach();

    // Main message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

void UpdateCountdown()
{
    while (countdown > 0)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        --countdown;
        InvalidateRect(hWnd, nullptr, TRUE);
    }
    PostMessage(hWnd, WM_CLOSE, 0, 0);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    wchar_t buffer[256];

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        swprintf(buffer, sizeof(buffer) / sizeof(wchar_t), L"Countdown: %d seconds remaining", countdown);
        TextOutW(hdc, 50, 50, buffer, wcslen(buffer));
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}