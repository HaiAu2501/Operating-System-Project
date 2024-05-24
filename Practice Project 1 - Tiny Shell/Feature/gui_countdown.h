#ifndef GUI_COUNTDOWN_H
#define GUI_COUNTDOWN_H

#include <windows.h>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>

std::atomic<bool> stopCountdown(false); // Biến toàn cục để dừng đếm ngược

// Hàm xử lý các thông điệp của cửa sổ
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Hàm để đếm ngược và hiển thị trong GUI
void countdown()
{
    const wchar_t CLASS_NAME[] = L"CountdownWindowClass";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0,                   // Optional window styles.
        CLASS_NAME,          // Window class
        L"Countdown",        // Window text
        WS_OVERLAPPEDWINDOW, // Window style
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
        NULL,                  // Parent window
        NULL,                  // Menu
        GetModuleHandle(NULL), // Instance handle
        NULL                   // Additional application data
    );

    if (hwnd == NULL)
    {
        return;
    }

    ShowWindow(hwnd, SW_SHOW);

    // Bộ đếm ngược từ 20 đến 0
    for (int i = 20; i >= 0 && !stopCountdown.load(); --i)
    {
        std::wstring text = std::to_wstring(i);
        SetWindowTextW(hwnd, L"Countdown");
        InvalidateRect(hwnd, NULL, TRUE);
        UpdateWindow(hwnd);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    DestroyWindow(hwnd);
}

// Hàm xử lý các thông điệp của cửa sổ
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rect;
        GetClientRect(hwnd, &rect);
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(0, 0, 0));
        std::wstring text = std::to_wstring(20); // Mặc định giá trị hiển thị
        DrawTextW(hdc, text.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        EndPaint(hwnd, &ps);
    }
        return 0;

    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
        {
            stopCountdown.store(true);
            DestroyWindow(hwnd);
        }
        return 0;
    }

    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

// Hàm để hiển thị bộ đếm ngược GUI
void showCountdownGUI(const std::vector<std::string> &args)
{
    stopCountdown.store(false); // Đặt lại biến đếm ngược
    std::thread countdownThread(countdown);
    countdownThread.join();
}

#endif // GUI_COUNTDOWN_H
