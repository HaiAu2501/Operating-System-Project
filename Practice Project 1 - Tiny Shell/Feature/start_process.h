#ifndef START_PROCESS_H
#define START_PROCESS_H

#include <iostream>
#include <vector>
#include <windows.h>
#include <tlhelp32.h>

DWORD findChildProcess(DWORD parentPID)
{
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Failed to create process snapshot: " << GetLastError() << std::endl;
        return 0;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32))
    {
        std::cerr << "Failed to retrieve process information: " << GetLastError() << std::endl;
        CloseHandle(hProcessSnap);
        return 0;
    }

    DWORD childPID = 0;
    do
    {
        if (pe32.th32ParentProcessID == parentPID)
        {
            childPID = pe32.th32ProcessID;
            break;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return childPID;
}

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
    if (!CreateProcessA(NULL, &command[0], NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
    {
        std::cerr << "Failed to start process: " << GetLastError() << std::endl;
        return;
    }
    std::cout << "Started process with PID: " << pi.dwProcessId << std::endl;

    // Wait a bit and check for child processes
    Sleep(1000);
    DWORD childPID = findChildProcess(pi.dwProcessId);
    if (childPID != 0)
    {
        std::cout << "Detected child process with PID: " << childPID << std::endl;
    }
    else
    {
        std::cout << "No child process detected for PID: " << pi.dwProcessId << std::endl;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

void startChildProcess()
{
    std::vector<std::string> args = {"child_process.exe"};
    startProcess(args);
}

#endif // START_PROCESS_H
