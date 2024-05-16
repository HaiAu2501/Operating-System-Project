#ifndef LIST_PROCESSES_H
#define LIST_PROCESSES_H

#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>

void listProcesses(const std::vector<std::string> &args)
{
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Failed to create process snapshot: " << GetLastError() << std::endl;
        return;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32))
    {
        std::cerr << "Failed to retrieve process information: " << GetLastError() << std::endl;
        CloseHandle(hProcessSnap);
        return;
    }

    std::cout << "PID\tProcess Name" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    do
    {
#ifdef UNICODE
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::string processName = converter.to_bytes(pe32.szExeFile);
#else
        std::string processName = pe32.szExeFile;
#endif
        std::cout << pe32.th32ProcessID << "\t" << processName << std::endl;
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
}

#endif // LIST_PROCESSES_H
