#ifndef PROCESS_MANAGEMENT_H
#define PROCESS_MANAGEMENT_H

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <tlhelp32.h>
#include <set>

// Hàm đợi tất cả tiến trình con của một tiến trình cha kết thúc
void waitForChildProcesses(DWORD parentPID)
{
    std::set<DWORD> childPIDs;
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Failed to create process snapshot: " << GetLastError() << std::endl;
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32))
    {
        std::cerr << "Failed to retrieve process information: " << GetLastError() << std::endl;
        CloseHandle(hProcessSnap);
        return;
    }

    do
    {
        if (pe32.th32ParentProcessID == parentPID)
        {
            childPIDs.insert(pe32.th32ProcessID);
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);

    for (auto pid : childPIDs)
    {
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
        if (hProcess)
        {
            WaitForSingleObject(hProcess, INFINITE);
            CloseHandle(hProcess);
            waitForChildProcesses(pid); // Đệ quy để đợi các tiến trình con của tiến trình con
        }
    }
}

void startProcessForeground(const std::string &command)
{
    STARTUPINFOA si = {sizeof(si)};
    PROCESS_INFORMATION pi;

    // Tạo một bản sao của command để có thể chỉnh sửa được
    char *cmd = new char[command.length() + 1];
    strcpy(cmd, command.c_str());

    if (!CreateProcessA(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        std::cerr << "Failed to start process: " << GetLastError() << std::endl;
        delete[] cmd; // Giải phóng bộ nhớ
        return;
    }

    // Đợi tiến trình chính kết thúc
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Đợi cho tất cả các tiến trình con của tiến trình chính kết thúc
    waitForChildProcesses(pi.dwProcessId);

    delete[] cmd; // Giải phóng bộ nhớ
}

void startProcessBackground(const std::string &command)
{
    STARTUPINFOA si = {sizeof(si)};
    PROCESS_INFORMATION pi;

    // Tạo một bản sao của command để có thể chỉnh sửa được
    char *cmd = new char[command.length() + 1];
    strcpy(cmd, command.c_str());

    if (!CreateProcessA(NULL, cmd, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
    {
        std::cerr << "Failed to start process: " << GetLastError() << std::endl;
        delete[] cmd; // Giải phóng bộ nhớ
        return;
    }

    std::cout << "Started process in background with PID: " << pi.dwProcessId << std::endl;

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    delete[] cmd; // Giải phóng bộ nhớ
}

void handleStartCommand(const std::vector<std::string> &args)
{
    if (args.size() < 2)
    {
        std::cerr << "Usage: start <foreground|background> <command>" << std::endl;
        return;
    }

    std::string mode = args[0];
    std::string command = args[1];
    for (size_t i = 2; i < args.size(); ++i)
    {
        command += " " + args[i];
    }

    if (mode == "foreground")
    {
        startProcessForeground(command);
    }
    else if (mode == "background")
    {
        startProcessBackground(command);
    }
    else
    {
        std::cerr << "Unknown mode: " << mode << std::endl;
        std::cerr << "Usage: start <foreground|background> <command>" << std::endl;
    }
}

#endif // PROCESS_MANAGEMENT_H
