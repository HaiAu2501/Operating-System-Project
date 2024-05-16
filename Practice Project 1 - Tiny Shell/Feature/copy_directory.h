#ifndef COPY_DIRECTORY_H
#define COPY_DIRECTORY_H

#include <iostream>
#include <filesystem>
#include <vector>

void copyDirectory(const std::vector<std::string> &args)
{
    if (args.size() != 2)
    {
        std::cout << "Usage: copy <source_path> <destination_path>" << std::endl;
        return;
    }
    std::filesystem::path sourcePath = args[0];
    std::filesystem::path destinationPath = args[1];
    if (!std::filesystem::exists(sourcePath) || !std::filesystem::is_directory(sourcePath))
    {
        std::cout << "Source directory does not exist: " << sourcePath << std::endl;
        return;
    }
    if (std::filesystem::exists(destinationPath))
    {
        std::cout << "Destination already exists: " << destinationPath << std::endl;
        return;
    }
    std::filesystem::copy(sourcePath, destinationPath, std::filesystem::copy_options::recursive);
    std::cout << "Directory copied from " << sourcePath << " to " << destinationPath << std::endl;
}

#endif // COPY_DIRECTORY_H
