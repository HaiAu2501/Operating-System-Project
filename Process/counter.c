#include <stdio.h>
#include <stdlib.h>

const int SPAN = 2;
const int BASE = 10;

void sleep_for(unsigned int secs);

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: counter <number>\n");
        return 1;
    }

    int n = 0;
    char *endptr = NULL;

    n = (int)strtol(argv[1], &endptr, BASE);

    if(*endptr != '\0') {
        printf("Invalid argument: %s\n", argv[1]);
        return 1;
    }

    for(int i = 0; i <= n; ++i) {
        printf("Second %d.\n", i);
        sleep_for(SPAN);
    }
    return 0;
}

#ifdef _WIN32
#include <windows.h>
void sleep_for(unsigned int seconds) {
    static const unsigned int milli_per_sec = 1000;
    Sleep(seconds * milli_per_sec);
}
#elif defined(__linux__)
#    include <unistd.h>
void sleep_for(unsigned int seconds) {
    sleep(seconds); // NOLINT
}
#endif