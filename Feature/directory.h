#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <filesystem>
#include <vector>
#include <unordered_set>

class DirectoryManager
{
public:
    // Các lệnh hỗ trợ
    static const std::unordered_set<std::string> supportedCommands;

    // Hàm lấy danh sách các lệnh hỗ trợ
    static const std::unordered_set<std::string> &getSupportedCommands()
    {
        return supportedCommands;
    }

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

private:
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
};

const std::unordered_set<std::string> DirectoryManager::supportedCommands = {
    "copy",
    "create",
    "delete",
    "list_tree",
    "move"};

#endif // DIRECTORY_H