#include <stdio.h>
#include <unistd.h>
#include <string.h>

void clearScreen()
{
    printf("\033[H\033[J");
}

void printDuck(int position, int quack)
{
    for (int i = 0; i < position; i++)
    {
        printf(" ");
    }
    if (quack % 10 == 0)
    {
        printf("__(.)< QUACK\n");
    }
    else
    {
        printf("__(.)<\n");
    }
    for (int i = 0; i < position; i++)
    {
        printf(" ");
    }
    printf("\\___)   \n");
    for (int i = 0; i < position - 6; i++)
    { // Dịch làn sóng sang trái một chút
        printf(" ");
    }
    printf("~~~~~~~~~~~~~~~~~~\n");
}

int main()
{
    int width = 80; // Width of the terminal
    int position = 0;
    int quack = 0;

    while (1)
    {
        clearScreen();
        printDuck(position, quack);
        position++;
        quack++;
        if (position >= width)
        {
            position = 0;
        }
        usleep(100000); // Delay for 100 milliseconds
    }

    return 0;
}
