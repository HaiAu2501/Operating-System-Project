#ifndef SHOW_CALCULATOR_H
#define SHOW_CALCULATOR_H

#include <iostream>
#include <vector>
#include <windows.h>

void showCalculator(const std::vector<std::string> &args)
{
    if (!args.empty())
    {
        std::cerr << "Usage: calculator" << std::endl;
        return;
    }

    STARTUPINFO si = {sizeof(si)};
    PROCESS_INFORMATION pi;

    if (!CreateProcess(TEXT("C:\\Windows\\System32\\calc.exe"), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        std::cerr << "Failed to start calculator: " << GetLastError() << std::endl;
        return;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

#endif // SHOW_CALCULATOR_H
