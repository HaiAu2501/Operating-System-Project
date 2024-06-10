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
    std::cout << std::setw(20) << "Command" << ": Description" << std::endl;
    std::cout << std::setw(20) << "--------------------" << "--------------------" << std::endl;
    std::cout << std::setw(20) << "delete" << ": Delete a directory" << std::endl;
    std::cout << std::setw(20) << "move" << ": Move a directory" << std::endl;
    std::cout << std::setw(20) << "list_tree" << ": List the directory tree" << std::endl;
    std::cout << std::setw(20) << "create" << ": Create a directory" << std::endl;
    std::cout << std::setw(20) << "copy" << ": Copy a directory" << std::endl;
    std::cout << std::setw(20) << "open" << ": Open a file" << std::endl;
    std::cout << std::setw(20) << "rename" << ": Rename a file" << std::endl;
    std::cout << std::setw(20) << "--------------------" << "--------------------" << std::endl;   
    std::cout << std::setw(20) << "start_foreground" << ": Start a process in foreground" << std::endl;
    std::cout << std::setw(20) << "start_background" << ": Start a process in background" << std::endl;
    std::cout << std::setw(20) << "terminate" << ": Terminate a process" << std::endl;
    std::cout << std::setw(20) << "list_processes" << ": List running processes" << std::endl;
    std::cout << std::setw(20) << "child" << ": Start a child process" << std::endl;
    std::cout << std::setw(20) << "manage_threads" << ": Manage threads" << std::endl;
    std::cout << std::setw(20) << "list_children" << ": Print all children processes" << std::endl;
    std::cout << std::setw(20) << "suspend" << ": Suspend a process" << std::endl;
    std::cout << std::setw(20) << "resume" << ": Resume a process" << std::endl;
    std::cout << std::setw(20) << "--------------------" << "--------------------" << std::endl;
    std::cout << std::setw(20) << "run" << ": Run a script" << std::endl;
    std::cout << std::setw(20) << "calculator" << ": Open the calculator" << std::endl;
    std::cout << std::setw(20) << "time" << ": Show system time" << std::endl;
    std::cout << std::setw(20) << "date" << ": Show system date" << std::endl;
    std::cout << std::setw(20) << "uptime" << ": Show system uptime" << std::endl;
    std::cout << std::setw(20) << "cpuinfo" << ": Show CPU information" << std::endl;
    std::cout << std::setw(20) << "meminfo" << ": Show memory information" << std::endl;
    std::cout << std::setw(20) << "diskinfo" << ": Show disk information" << std::endl;
    std::cout << std::setw(20) << "--------------------" << "--------------------" << std::endl;
    std::cout << std::setw(20) << "change_color" << ": Change text color" << std::endl;
    std::cout << std::setw(20) << "calculate" << ": Calculate expression value" << std::endl;
    std::cout << std::setw(20) << "function" << ": Define a function" << std::endl;
    std::cout << std::setw(20) << "evaluate" << ": Evaluate a function" << std::endl;
    std::cout << std::setw(20) << "if else" << ": Conditional execution" << std::endl;
    std::cout << std::setw(20) << "loop" << ": Loop expression" << std::endl;
    std::cout << std::setw(20) << "convert" << ": Number base convertion" << std::endl;
    std::cout << std::setw(20) << "alias" << ": Create command alias" << std::endl;
    std::cout << std::setw(20) << "unalias" << ": Remove command alias" << std::endl;
    std::cout << std::setw(20) << "--------------------" << "--------------------" << std::endl;
    std::cout << std::setw(20) << "add_path" << ": Add a path to PATH" << std::endl;
    std::cout << std::setw(20) << "remove_path" << ": Remove a path from PATH" << std::endl;
    std::cout << std::setw(20) << "print_env" << ": Print environment variable" << std::endl;
    std::cout << std::setw(20) << "set_env" << ": Set environment variable" << std::endl;
    std::cout << std::setw(20) << "unset_env" << ": Unset environment variable" << std::endl;
    std::cout << std::setw(20) << "is_in_path" << ": Check if a path is in PATH" << std::endl;
    std::cout << std::setw(20) << "list_env" << ": List all environment variables" << std::endl;
    std::cout << std::setw(20) << "save_env" << ": Save environment variables to file" << std::endl;
    std::cout << std::setw(20) << "load_env" << ": Load environment variables from file" << std::endl;
    std::cout << std::setw(20) << "--------------------" << "--------------------" << std::endl;
    std::cout << std::setw(20) << "write_file" << ": Write content to file" << std::endl;
    std::cout << std::setw(20) << "read_file" << ": Read content from file" << std::endl;
    std::cout << std::setw(20) << "file_size" << ": Get file size" << std::endl;
    std::cout << std::setw(20) << "--------------------" << "--------------------" << std::endl;
    std::cout << std::setw(20) << "dancing" << ": Show dancing faces" << std::endl;
    std::cout << std::setw(20) << "playing" << ": Start a Tic-Tac-Toe game" << std::endl;
    std::cout << std::setw(20) << "duck" << ": Show a duck" << std::endl;
    std::cout << std::setw(20) << "--------------------" << "--------------------" << std::endl;
    std::cout << std::setw(20) << "cd" << ": Change directory" << std::endl;
    std::cout << std::setw(20) << "dir" << ": List directory contents" << std::endl;
    std::cout << std::setw(20) << "pwd" << ": Print working directory" << std::endl;
    std::cout << std::setw(20) << "exit" << ": Exit the shell" << std::endl;
    std::cout << std::setw(20) << "help" << ": Show this help message" << std::endl;
    std::cout << std::setw(20) << "history" << ": Show history" << std::endl;
    std::cout << std::setw(20) << "clear" << ": Clear screen" << std::endl;
    std::cout << std::setw(20) << "clear_history" << ": Clear history" << std::endl;
}

#endif // HELP_COMMAND_H
