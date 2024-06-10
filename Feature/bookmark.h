#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <filesystem>

class BookmarkManager
{
public:
    BookmarkManager()
    {
        initialDirectory = std::filesystem::current_path();
    }

    // Hàm để thêm bookmark
    void addBookmark(const std::string &name, const std::string &path)
    {
        if (!std::filesystem::exists(path))
        {
            std::cerr << "Error: Path does not exist: " << path << std::endl;
            return;
        }
        bookmarks[name] = path;
        std::cout << "Bookmark added: " << name << " -> " << path << std::endl;
    }

    // Hàm để xóa bookmark
    void removeBookmark(const std::string &name)
    {
        if (bookmarks.erase(name))
        {
            std::cout << "Bookmark removed: " << name << std::endl;
        }
        else
        {
            std::cerr << "Error: Bookmark not found: " << name << std::endl;
        }
    }

    // Hàm để liệt kê tất cả các bookmark
    void listBookmarks() const
    {
        if (bookmarks.empty())
        {
            std::cout << "No bookmarks available." << std::endl;
            return;
        }
        for (const auto &bookmark : bookmarks)
        {
            std::cout << bookmark.first << " -> " << bookmark.second << std::endl;
        }
    }

    // Hàm để chuyển đến thư mục đã được bookmark
    void goBookmark(const std::string &name)
    {
        auto it = bookmarks.find(name);
        if (it != bookmarks.end())
        {
            if (std::filesystem::exists(it->second))
            {
                std::filesystem::current_path(it->second);
                std::cout << "Changed directory to: " << it->second << std::endl;
            }
            else
            {
                std::cerr << "Error: Path does not exist: " << it->second << std::endl;
            }
        }
        else
        {
            std::cerr << "Error: Bookmark not found: " << name << std::endl;
        }
    }

    // Hàm để chuyển đến thư mục gốc
    void goHomeDirectory()
    {
        if (std::filesystem::exists(initialDirectory))
        {
            std::filesystem::current_path(initialDirectory);
            std::cout << "Changed directory to initial directory: " << initialDirectory << std::endl;
        }
        else
        {
            std::cerr << "Error: Initial directory does not exist: " << initialDirectory << std::endl;
        }
    }

private:
    std::unordered_map<std::string, std::string> bookmarks;
    std::filesystem::path initialDirectory;
};

#endif // BOOKMARK_H
