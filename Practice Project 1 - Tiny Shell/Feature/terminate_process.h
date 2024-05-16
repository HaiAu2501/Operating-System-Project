#ifndef TERMINATE_PROCESS_H
#define TERMINATE_PROCESS_H

#include <iostream>
#include <vector>
#include <windows.h>

void terminateProcess(const std::vector<std::string> &args)
{
    if (args.size() != 1)
    {
        std::cout << "Usage: terminate <pid>" << std::endl;
        return;
    }

    DWORD pid = std::stoul(args[0]);

    // Thử mở tiến trình với quyền truy cập thông tin và hủy bỏ
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_TERMINATE, FALSE, pid);
    if (!hProcess)
    {
        DWORD error = GetLastError();
        std::cerr << "Failed to open process for querying and termination: " << error << std::endl;

        if (error == ERROR_ACCESS_DENIED)
        {
            std::cerr << "Access denied. Please run the shell as administrator." << std::endl;
        }
        else if (error == ERROR_INVALID_PARAMETER)
        {
            std::cerr << "Invalid parameter. The process might not exist." << std::endl;
        }

        return;
    }

    if (!TerminateProcess(hProcess, 0))
    {
        DWORD error = GetLastError();
        std::cerr << "Failed to terminate process: " << error << std::endl;
    }
    else
    {
        std::cout << "Terminated process with PID: " << pid << std::endl;
    }

    CloseHandle(hProcess);
}

#endif // TERMINATE_PROCESS_H
