#ifndef START_PROCESS_H
#define START_PROCESS_H

#include <iostream>
#include <vector>
#include <windows.h>

void startProcess(const std::vector<std::string> &args)
{
    if (args.size() < 1)
    {
        std::cout << "Usage: start <executable_path> [arguments...]" << std::endl;
        return;
    }

    std::string command = args[0];
    for (size_t i = 1; i < args.size(); ++i)
    {
        command += " " + args[i];
    }

    STARTUPINFOA si = {sizeof(si)};
    PROCESS_INFORMATION pi;
    if (!CreateProcessA(NULL, &command[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        std::cerr << "Failed to start process: " << GetLastError() << std::endl;
        return;
    }
    std::cout << "Started process with PID: " << pi.dwProcessId << std::endl;
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

#endif // START_PROCESS_H
