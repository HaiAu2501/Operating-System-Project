// clear_screen.h
#ifndef CLEAR_SCREEN_H
#define CLEAR_SCREEN_H

#include <windows.h>

// Hàm xóa màn hình
void clearScreen()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = {0, 0};

    if (hStdOut == INVALID_HANDLE_VALUE)
        return;

    // Lấy thông tin buffer hiện tại
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
        return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // Lấp đầy màn hình với khoảng trắng
    if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, homeCoords, &count))
        return;

    // Đặt lại các thuộc tính màn hình hiện tại
    if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count))
        return;

    // Đặt lại con trỏ về vị trí đầu tiên
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

#endif // CLEAR_SCREEN_H
