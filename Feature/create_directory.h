#ifndef CREATE_DIRECTORY_H
#define CREATE_DIRECTORY_H

#include <iostream>
#include <filesystem>
#include <vector>

void createDirectory(const std::vector<std::string> &args)
{
    if (args.size() != 1)
    {
        std::cout << "Usage: create <directory_path>" << std::endl;
        return;
    }
    std::filesystem::path dirPath = args[0];
    if (std::filesystem::exists(dirPath))
    {
        std::cout << "Directory already exists: " << dirPath << std::endl;
        return;
    }
    std::filesystem::create_directories(dirPath);
    std::cout << "Directory created: " << dirPath << std::endl;
}

#endif // CREATE_DIRECTORY_H
