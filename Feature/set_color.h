#ifndef SET_COLOR_H
#define SET_COLOR_H

#include <windows.h>
#include <iostream>
#include <string>

enum class ConsoleColor
{
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    YELLOW = 6,
    WHITE = 7,
    GRAY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_YELLOW = 14,
    BRIGHT_WHITE = 15
};

void setColor(ConsoleColor color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, static_cast<int>(color));
}

void resetColor()
{
    setColor(ConsoleColor::WHITE);
}

ConsoleColor parseColor(const std::string &colorName)
{
    if (colorName == "black")
        return ConsoleColor::BLACK;
    if (colorName == "blue")
        return ConsoleColor::BLUE;
    if (colorName == "green")
        return ConsoleColor::GREEN;
    if (colorName == "cyan")
        return ConsoleColor::CYAN;
    if (colorName == "red")
        return ConsoleColor::RED;
    if (colorName == "magenta")
        return ConsoleColor::MAGENTA;
    if (colorName == "yellow")
        return ConsoleColor::YELLOW;
    if (colorName == "white")
        return ConsoleColor::WHITE;
    if (colorName == "gray")
        return ConsoleColor::GRAY;
    if (colorName == "light_blue")
        return ConsoleColor::LIGHT_BLUE;
    if (colorName == "light_green")
        return ConsoleColor::LIGHT_GREEN;
    if (colorName == "light_cyan")
        return ConsoleColor::LIGHT_CYAN;
    if (colorName == "light_red")
        return ConsoleColor::LIGHT_RED;
    if (colorName == "light_magenta")
        return ConsoleColor::LIGHT_MAGENTA;
    if (colorName == "light_yellow")
        return ConsoleColor::LIGHT_YELLOW;
    if (colorName == "bright_white")
        return ConsoleColor::BRIGHT_WHITE;

    return ConsoleColor::WHITE; // Default color if no match
}

#endif // SET_COLOR_H
