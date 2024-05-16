#ifndef MOVE_DIRECTORY_H
#define MOVE_DIRECTORY_H

#include <iostream>
#include <filesystem>
#include <vector>

void moveDirectory(const std::vector<std::string> &args)
{
    if (args.size() != 2)
    {
        std::cout << "Usage: move <source_path> <destination_path>" << std::endl;
        return;
    }
    std::filesystem::path sourcePath = args[0];
    std::filesystem::path destinationPath = args[1];
    if (!std::filesystem::exists(sourcePath))
    {
        std::cout << "Source directory does not exist: " << sourcePath << std::endl;
        return;
    }
    std::filesystem::rename(sourcePath, destinationPath);
    std::cout << "Directory moved from " << sourcePath << " to " << destinationPath << std::endl;
}

#endif // MOVE_DIRECTORY_H
