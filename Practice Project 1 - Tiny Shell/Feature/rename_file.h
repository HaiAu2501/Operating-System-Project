#ifndef RENAME_FILE_H
#define RENAME_FILE_H

#include <iostream>
#include <filesystem>
#include <vector>

void renameFile(const std::vector<std::string> &args)
{
    if (args.size() != 2)
    {
        std::cout << "Usage: rename <old_file_path> <new_file_path>" << std::endl;
        return;
    }
    std::filesystem::path oldPath = args[0];
    std::filesystem::path newPath = args[1];
    if (!std::filesystem::exists(oldPath))
    {
        std::cout << "File does not exist: " << oldPath << std::endl;
        return;
    }
    std::filesystem::rename(oldPath, newPath);
    std::cout << "File renamed from " << oldPath << " to " << newPath << std::endl;
}

#endif // RENAME_FILE_H
