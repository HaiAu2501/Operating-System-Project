#ifndef FIND_CHILD_PROCESSES_H
#define FIND_CHILD_PROCESSES_H

#include <iostream>
#include <vector>
#include <windows.h>
#include <tlhelp32.h>

// Hàm để tìm tất cả tiến trình con của một tiến trình cha
std::vector<DWORD> findAllChildProcesses(DWORD parentPID)
{
    std::vector<DWORD> childPIDs;
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Failed to create process snapshot: " << GetLastError() << std::endl;
        return childPIDs;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32))
    {
        std::cerr << "Failed to retrieve process information: " << GetLastError() << std::endl;
        CloseHandle(hProcessSnap);
        return childPIDs;
    }

    do
    {
        if (pe32.th32ParentProcessID == parentPID)
        {
            childPIDs.push_back(pe32.th32ProcessID);
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return childPIDs;
}

// Hàm để in ra tất cả tiến trình con của một tiến trình cha
void printAllChildProcesses(const std::vector<std::string> &args)
{
    if (args.size() != 1)
    {
        std::cerr << "Usage: list_children <parentPID>" << std::endl;
        return;
    }

    DWORD parentPID = std::stoul(args[0]);
    std::vector<DWORD> childPIDs = findAllChildProcesses(parentPID);

    if (childPIDs.empty())
    {
        std::cout << "No child processes found for PID: " << parentPID << std::endl;
    }
    else
    {
        std::cout << "Child processes of PID " << parentPID << ":" << std::endl;
        for (DWORD pid : childPIDs)
        {
            std::cout << "  PID: " << pid << std::endl;
        }
    }
}

#endif // FIND_CHILD_PROCESSES_H
