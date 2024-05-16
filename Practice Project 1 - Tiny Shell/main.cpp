#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Feature/features.h"

void executeCommand(const std::string &command, const std::vector<std::string> &args)
{
    if (command == "delete")
    {
        deleteDirectory(args);
    }
    else if (command == "move")
    {
        moveDirectory(args);
    }
    else if (command == "open")
    {
        openFile(args);
    }
    else if (command == "exit")
    {
        exitShell();
        exit(0); // Exit the program
    }
    else if (command == "list_tree")
    {
        listDirectoryTree(args);
    }
    else if (command == "create")
    {
        createDirectory(args);
    }
    else if (command == "copy")
    {
        copyDirectory(args);
    }
    else if (command == "run")
    {
        runScript(args);
    }
    else if (command == "help")
    {
        help(args);
    }
    else if (command == "rename")
    {
        renameFile(args);
    }
    else if (command == "cd")
    {
        changeDirectory(args);
    }
    else if (command == "dir")
    {
        listDirectoryContents(args);
    }
    else if (command == "pwd")
    {
        printWorkingDirectory(args);
    }
    else if (command == "start")
    {
        startProcess(args);
    }
    else if (command == "terminate")
    {
        terminateProcess(args);
    }
    else if (command == "list_processes")
    {
        listProcesses(args);
    }
    else if (command == "start_child")
    {
        startChildProcess();
    }
    else if (command == "manage_threads")
    {
        handleManageThreadsCommand(args);
    }
    else
    {
        std::cout << "Unknown command: " << command << std::endl;
    }
}

std::vector<std::string> splitInput(const std::string &input)
{
    std::vector<std::string> tokens;
    std::string token;
    bool inQuotes = false;
    for (char ch : input)
    {
        if (ch == '\"')
        {
            inQuotes = !inQuotes;
        }
        else if (ch == ' ' && !inQuotes)
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
        }
        else
        {
            token += ch;
        }
    }
    if (!token.empty())
    {
        tokens.push_back(token);
    }
    return tokens;
}

int main()
{
    std::string input;
    while (true)
    {
        std::cout << "tiny_shell> ";
        std::getline(std::cin, input);

        std::vector<std::string> tokens = splitInput(input);

        if (tokens.empty())
            continue;

        std::string command = tokens[0];
        tokens.erase(tokens.begin());
        executeCommand(command, tokens);
    }
    return 0;
}