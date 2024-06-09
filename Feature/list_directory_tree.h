#ifndef LIST_DIRECTORY_TREE_H
#define LIST_DIRECTORY_TREE_H

#include <iostream>
#include <filesystem>
#include <vector>

void listDirectoryTreeHelper(const std::filesystem::path &path, int level)
{
    if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path))
    {
        return;
    }

    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        for (int i = 0; i < level; ++i)
        {
            std::cout << "  ";
        }
        std::cout << entry.path().filename().string() << std::endl;
        if (entry.is_directory())
        {
            listDirectoryTreeHelper(entry, level + 1);
        }
    }
}

void listDirectoryTree(const std::vector<std::string> &args)
{
    if (args.size() != 1)
    {
        std::cout << "Usage: list_tree <directory_path>" << std::endl;
        return;
    }
    std::filesystem::path dirPath = args[0];
    if (!std::filesystem::exists(dirPath))
    {
        std::cout << "Directory does not exist: " << dirPath << std::endl;
        return;
    }
    std::cout << dirPath.string() << std::endl;
    listDirectoryTreeHelper(dirPath, 1);
}

#endif // LIST_DIRECTORY_TREE_H
