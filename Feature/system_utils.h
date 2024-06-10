#ifndef SYSTEM_UTILS_H
#define SYSTEM_UTILS_H

#include <iostream>
#include <ctime>
#include <windows.h>
#include <unordered_set>

class SystemUtils
{
public:
    // Danh sách các lệnh hỗ trợ
    static const std::unordered_set<std::string> supportedCommands;

    // Hàm lấy danh sách các lệnh hỗ trợ
    static const std::unordered_set<std::string> &getSupportedCommands()
    {
        return supportedCommands;
    }

    void showSystemTime(const std::vector<std::string> &args)
    {
        if (!args.empty())
        {
            std::cerr << "Usage: time" << std::endl;
            return;
        }

        std::time_t t = std::time(nullptr);
        std::tm *now = std::localtime(&t);

        std::cout << "Current system time: "
                  << (now->tm_year + 1900) << '-'
                  << (now->tm_mon + 1) << '-'
                  << now->tm_mday << ' '
                  << now->tm_hour << ':'
                  << now->tm_min << ':'
                  << now->tm_sec
                  << std::endl;
    }

    void showSystemDate(const std::vector<std::string> &args)
    {
        if (!args.empty())
        {
            std::cerr << "Usage: date" << std::endl;
            return;
        }

        std::time_t t = std::time(nullptr);
        std::tm *now = std::localtime(&t);

        std::cout << "Current system date: "
                  << (now->tm_year + 1900) << '-'
                  << (now->tm_mon + 1) << '-'
                  << now->tm_mday
                  << std::endl;
    }

    void showSystemUptime(const std::vector<std::string> &args)
    {
        if (!args.empty())
        {
            std::cerr << "Usage: uptime" << std::endl;
            return;
        }

        DWORD uptime = GetTickCount64() / 1000; // Get system uptime in seconds
        DWORD seconds = uptime % 60;
        DWORD minutes = (uptime / 60) % 60;
        DWORD hours = (uptime / 3600) % 24;
        DWORD days = uptime / 86400;

        std::cout << "System uptime: "
                  << days << " days, "
                  << hours << " hours, "
                  << minutes << " minutes, "
                  << seconds << " seconds"
                  << std::endl;
    }

    void showCPUInfo(const std::vector<std::string> &args)
    {
        if (!args.empty())
        {
            std::cerr << "Usage: cpuinfo" << std::endl;
            return;
        }

        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);

        std::cout << "CPU Information:" << std::endl;
        std::cout << "Number of processors: " << sysInfo.dwNumberOfProcessors << std::endl;
        std::cout << "Processor type: " << sysInfo.dwProcessorType << std::endl;
    }

    void showMemoryInfo(const std::vector<std::string> &args)
    {
        if (!args.empty())
        {
            std::cerr << "Usage: meminfo" << std::endl;
            return;
        }

        MEMORYSTATUSEX statex;
        statex.dwLength = sizeof(statex);
        GlobalMemoryStatusEx(&statex);

        std::cout << "Memory Information:" << std::endl;
        std::cout << "Total physical memory: " << statex.ullTotalPhys / (1024 * 1024) << " MB" << std::endl;
        std::cout << "Available physical memory: " << statex.ullAvailPhys / (1024 * 1024) << " MB" << std::endl;
        std::cout << "Total virtual memory: " << statex.ullTotalPageFile / (1024 * 1024) << " MB" << std::endl;
        std::cout << "Available virtual memory: " << statex.ullAvailPageFile / (1024 * 1024) << " MB" << std::endl;
    }

    void showDiskInfo(const std::vector<std::string> &args)
    {
        if (args.size() != 1)
        {
            std::cerr << "Usage: diskinfo <drive_letter>" << std::endl;
            return;
        }

        std::string drive = args[0] + ":\\";
        ULARGE_INTEGER freeBytesAvailableToCaller, totalNumberOfBytes, totalNumberOfFreeBytes;

        if (GetDiskFreeSpaceExA(drive.c_str(), &freeBytesAvailableToCaller, &totalNumberOfBytes, &totalNumberOfFreeBytes))
        {
            std::cout << "Disk Information for drive " << drive << ":" << std::endl;
            std::cout << "Total space: " << totalNumberOfBytes.QuadPart / (1024 * 1024 * 1024) << " GB" << std::endl;
            std::cout << "Free space: " << totalNumberOfFreeBytes.QuadPart / (1024 * 1024 * 1024) << " GB" << std::endl;
        }
        else
        {
            std::cerr << "Failed to get disk information: " << GetLastError() << std::endl;
        }
    }

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
};

const std::unordered_set<std::string> SystemUtils::supportedCommands = {
    "time",
    "date",
    "uptime",
    "cpuinfo",
    "meminfo",
    "diskinfo",
    "calculator"};

#endif // SYSTEM_UTILS_H
