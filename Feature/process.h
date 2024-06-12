#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <tlhelp32.h>
#include <unordered_set>
#include <set>
#include <locale>
#include <codecvt>
#include <iomanip>

using namespace std;

class ProcessManager
{
public:
    static const std::unordered_set<std::string> supportedCommands;

    static const std::unordered_set<std::string> &getSupportedCommands()
    {
        return supportedCommands;
    }

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

    void startProcessForeground(const std::vector<std::string> &args)
    {
        if (args.size() < 1)
        {
            std::cerr << "Usage: start_foreground <command>" << std::endl;
            return;
        }

        std::string command = args[0];
        for (size_t i = 1; i < args.size(); ++i)
        {
            command += " " + args[i];
        }

        STARTUPINFOA si = {sizeof(si)};
        PROCESS_INFORMATION pi;
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

    void startProcessBackground(const std::vector<std::string> &args)
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
        ZeroMemory(&pi, sizeof(pi));

        char *cmd = new char[command.length() + 1];
        strcpy(cmd, command.c_str());

        if (!CreateProcessA(NULL, cmd, NULL, NULL, TRUE, CREATE_NEW_PROCESS_GROUP, NULL, NULL, &si, &pi))
        {
            std::cerr << "Failed to start process: " << GetLastError() << std::endl;
            delete[] cmd; // Giải phóng bộ nhớ
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
        delete[] cmd; // Giải phóng bộ nhớ
    }

    // Nhóm Forground | Nhóm này không nên chạy Background
    void startTicTacToe()
    {
        std::vector<std::string> args = {"Process/tictactoe.exe"};
        startProcessForeground(args);
    }

    void startDuck()
    {
        std::vector<std::string> args = {"Process/duck.exe"};
        startProcessForeground(args);
    }

    // Nhóm Background | Nhóm này vẫn có thể chạy Foreground
    void startCountdownProcess()
    {
        std::vector<std::string> args = {"Process/countdown.exe"};
        startProcessBackground(args);
    }

    void startChildProcess()
    {
        std::vector<std::string> args = {"Process/child.exe"};
        startProcessBackground(args);
    }

    void suspendProc(const vector<string> &args)
    {
        if (args.size() != 1)
        {
            cerr << "Usage: suspend <PID>\n";
            return;
        }
        DWORD dwProcessId = stoul(args[0]);

        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
        if (hSnapshot == INVALID_HANDLE_VALUE)
        {
            cerr << "System error!\n";
            return;
        }

        THREADENTRY32 te;
        te.dwSize = sizeof(THREADENTRY32);

        if (!Thread32First(hSnapshot, &te))
        {
            CloseHandle(hSnapshot);
            cerr << "System error!\n";
            return;
        }

        do
        {
            if (te.th32OwnerProcessID == dwProcessId)
            {
                HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te.th32ThreadID);
                if (hThread != NULL)
                {
                    SuspendThread(hThread);
                    CloseHandle(hThread);
                }
                else
                {
                    cerr << "System error!\n";
                    return;
                }
            }
        } while (Thread32Next(hSnapshot, &te));

        CloseHandle(hSnapshot);
    }

    void resumeProc(const vector<string> &args)
    {
        if (args.size() != 1)
        {
            cerr << "Usage: resume <PID>\n";
            return;
        }
        DWORD dwProcessId = stoul(args[0]);

        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
        if (hSnapshot == INVALID_HANDLE_VALUE)
        {
            cerr << "System error!\n";
            return;
        }

        THREADENTRY32 te;
        te.dwSize = sizeof(THREADENTRY32);

        if (!Thread32First(hSnapshot, &te))
        {
            CloseHandle(hSnapshot);
            cerr << "System error!\n";
            return;
        }

        do
        {
            if (te.th32OwnerProcessID == dwProcessId)
            {
                HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te.th32ThreadID);
                if (hThread != NULL)
                {
                    ResumeThread(hThread);
                    CloseHandle(hThread);
                }
                else
                {
                    cerr << "System error!\n";
                    return;
                }
            }
        } while (Thread32Next(hSnapshot, &te));

        CloseHandle(hSnapshot);
    }

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

        std::cout << std::left << std::setw(8) << "PID" << std::setw(50) << "Process Name" << "Status" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        do
        {
#ifdef UNICODE
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::string processName = converter.to_bytes(pe32.szExeFile);
#else
            std::string processName = pe32.szExeFile;
#endif

            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pe32.th32ProcessID);
            std::string processStatus = "Unknown";
            if (hProcess)
            {
                DWORD exitCode;
                if (GetExitCodeProcess(hProcess, &exitCode))
                {
                    if (exitCode == STILL_ACTIVE)
                    {
                        processStatus = "Running";
                    }
                    else
                    {
                        processStatus = "Terminated";
                    }
                }
                CloseHandle(hProcess);
            }
            else
            {
                processStatus = "Access Denied";
            }

            std::cout << std::left << std::setw(8) << pe32.th32ProcessID << std::setw(50) << processName << processStatus << std::endl;
        } while (Process32Next(hProcessSnap, &pe32));

        CloseHandle(hProcessSnap);
    }

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
};

const std::unordered_set<std::string> ProcessManager::supportedCommands = {
    "start_foreground",
    "start_background",
    "tictactoe",
    "duck",
    "countdown",
    "child",
    "suspend",
    "resume",
    "list_processes",
    "terminate",
    "list_children"};

#endif // PROCESS_H