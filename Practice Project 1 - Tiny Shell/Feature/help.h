#ifndef HELP_H
#define HELP_H

#include <iostream>
#include <vector>

void help(const std::vector<std::string> &args)
{
    std::cout << "Tiny Shell supports the following commands:\n";
    std::cout << "  delete <directory_path>          - Delete a directory and its contents\n";
    std::cout << "  move <source_path> <destination_path> - Move a directory or file\n";
    std::cout << "  open <file_path>                - Open a file\n";
    std::cout << "  exit                            - Exit the shell\n";
    std::cout << "  list_tree <directory_path>      - List directory tree\n";
    std::cout << "  create <directory_path>         - Create a new directory\n";
    std::cout << "  copy <source_path> <destination_path> - Copy a directory or file\n";
    std::cout << "  run <script_file_path>          - Run a script file containing shell commands\n";
    std::cout << "  help                            - Show this help message\n";
}

#endif // HELP_H
