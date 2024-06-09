#ifndef LOOP_H
#define LOOP_H

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

void executeCommand(const std::string &command, const std::vector<std::string> &args);

// Hàm tách các lệnh bằng dấu '&'
std::vector<std::vector<std::string>> splitCommands(const std::vector<std::string> &args)
{
    std::vector<std::vector<std::string>> commands;
    std::vector<std::string> currentCommand;

    for (const std::string &arg : args)
    {
        if (arg == "&")
        {
            if (!currentCommand.empty())
            {
                commands.push_back(currentCommand);
                currentCommand.clear();
            }
        }
        else
        {
            currentCommand.push_back(arg);
        }
    }

    if (!currentCommand.empty())
    {
        commands.push_back(currentCommand);
    }

    return commands;
}

void handleLoop(const std::vector<std::string> &args)
{
    if (args.size() < 2)
    {
        throw std::runtime_error("Usage: loop <number_of_iterations> <command1> & <command2> & ...");
    }

    int iterations;
    try
    {
        iterations = std::stoi(args[0]);
    }
    catch (const std::exception &)
    {
        throw std::runtime_error("Invalid number of iterations.");
    }

    std::vector<std::vector<std::string>> commands = splitCommands(std::vector<std::string>(args.begin() + 1, args.end()));

    for (int i = 0; i < iterations; ++i)
    {
        for (const auto &command : commands)
        {
            if (!command.empty())
            {
                std::string cmd = command[0];
                std::vector<std::string> cmdArgs(command.begin() + 1, command.end());
                executeCommand(cmd, cmdArgs);
            }
        }
    }
}

#endif // LOOP_H
