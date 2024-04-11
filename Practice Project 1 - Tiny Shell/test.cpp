#include <iostream>
#include <string>
#include <windows.h>

void ExecuteCommand(const std::string &command)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Tạo một chuỗi lệnh có thể thay đổi được
    char cmd[1024];
    strncpy(cmd, command.c_str(), sizeof(cmd));
    cmd[sizeof(cmd) - 1] = 0; // Đảm bảo chuỗi kết thúc bằng null

    // Tạo quy trình con để thực thi lệnh
    if (!CreateProcess(NULL,                          // Không sử dụng module name
                       reinterpret_cast<LPWSTR>(cmd), // Command line
                       NULL,                          // Process handle not inheritable
                       NULL,                          // Thread handle not inheritable
                       FALSE,                         // Set handle inheritance to FALSE
                       0,                             // No creation flags
                       NULL,                          // Use parent's environment block
                       NULL,                          // Use parent's starting directory
                       &si,                           // Pointer to STARTUPINFO structure
                       &pi)                           // Pointer to PROCESS_INFORMATION structure
    )
    {
        std::cout << "CreateProcess failed (" << GetLastError() << ").\n";
    }
    else
    {
        // Wait until child process exits.
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Close process and thread handles.
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

int main()
{
    std::string input;

    while (true)
    {
        std::cout << "TinyShell> ";
        std::getline(std::cin, input);

        // Simple command handling
        if (input == "exit")
        {
            break;
        }
        else
        {
            ExecuteCommand(input);
        }
    }

    return 0;
}
