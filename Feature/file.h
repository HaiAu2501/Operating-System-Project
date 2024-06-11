#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <csignal>
#include <conio.h>
#include <windows.h>
#include <filesystem>

namespace fs = std::filesystem;

class FileManager
{
public:
    FileManager()
    {
        // Đăng ký xử lý tín hiệu SIGINT (Ctrl+C)
        signal(SIGINT, signalHandler);
    }

    static const std::unordered_set<std::string> supportedCommands;

    static const std::unordered_set<std::string> &getSupportedCommands()
    {
        return supportedCommands;
    }

    // Hàm để ghi nội dung vào file
    void writeFile(const std::vector<std::string> &args)
    {
        if (args.size() < 2)
        {
            std::cerr << "Usage: write_file <content> <filename> [~HEAD | ~FOOT | ~LINE N]" << std::endl;
            return;
        }

        std::string content = args[0];
        std::string filename = args[1];

        if (args.size() == 2)
        {
            // Mặc định ghi vào cuối file
            std::ofstream file(filename, std::ios::app);
            if (!file)
            {
                std::cerr << "Failed to open file: " << filename << std::endl;
                return;
            }

            file << content << std::endl;
            file.close();
        }
        else if (args.size() == 3 || (args.size() == 4 && args[2] == "~LINE"))
        {
            std::string position = args[2];
            std::ifstream file_in(filename);
            if (!file_in)
            {
                std::cerr << "Failed to open file: " << filename << std::endl;
                return;
            }

            std::vector<std::string> lines;
            std::string line;
            while (std::getline(file_in, line))
            {
                lines.push_back(line);
            }
            file_in.close();

            if (position == "~HEAD")
            {
                lines.insert(lines.begin(), content);
            }
            else if (position == "~FOOT")
            {
                lines.push_back(content);
            }
            else if (position == "~LINE")
            {
                if (args.size() != 4)
                {
                    std::cerr << "Usage: write_file <content> <filename> ~LINE N" << std::endl;
                    return;
                }
                size_t line_number = std::stoi(args[3]) - 1;
                if (line_number < lines.size())
                {
                    lines.insert(lines.begin() + line_number, content);
                }
                else
                {
                    lines.push_back(content);
                }
            }

            std::ofstream file_out(filename);
            if (!file_out)
            {
                std::cerr << "Failed to open file for writing: " << filename << std::endl;
                return;
            }

            for (const auto &l : lines)
            {
                file_out << l << std::endl;
            }
            file_out.close();
        }
        else
        {
            std::cerr << "Invalid number of arguments." << std::endl;
        }

        std::cout << "Successfully wrote to file: " << filename << std::endl;
    }

    // Hàm để đọc file
    void readFile(const std::vector<std::string> &args)
    {
        if (args.size() < 1 || args.size() > 4)
        {
            std::cerr << "Usage: read_file <filename> [~HEAD N | ~FOOT N | ~RANGE M N | ~LINE N]" << std::endl;
            return;
        }

        std::string filename = args[0];
        std::ifstream file(filename);
        if (!file)
        {
            std::cerr << "Could not open file: " << filename << std::endl;
            return;
        }

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();

        if (args.size() == 1)
        {
            // Mặc định đọc toàn bộ file, 5 dòng một lần và hỏi người dùng ấn Enter để tiếp tục hoặc Ctrl+C để thoát
            printLinesWithPause(lines, 0, lines.size());
        }
        else
        {
            std::string position = args[1];
            if (position == "~HEAD")
            {
                if (args.size() != 3)
                {
                    std::cerr << "Usage: read_file <filename> ~HEAD N" << std::endl;
                    return;
                }
                size_t num_lines = std::stoi(args[2]);
                printLines(lines, 0, std::min(num_lines, lines.size()));
            }
            else if (position == "~FOOT")
            {
                if (args.size() != 3)
                {
                    std::cerr << "Usage: read_file <filename> ~FOOT N" << std::endl;
                    return;
                }
                size_t num_lines = std::stoi(args[2]);
                printLines(lines, std::max(lines.size() - num_lines, (size_t)0), lines.size());
            }
            else if (position == "~RANGE")
            {
                if (args.size() != 4)
                {
                    std::cerr << "Usage: read_file <filename> ~RANGE M N" << std::endl;
                    return;
                }
                size_t start_line = std::stoi(args[2]) - 1;
                size_t end_line = std::stoi(args[3]) - 1;
                if (start_line <= end_line && end_line < lines.size())
                {
                    printLines(lines, start_line, end_line + 1);
                }
                else
                {
                    std::cerr << "Invalid line range." << std::endl;
                }
            }
            else if (position == "~LINE")
            {
                if (args.size() != 3)
                {
                    std::cerr << "Usage: read_file <filename> ~LINE N" << std::endl;
                    return;
                }
                size_t line_number = std::stoi(args[2]) - 1;
                if (line_number < lines.size())
                {
                    printLines(lines, line_number, line_number + 1);
                }
                else
                {
                    std::cerr << "Line number out of range." << std::endl;
                }
            }
            else
            {
                std::cerr << "Invalid position format." << std::endl;
            }
        }
    }

    // Hàm để hiển thị kích thước file và số lượng dòng
    void showFileSize(const std::string &fileName)
    {
        try
        {
            auto fileSize = fs::file_size(fileName);
            std::ifstream file(fileName);
            size_t lineCount = 0;
            std::string line;
            while (std::getline(file, line))
            {
                lineCount++;
            }
            std::cout << "Size of file " << fileName << ": " << fileSize << " bytes" << std::endl;
            std::cout << "Number of lines in file " << fileName << ": " << lineCount << std::endl;
        }
        catch (const fs::filesystem_error &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Hàm để mở file
    void openFile(const std::vector<std::string> &args)
    {
        if (args.size() != 1)
        {
            std::cout << "Usage: open <file_path>" << std::endl;
            return;
        }
        std::string filePath = args[0];
        ShellExecuteA(NULL, "open", filePath.c_str(), NULL, NULL, SW_SHOW);
    }

    // Hàm để đổi tên file
    void renameFile(const std::vector<std::string> &args)
    {
        if (args.size() != 2)
        {
            std::cout << "Usage: rename <old_file_path> <new_file_path>" << std::endl;
            return;
        }
        fs::path oldPath = args[0];
        fs::path newPath = args[1];
        if (!fs::exists(oldPath))
        {
            std::cout << "File does not exist: " << oldPath << std::endl;
            return;
        }
        fs::rename(oldPath, newPath);
        std::cout << "File renamed from " << oldPath << " to " << newPath << std::endl;
    }

    // Hàm để tạo một hoặc nhiều file
    void createFile(const std::vector<std::string> &fileNames)
    {
        for (const auto &fileName : fileNames)
        {
            std::ofstream file(fileName);
            if (file)
            {
                std::cout << "File created successfully: " << fileName << std::endl;
            }
            else
            {
                std::cerr << "Failed to create file: " << fileName << std::endl;
            }
        }
    }

    // Hàm để xóa một hoặc nhiều file
    void deleteFile(const std::vector<std::string> &fileNames)
    {
        for (const auto &fileName : fileNames)
        {
            if (fs::remove(fileName))
            {
                std::cout << "File deleted successfully: " << fileName << std::endl;
            }
            else
            {
                std::cerr << "Failed to delete file: " << fileName << std::endl;
            }
        }
    }

    // Hàm để kiểm tra xem file có tồn tại không
    void checkFileExistence(const std::vector<std::string> &fileNames)
    {
        for (const auto &fileName : fileNames)
        {
            if (fs::exists(fileName))
            {
                std::cout << "File exists: " << fileName << std::endl;
            }
            else
            {
                std::cout << "File does not exist: " << fileName << std::endl;
            }
        }
    }

    // Hàm in ra phần mở rộng của một hay nhiều file
    void printFileExtensions(const std::vector<std::string> &fileNames)
    {
        for (const auto &fileName : fileNames)
        {
            std::cout << "Extension of file " << fileName << ": " << fs::path(fileName).extension() << std::endl;
        }
    }

    // Hàm sao chép file
    void copyFile(const std::vector<std::string> &args)
    {
        if (args.size() != 2)
        {
            std::cout << "Usage: copy_file <source_file_path> <destination_file_path>" << std::endl;
            return;
        }
        std::string source = args[0];
        std::string destination = args[1];
        try
        {
            fs::copy_file(source, destination);
            std::cout << "File copied successfully from " << source << " to " << destination << std::endl;
        }
        catch (const fs::filesystem_error &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Hàm để di chuyển file
    void moveFile(const std::vector<std::string> &args)
    {
        if (args.size() != 2)
        {
            std::cout << "Usage: move_file <source_file_path> <destination_file_path>" << std::endl;
            return;
        }
        std::string source = args[0];
        std::string destination = args[1];
        try
        {
            fs::rename(source, destination);
            std::cout << "File moved successfully from " << source << " to " << destination << std::endl;
        }
        catch (const fs::filesystem_error &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Hàm để liệt kê tất cả file có đuôi xác định trong thư mục
    void listFilesWithExtension(const std::vector<std::string> &args)
    {
        if (args.size() > 2)
        {
            std::cout << "Usage: list_file <directory> <extension>" << std::endl;
            return;
        }

        // Nếu chỉ có 1 tham số, in ra tất cả file trong thư mục đó
        if (args.size() == 1)
        {
            std::string directory = args[0];
            for (const auto &entry : fs::directory_iterator(directory))
            {
                if (entry.is_regular_file())
                {
                    std::cout << entry.path().filename() << std::endl;
                }
            }
            return;
        }

        // Nếu có 2 tham số, in ra tất cả file có đuôi xác định trong thư mục đó
        std::string directory = args[0];
        std::string extension = args[1];
        for (const auto &entry : fs::directory_iterator(directory))
        {
            if (entry.is_regular_file() && entry.path().extension() == extension)
            {
                std::cout << entry.path().filename() << std::endl;
            }
        }
    }

private:
    static bool interrupted;

    // Hàm xử lý tín hiệu SIGINT
    static void signalHandler(int signum)
    {
        interrupted = true;
    }

    // Hàm để in các dòng từ start đến end-1
    void printLines(const std::vector<std::string> &lines, size_t start, size_t end)
    {
        for (size_t i = start; i < end; ++i)
        {
            std::cout << lines[i] << std::endl;
        }
        std::cout << "End of reading. Returning to shell..." << std::endl;
    }

    // Hàm để in các dòng từ start đến end-1 với tạm dừng
    void printLinesWithPause(const std::vector<std::string> &lines, size_t start, size_t end)
    {
        for (size_t i = start; i < end; ++i)
        {
            std::cout << lines[i] << std::endl;
            if (interrupted)
            {
                std::cout << "\nReading interrupted. Returning to shell..." << std::endl;
                interrupted = false; // Reset flag
                return;
            }

            if ((i + 1) % 5 == 0 && i + 1 < end)
            {
                std::cout << "[READ MORE] (Press any key to continue, Ctrl+C to quit)..." << std::endl;
                char ch = _getch();
                if (ch == 3)
                { // Ctrl+C
                    std::cout << "\nReading interrupted. Returning to shell..." << std::endl;
                    return;
                }
            }
        }
        std::cout << "End of reading. Returning to shell..." << std::endl;
    }
};

// Khởi tạo biến tĩnh
bool FileManager::interrupted = false;

// Khởi tạo danh sách các câu lệnh mà đối tượng này hỗ trợ
const std::unordered_set<std::string> FileManager::supportedCommands = {
    "write_file",
    "read_file",
    "file_size",
    "open",
    "rename"};

#endif // FILE_H
