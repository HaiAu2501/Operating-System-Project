#ifndef HELP_COMMAND_H
#define HELP_COMMAND_H

#include <iostream>
#include <vector>
#include <iomanip>

void showHelp(const std::vector<std::string> &args)
{
    if (!args.empty())
    {
        std::cerr << "Usage: help" << std::endl;
        return;
    }

    std::cout << std::left;
    std::cout << std::setw(20) << "Command" << "Description" << std::endl;
    std::cout << std::setw(20) << "-------" << "-----------" << std::endl;
    std::cout << std::setw(20) << "delete" << ": Delete a directory" << std::endl;
    std::cout << std::setw(20) << "move" << ": Move a directory" << std::endl;
    std::cout << std::setw(20) << "list_tree" << ": List the directory tree" << std::endl;
    std::cout << std::setw(20) << "create" << ": Create a directory" << std::endl;
    std::cout << std::setw(20) << "copy" << ": Copy a directory" << std::endl;
    std::cout << std::setw(20) << "open" << ": Open a file" << std::endl;
    std::cout << std::setw(20) << "rename" << ": Rename a file" << std::endl;
    std::cout << std::setw(20) << "-------" << "-----------" << std::endl;
    std::cout << std::setw(20) << "start" << ": Start a process" << std::endl;
    std::cout << std::setw(20) << "start_foreground" << ": Start a process in foreground" << std::endl;
    std::cout << std::setw(20) << "start_background" << ": Start a process in background" << std::endl;
    std::cout << std::setw(20) << "terminate" << ": Terminate a process" << std::endl;
    std::cout << std::setw(20) << "list_processes" << ": List running processes" << std::endl;
    std::cout << std::setw(20) << "start_child" << ": Start a child process" << std::endl;
    std::cout << std::setw(20) << "manage_threads" << ": Manage threads" << std::endl;
    std::cout << std::setw(20) << "list_children" << ": Print all children processes" << std::endl;
    std::cout << std::setw(20) << "-------" << "-----------" << std::endl;
    std::cout << std::setw(20) << "run" << ": Run a script" << std::endl;
    std::cout << std::setw(20) << "calculator" << ": Open the calculator" << std::endl;
    std::cout << std::setw(20) << "time" << ": Show system time" << std::endl;
    std::cout << std::setw(20) << "date" << ": Show system date" << std::endl;
    std::cout << std::setw(20) << "uptime" << ": Show system uptime" << std::endl;
    std::cout << std::setw(20) << "cpuinfo" << ": Show CPU information" << std::endl;
    std::cout << std::setw(20) << "meminfo" << ": Show memory information" << std::endl;
    std::cout << std::setw(20) << "diskinfo" << ": Show disk information" << std::endl;
    std::cout << std::setw(20) << "-------" << "-----------" << std::endl;
    std::cout << std::setw(20) << "calculate" << ": Calculate expression value" << std::endl;
    std::cout << std::setw(20) << "dancing" << ": Show dancing faces" << std::endl;
    std::cout << std::setw(20) << "-------" << "-----------" << std::endl;
    std::cout << std::setw(20) << "cd" << ": Change directory" << std::endl;
    std::cout << std::setw(20) << "dir" << ": List directory contents" << std::endl;
    std::cout << std::setw(20) << "pwd" << ": Print working directory" << std::endl;
    std::cout << std::setw(20) << "exit" << ": Exit the shell" << std::endl;
    std::cout << std::setw(20) << "help" << ": Show this help message" << std::endl;
    std::cout << std::setw(20) << "history" << ": Show history" << std::endl;
    std::cout << std::setw(20) << "clear" << ": Clear screen" << std::endl;
}

#endif // HELP_COMMAND_H
