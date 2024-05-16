#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <iostream>
#include <filesystem>
#include <vector>

void changeDirectory(const std::vector<std::string> &args)
{
    if (args.size() != 1)
    {
        std::cout << "Usage: cd <directory_path>" << std::endl;
        return;
    }
    std::filesystem::path dirPath = args[0];
    if (!std::filesystem::exists(dirPath) || !std::filesystem::is_directory(dirPath))
    {
        std::cout << "Directory does not exist: " << dirPath << std::endl;
        return;
    }
    std::filesystem::current_path(dirPath);
    std::cout << "Changed directory to " << dirPath << std::endl;
}

void listDirectoryContents(const std::vector<std::string> &args)
{
    std::filesystem::path dirPath = ".";
    if (args.size() == 1)
    {
        dirPath = args[0];
    }
    if (!std::filesystem::exists(dirPath) || !std::filesystem::is_directory(dirPath))
    {
        std::cout << "Directory does not exist: " << dirPath << std::endl;
        return;
    }
    for (const auto &entry : std::filesystem::directory_iterator(dirPath))
    {
        std::cout << entry.path().filename().string() << (entry.is_directory() ? "/" : "") << std::endl;
    }
}

void printWorkingDirectory(const std::vector<std::string> &args)
{
    std::cout << std::filesystem::current_path().string() << std::endl;
}

#endif // NAVIGATION_H
