#include <iostream>
#include <thread> // Để sử dụng std::this_thread::sleep_for
#include <chrono> // Để sử dụng std::chrono::milliseconds

void dancing()
{
    const char *dance[] = {
        " ~~(^-^~~)",
        " ~~(^-^)~~",
        " (~~^-^)~~"};

    const int numDanceMoves = sizeof(dance) / sizeof(dance[0]);
    const int numLines = 30;
    const int delayMilliseconds = 500;

    for (int i = 0; i < numLines; ++i)
    {
        std::cout << dance[i % numDanceMoves] << '\r';
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMilliseconds));
    }
}