#ifndef RUN_SCRIPT_H
#define RUN_SCRIPT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "delete_directory.h"
#include "move_directory.h"
#include "open_file.h"
#include "exit_shell.h"
#include "list_directory_tree.h"
#include "create_directory.h"
#include "copy_directory.h"

void executeCommand(const std::string &command, const std::vector<std::string> &args);

std::vector<std::string> splitInput(const std::string &input);

void runScript(const std::vector<std::string> &args)
{
    if (args.size() != 1)
    {
        std::cout << "Usage: run <script_file_path>" << std::endl;
        return;
    }
    std::ifstream scriptFile(args[0]);
    if (!scriptFile)
    {
        std::cout << "Unable to open script file: " << args[0] << std::endl;
        return;
    }
    std::string line;
    while (std::getline(scriptFile, line))
    {
        std::vector<std::string> tokens = splitInput(line);
        if (!tokens.empty())
        {
            std::string command = tokens[0];
            tokens.erase(tokens.begin());
            executeCommand(command, tokens);
        }
    }
    scriptFile.close();
}

#endif // RUN_SCRIPT_H
