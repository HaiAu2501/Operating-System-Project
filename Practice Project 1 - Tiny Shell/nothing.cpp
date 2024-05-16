#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

// Khai báo các hàm cần thiết
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);
void RunCommand(HWND);

// Handle cho các control
HWND hInput;
HWND hOutput;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WndProc;

    if (!RegisterClassW(&wc))
        return -1;

    CreateWindowW(L"myWindowClass", L"Windows Command Interface", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  100, 100, 800, 600, NULL, NULL, NULL, NULL);

    MSG msg = {0};

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_COMMAND:
        if (wp == 1)
        {
            RunCommand(hWnd);
        }
        break;
    case WM_CREATE:
        AddControls(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd, msg, wp, lp);
    }
    return 0;
}

void AddControls(HWND hWnd)
{
    CreateWindowW(L"static", L"Enter Command:", WS_VISIBLE | WS_CHILD, 50, 50, 120, 40, hWnd, NULL, NULL, NULL);
    hInput = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 180, 50, 300, 40, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"button", L"Run", WS_VISIBLE | WS_CHILD, 490, 50, 80, 40, hWnd, (HMENU)1, NULL, NULL);
    hOutput = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 50, 100, 700, 400, hWnd, NULL, NULL, NULL);
}

// Định nghĩa hàm để thực thi lệnh và hiển thị kết quả
void RunCommand(HWND hWnd)
{
    char buffer[256];
    GetWindowTextA(hInput, buffer, 256);

    FILE *pipe = _popen(buffer, "r");
    if (!pipe)
        return;

    char output[1024];
    std::string result = "";
    while (!feof(pipe))
    {
        if (fgets(output, 1024, pipe) != NULL)
            result += output;
    }
    _pclose(pipe);

    SetWindowTextA(hOutput, result.c_str());
}
