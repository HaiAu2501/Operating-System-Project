#ifndef DELETE_DIRECTORY_H
#define DELETE_DIRECTORY_H

#include <iostream>
#include <filesystem>
#include <vector>

void deleteDirectory(const std::vector<std::string> &args)
{
    if (args.size() != 1)
    {
        std::cout << "Usage: delete <directory_path>" << std::endl;
        return;
    }
    std::filesystem::path dirPath = args[0];
    if (!std::filesystem::exists(dirPath))
    {
        std::cout << "Directory does not exist: " << dirPath << std::endl;
        return;
    }
    std::filesystem::remove_all(dirPath);
    std::cout << "Directory deleted: " << dirPath << std::endl;
}

#endif // DELETE_DIRECTORY_H
