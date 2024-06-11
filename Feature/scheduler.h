#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <iostream>
#include <sstream>

void executeCommand(const std::string &command, const std::vector<std::string> &args);

void scheduleCommand(const std::vector<std::string> &args)
{
    if (args.size() < 3 || args[1] != "s")
    {
        std::cerr << "Usage: after <number> s <command>" << std::endl;
        return;
    }

    int delay;
    try
    {
        delay = std::stoi(args[0]);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Invalid number: " << args[0] << std::endl;
        return;
    }

    std::string command = args[2];
    std::vector<std::string> commandArgs(args.begin() + 3, args.end());

    std::thread([=]()
                {
            std::this_thread::sleep_for(std::chrono::seconds(delay));
            std::cout << "\nThe thread is completed!" << std::endl;
            executeCommand(command, commandArgs); })
        .detach();

    std::cout << "Scheduled command '" << command << "' to run after " << delay << " seconds." << std::endl;
}

#endif // SCHEDULER_H
