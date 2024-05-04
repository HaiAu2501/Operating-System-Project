#include <windows.h>
#include <iostream>
#include <string>

void ExecuteCommand(const std::string& command) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

    // Create a mutable copy of the command string for CreateProcess
    char cmd[1024];
    strncpy(cmd, command.c_str(), sizeof(cmd));
    cmd[sizeof(cmd) - 1] = 0;  // Ensure null termination in edge case

    // Start the child process
    if (!CreateProcess(
        NULL,   // No module name (use command line)
        cmd,                  // Command line
        NULL,                 // Process handle not inheritable
        NULL,                 // Thread handle not inheritable
        FALSE,                // Set handle inheritance to FALSE
        0,                    // No creation flags
        NULL,                 // Use parent's environment block
        NULL,                 // Use parent's starting directory
        &si,                  // Pointer to STARTUPINFO structure
        &pi)                  // Pointer to PROCESS_INFORMATION structure
    ) {
        std::cerr << "CreateProcess failed (" << GetLastError() << ").\n";
    } else {
        // Wait until child process exits.
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Close process and thread handles.
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

int main() {
    std::string input;
    std::cout << "Tiny Shell (type 'exit' to quit)\n";

    do {
        std::cout << "> ";
        std::getline(std::cin, input);

        // Handle exit command
        if (input.compare("exit") == 0) {
            break;
        }

        ExecuteCommand(input);
    } while (true);

    return 0;
}
